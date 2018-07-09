#include "Task_CardJudge.h"
#include "DxLib.h"
#include "SystemDefine.h"
#include "InputState.h"
#include "Task_SceneTitle.h"

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
		//�J�[�h��
		handCard[0] = std::make_shared<CardID>(Suit::Spade, 9, Side::Front);
		GameCard::Task::Create(
			CardType::HandCardLeft,
			*handCard[0],
			Math::Vec2(SystemDefine::windowSizeX / 2.f, SystemDefine::windowSizeY + 200.f),
			GameCard::defPriority
		);

		//�J�[�h�E
		handCard[1] = std::make_shared<CardID>(Suit::Heart, 9, Side::Front);
		GameCard::Task::Create(
			CardType::HandCardRight,
			*handCard[1],
			Math::Vec2(SystemDefine::windowSizeX / 2.f, SystemDefine::windowSizeY + 200.f),
			GameCard::defPriority
		);

		progress = 1;
	}

	//----------------------------------------------
	//�I��������D��o�^����
	void Task::SetHandCard()
	{
		if ((Input::key[KEY_INPUT_A] == DOWN || Input::joypad1[PadInput::LEFT] == DOWN) &&
			(Input::key[KEY_INPUT_D] == DOWN || Input::joypad1[PadInput::B] == DOWN))
			return;

		//�J�[�h��
		if (Input::key[KEY_INPUT_A] == DOWN ||
			Input::joypad1[PadInput::LEFT] == DOWN)
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
		if (Input::key[KEY_INPUT_D] == DOWN ||
			Input::joypad1[PadInput::B] == DOWN)
		{
			centerCardBundle.emplace_back(handCard[1]);
			for (int i = 0; i < 2; ++i)
			{
				handCard[i].reset();
			}
			progress = 0;
			return;
		}
	}

	//----------------------------------------------
	//���S�J�[�h�̖������擾
	int Task::GetCardNum() const
	{
		return (int)centerCardBundle.size();
	}
}