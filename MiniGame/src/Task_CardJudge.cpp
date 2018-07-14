#include "Task_CardJudge.h"
#include <algorithm>
#include "DxLib.h"
#include "SystemDefine.h"
#include "InputState.h"
#include "Task_SceneTitle.h"
#include "SystemDefine.h"
#include "Task_JudgeEffect.h"

namespace CardJudge
{
	//��������������������������������������������������������������������������������������������
	//��������������������������������������������������������������������������������������������

	//----------------------------------------------
	//�^�X�N�̃R���X�g���N�^
	Task::Task():
		TaskAbstract(defGroupName, defPriority),
		progress(0),
		centerCardNum(0)
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
		CreateRandomCard(Side::Front);
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
		switch (progress)
		{
		case 0:
			CreateHandCard();
			break;

		case 1:
			Judge();
			break;
		}
		centerCardNum = (int)centerCardBundle.size();
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
		GameCard::Task::Create(
			CardType::HandCardLeft,
			*(handCard[0].second),
			Math::Vec2(SystemDefine::windowSizeX / 2.f, SystemDefine::windowSizeY + 200.f));

		//�J�[�h�E
		GameCard::Task::Create(
			CardType::HandCardRight,
			*(handCard[1].second),
			Math::Vec2(SystemDefine::windowSizeX / 2.f, SystemDefine::windowSizeY + 200.f));

		progress = 1;
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
			return;
		}

		//�J�[�h��
		if (SelectLeftCard())
		{
			centerCardBundle.emplace_back(handCard[0].second);
			CreateEffect(-30.f, 400.f, handCard[0].first == true);
			return;
		}

		//�J�[�h�E
		if (SelectRightCard())
		{
			centerCardBundle.emplace_back(handCard[1].second);
			CreateEffect(210.f, 400.f, handCard[1].first == true);
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

		GameCard::Task::Create(
			CardType::CenterCard,
			*cardID,
			Math::Vec2(SystemDefine::windowSizeX / 2.f, -200.f));

		centerCardBundle.emplace_back(cardID);
	}

	//----------------------------------------------
	//��D��ݒ肷��
	void Task::SetNextHandCard()
	{
		//���S�ɉ��̃J�[�h���Ȃ������ꍇ�͏����Ȃ�
		if (centerCardBundle.empty())
			return;

		//���S�J�[�h���̈�ԏ���擾
		auto centerTop = centerCardBundle.back();

		std::vector<std::shared_ptr<CardID>> right;	//�������i�[
		right.reserve(8);
		std::vector<std::shared_ptr<CardID>> wrong;	//�ԈႢ���i�[
		wrong.reserve(44);

		for (int s = 0; s < 4; ++s)
		{
			for (int n = 0; n < 13; ++n)
			{
				//�擪�J�[�h�Ɠ����J�[�h�������ꍇ�͂�蒼��
				if (centerTop->suit == Suit(s) && centerTop->number == n)
					continue;

				//����1��12�̃J�[�h�͐���
				if (abs(centerTop->number - n) % 11 == 1)
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
	//�G�t�F�N�g�𔭐�������
	void Task::CreateEffect(float angle, float length, bool rw)
	{
		float ang = angle + SystemDefine::GetRand(-20, 20);

		if (rw)
		{
			JudgeEffect::Task::Create(
				JEffect::Right, ang, length);
		}
		else
		{
			JudgeEffect::Task::Create(
				JEffect::Wrong, ang, length);
		}
		progress = 0;
	}

	//----------------------------------------------
	//�����J�[�h�̖������擾
	const int* Task::GetCenterCardNum() const
	{
		return &centerCardNum;
	}


	bool SelectLeftCard()
	{
		return	Input::key[KEY_INPUT_A]			== DOWN ||
				Input::joypad1[PadInput::LEFT]	== DOWN;
	}
	bool SelectRightCard()
	{
		return	Input::key[KEY_INPUT_D]			== DOWN ||
				Input::joypad1[PadInput::B]		== DOWN;
	}
	bool SelectThrowCard()
	{
		return	Input::key[KEY_INPUT_W]			== DOWN ||
				Input::joypad1[PadInput::L1]	== DOWN ||
				Input::joypad1[PadInput::R1]	== DOWN;
	}
}