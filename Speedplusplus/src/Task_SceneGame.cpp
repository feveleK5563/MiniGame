#include "Task_SceneGame.h"
#include "DxLib.h"
#include "Task_SceneTitle.h"
#include "SystemDefine.h"

namespace SceneGame
{
	//��������������������������������������������������������������������������������������������
	//��������������������������������������������������������������������������������������������

	//----------------------------------------------
	//�^�X�N�̃R���X�g���N�^
	Task::Task(Mode mode):
		TaskAbstract(defGroupName, defPriority),
		isBackMode(isBackMode),
		mode(mode)
	{ 
	}
	//----------------------------------------------
	//�^�X�N�̃f�X�g���N�^
	Task::~Task()
	{

	}
	//----------------------------------------------
	//�^�X�N�̐���
	std::shared_ptr<Task> Task::Create(Mode mode)
	{
		std::shared_ptr<Task> task = std::make_shared<Task>(mode);
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
		if (mode == Mode::VS)
		{
			KillMe();
			return;
		}

		gameTimer = GameTimer::Task::Create();
		cardJudge = CardJudge::Task::Create();
		gameScore = GameScore::Task::Create();
	}

	//----------------------------------------------
	//�I������
	//----------------------------------------------
	void Task::Finalize()
	{
		LogoCard::Task::Create(
			CardID(Suit::Etc, (int)Suit::Etc_Logo, Side::Front),
			Math::Vec2(SystemDefine::windowSizeX / 2.f, SystemDefine::windowSizeY / 2.f));

		SceneTitle::Task::Create();
		TS::taskSystem.KillTask("�J�[�h����t");
	}

	//----------------------------------------------
	//�X�V
	//----------------------------------------------
	void Task::Update()
	{
		if (gameTimer->state == TaskState::Kill)
		{
			cardJudge->KillMe();
			gameScore->KillMe();
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