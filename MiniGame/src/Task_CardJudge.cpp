#include "Task_CardJudge.h"
#include <algorithm>
#include "DxLib.h"
#include "SystemDefine.h"
#include "Task_SceneTitle.h"
#include "SystemDefine.h"
#include "GameDefine.h"
#include "Task_JudgeEffect.h"

namespace CardJudge
{
	//��������������������������������������������������������������������������������������������
	//��������������������������������������������������������������������������������������������

	//----------------------------------------------
	//�^�X�N�̃R���X�g���N�^
	Task::Task():
		TaskAbstract(defGroupName, defPriority),
		isHaveHandCard(false),
		centerCardNum(0),
		scoreFluctuation(0)
	{
	}
	//----------------------------------------------
	//�^�X�N�̃f�X�g���N�^
	Task::~Task()
	{

	}
	//----------------------------------------------
	//�^�X�N�̐���
	std::shared_ptr<Task> Task::Create()
	{
		std::shared_ptr<Task> task = std::make_shared<Task>();
		TS::taskSystem.RegistrationTask(task);

		task->Initialize();
		return task;
	}

	//��������������������������������������������������������������������������������������������
	//��������������������������������������������������������������������������������������������

	//----------------------------------------------
	//����������
	//----------------------------------------------
	void Task::Initialize()
	{
		auto gt = TS::taskSystem.GetTaskOne<GameTimer::Task>(GameTimer::defGroupName);
		gameState = &gt->GetTimeState();

		CreateRandomCard(Side::Back);
	}

	//----------------------------------------------
	//�I������
	//----------------------------------------------
	void Task::Finalize()
	{

	}

	//----------------------------------------------
	//�X�V
	//----------------------------------------------
	void Task::Update()
	{
		scoreFluctuation = 0;

		if (*gameState == GameState::Game)
		{
			if (isHaveHandCard)
			{
				Judge();
			}
			else
			{
				CreateHandCard();
			}
		}
	}

	//----------------------------------------------
	//�`��
	//----------------------------------------------
	void Task::Draw()
	{
		
	}

	//----------------------------------------------
	//��D���쐬����
	void Task::CreateHandCard()
	{
		//��D��ݒ�
		SetNextHandCard();

		//�J�[�h��
		HandCard::Task::Create(
			*(handCard[0].second),
			Math::Vec2(SystemDefine::windowSizeX / 2.f, SystemDefine::windowSizeY + 200.f),
			true);

		//�J�[�h�E
		HandCard::Task::Create(
			*(handCard[1].second),
			Math::Vec2(SystemDefine::windowSizeX / 2.f, SystemDefine::windowSizeY + 200.f),
			false);

		isHaveHandCard = true;
	}

	//----------------------------------------------
	//�I��������D�ɂ���āA�X�R�A�̕ω��ƃG�t�F�N�g�̐������s��
	void Task::Judge()
	{
		//���������͖���
		if (SelectLeftCard() && SelectRightCard())
			return;

		//�p�X
		if (SelectThrowCard())
		{
			CreateRandomCard(Side::Front);
			CreateEffect(90.f, 200.f,
				handCard[0].first == false && handCard[1].first == false);
			++centerCardNum;
			return;
		}

		//�J�[�h��
		if (SelectLeftCard())
		{
			centerTopCard = handCard[0].second;
			CreateEffect(-30.f, 400.f, handCard[0].first == true);
			++centerCardNum;
			return;
		}

		//�J�[�h�E
		if (SelectRightCard())
		{
			centerTopCard = handCard[1].second;
			CreateEffect(210.f, 400.f, handCard[1].first == true);
			++centerCardNum;
			return;
		}
	}

	//----------------------------------------------
	//�����_���ɃJ�[�h���쐬�A�ǉ�����
	void Task::CreateRandomCard(Side side)
	{
		std::shared_ptr<CardID> cardID = 
			std::make_shared<CardID>(
			Suit(SystemDefine::GetRand(0, 3)),
			SystemDefine::GetRand(0, 12),
			side);

		CenterCard::Task::Create(
			*cardID, Math::Vec2(SystemDefine::windowSizeX / 2.f, -200.f));

		centerTopCard= cardID;
	}

	//----------------------------------------------
	//��D��ݒ肷��
	void Task::SetNextHandCard()
	{
		//���S�ɉ��̃J�[�h���Ȃ������ꍇ�͏����Ȃ�
		if (centerTopCard == false)
			return;

		std::vector<std::shared_ptr<CardID>> right;	//�������i�[
		right.reserve(8);
		std::vector<std::shared_ptr<CardID>> wrong;	//�ԈႢ���i�[
		wrong.reserve(44);

		for (int s = 0; s < 4; ++s)
		{
			for (int n = 0; n < 13; ++n)
			{
				//�擪�J�[�h�Ɠ����J�[�h�������ꍇ�͂�蒼��
				if (centerTopCard->suit == Suit(s) && centerTopCard->number == n)
					continue;

				//����1��12�̃J�[�h�͐���
				if (abs(centerTopCard->number - n) % 11 == 1)
				{
					//�����̃J�[�h���i�[
					right.emplace_back(std::make_shared<CardID>(Suit(s), n, Side::Back));
				}
				else
				{
					//�ԈႢ�̃J�[�h���i�[
					wrong.emplace_back(std::make_shared<CardID>(Suit(s), n, Side::Back));
				}
			}
		}

		//�����ƂȂ�J�[�h��I��
		int isRight = SystemDefine::GetRand(0, 2);
		if (isRight == 2)	//�����i�V
		{
			std::random_shuffle(wrong.begin(), wrong.end());
			for (int i = 0; i < 2; ++i)
			{
				handCard[i].first = false;
				handCard[i].second = wrong[i];
			}
		}
		else	//�����A��
		{
			handCard[isRight].first = true;
			handCard[isRight].second = right[SystemDefine::GetRand(0, (int)right.size() - 1)];
			handCard[!isRight].first = false;
			handCard[!isRight].second = wrong[SystemDefine::GetRand(0, (int)wrong.size() - 1)];
		}
	}
	//----------------------------------------------
	//����ɉ����ăG�t�F�N�g�𔭐�������
	void Task::CreateEffect(float angle, float length, bool rw)
	{
		float ang = angle + SystemDefine::GetRand(-20, 20);

		if (rw)
		{
			JudgeEffect::Task::Create(
				JEffect::Right, ang, length);
			scoreFluctuation = 1;
		}
		else
		{
			JudgeEffect::Task::Create(
				JEffect::Wrong, ang, length);
			scoreFluctuation = -1;
		}
		isHaveHandCard = false;
	}

	//----------------------------------------------
	//�����J�[�h�̖������擾
	const int& Task::GetCenterCardNum() const
	{
		return centerCardNum;
	}

	//----------------------------------------------
	//����󋵂��擾
	const int& Task::GetScoreFluctuation() const
	{
		return scoreFluctuation;
	}
}