#include "Task_CardJudge.h"
#include "DxLib.h"
#include "SystemDefine.h"
#include "InputState.h"
#include "Task_SceneTitle.h"
#include "SystemDefine.h"

namespace CardJudge
{
	//��������������������������������������������������������������������������������������������
	//��������������������������������������������������������������������������������������������

	//----------------------------------------------
	//�^�X�N�̃R���X�g���N�^
	Task::Task():
		TaskAbstract(defGroupName, defPriority),
		progress(0)
	{
		Initialize();
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

		return task;
	}

	//��������������������������������������������������������������������������������������������
	//��������������������������������������������������������������������������������������������

	//----------------------------------------------
	//����������
	//----------------------------------------------
	void Task::Initialize()
	{
		std::shared_ptr<CardID> cardID = RandomNextCard();
		GameCard::Task::Create(
			CardType::CenterCard,
			*cardID,
			Math::Vec2(SystemDefine::windowSizeX / 2.f, -200.f),
			GameCard::defPriority - 0.1f
		);
		centerCardBundle.emplace_back(cardID);
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
			SetHandCard();
			break;
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
		switch (SystemDefine::OutputRandomRange(0, 2, 1)[0])
		{
		case 0:
			handCard[0] = ChoiceNextCard(true);
			handCard[1] = ChoiceNextCard(false);
			break;

		case 1:
			handCard[0] = ChoiceNextCard(false);
			handCard[1] = ChoiceNextCard(true);
			break;

		case 2:
			handCard[0] = ChoiceNextCard(false);
			handCard[1] = ChoiceNextCard(false);
			break;
		}

		//�J�[�h��
		GameCard::Task::Create(
			CardType::HandCardLeft,
			*handCard[0],
			Math::Vec2(SystemDefine::windowSizeX / 2.f, SystemDefine::windowSizeY + 200.f),
			GameCard::defPriority
		);

		//�J�[�h�E
		GameCard::Task::Create(
			CardType::HandCardRight,
			*handCard[1],
			Math::Vec2(SystemDefine::windowSizeX / 2.f, SystemDefine::windowSizeY + 200.f),
			GameCard::defPriority
		);

		progress = 1;
	}

	//----------------------------------------------
	//���͂ɉ����Ď�D��o�^����
	void Task::SetHandCard()
	{
		//���������͖���
		if (SelectLeftCard() && SelectRightCard())
			return;

		//�J�[�h��
		if (SelectLeftCard())
		{
			centerCardBundle.emplace_back(handCard[0]);
			for (int i = 0; i < 2; ++i)
			{
				handCard[i].reset();
			}
			progress = 0;
			return;
		}

		//�J�[�h�E
		if (SelectRightCard())
		{
			centerCardBundle.emplace_back(handCard[1]);
			for (int i = 0; i < 2; ++i)
			{
				handCard[i].reset();
			}
			progress = 0;
			return;
		}

		//�J�[�h���̂āA�V�K�ɃJ�[�h��ǉ�����
		if (SelectThrowCard())
		{
			for (int i = 0; i < 2; ++i)
			{
				handCard[i].reset();
			}
			std::shared_ptr<CardID> cardID = RandomNextCard();
			GameCard::Task::Create(
				CardType::CenterCard,
				*cardID,
				Math::Vec2(SystemDefine::windowSizeX / 2.f, -200.f),
				GameCard::defPriority - 0.1f
			);
			centerCardBundle.emplace_back(cardID);
			progress = 0;
		}
	}

	//----------------------------------------------
	//�����_���ɃJ�[�h��ǉ�����
	std::shared_ptr<CardID> Task::RandomNextCard()
	{
		return std::make_shared<CardID>(
			Suit(SystemDefine::OutputRandomRange(0, 3, 1)[0]),
			SystemDefine::OutputRandomRange(0, 12, 1)[0],
			Side::Front);
	}

	//----------------------------------------------
	//��D��ݒ肷��
	std::shared_ptr<CardID> Task::ChoiceNextCard(bool isAnswerCard)
	{
		//���S�ɉ��̃J�[�h���Ȃ������ꍇ�͂����̃����_��
		if (centerCardBundle.empty())
			return RandomNextCard();

		//���S�J�[�h���̈�ԏ���擾
		auto centerTop = centerCardBundle.back();

		std::vector<std::shared_ptr<CardID>> answer;
		answer.reserve(52);
		for (int s = 0; s < 4; ++s)
		{
			for (int n = 0; n < 13; ++n)
			{
				if (((abs(centerTop->number - n) == 1) == isAnswerCard) &&
					(centerTop->suit != Suit(s) && centerTop->number != n))
				{
					answer.emplace_back(std::make_shared<CardID>(Suit(s), n, Side::Front));
				}
			}
		}

		return answer[SystemDefine::OutputRandomRange(0, (int)answer.size() - 1, 1)[0]];
	}

	//----------------------------------------------
	//���S�J�[�h�̖������擾
	int Task::GetCardNum() const
	{
		return (int)centerCardBundle.size();
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
				Input::joypad1[PadInput::Y]		== DOWN ||
				Input::joypad1[PadInput::UP]	== DOWN;
	}
}