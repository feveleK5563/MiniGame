#include "Task_SceneTitle.h"
#include "DxLib.h"
#include "InputState.h"
#include "SystemDefine.h"
#include "Task_Back.h"
#include "Task_SceneGame.h"

namespace SceneTitle
{
	//��������������������������������������������������������������������������������������������
	//��������������������������������������������������������������������������������������������

	//----------------------------------------------
	//�^�X�N�̃R���X�g���N�^
	Task::Task():
		TaskAbstract(defGroupName, defPriority)
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
		if (!TS::taskSystem.FindTask(Back::defGroupName))
		{
			Back::Task::Create();
		}

		logoCardRef = GameCard::Task::Create(
			CardType::LogoCard,
			CardID(Suit::Etc, 1, Side::Back),
			Math::Vec2(SystemDefine::windowSizeX / 2.f, -200),
			GameCard::defPriority);
	}

	//----------------------------------------------
	//�I������
	//----------------------------------------------
	void Task::Finalize()
	{
		SceneGame::Task::Create();
	}

	//----------------------------------------------
	//�X�V
	//----------------------------------------------
	void Task::Update()
	{
		if (logoCardRef->state == TaskState::Kill)
		{
			KillMe();
		}
	}

	//----------------------------------------------
	//�`��
	//----------------------------------------------
	void Task::Draw()
	{

	}
}