#include "Task_SceneTitle.h"
#include "DxLib.h"
#include "SystemDefine.h"
#include "Task_Back.h"
#include "Task_SceneGame.h"
#include "GameDefine.h"
#include "Task_Ranking.h"
#include "Task_Sound.h"

namespace SceneTitle
{
	//��������������������������������������������������������������������������������������������
	//��������������������������������������������������������������������������������������������

	//----------------------------------------------
	//�^�X�N�̃R���X�g���N�^
	Task::Task():
		TaskAbstract(defGroupName, defPriority)
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
		if (!TS::taskSystem.FindTask(Back::defGroupName))
		{
			Back::Task::Create();
		}
		
		if (!TS::taskSystem.FindTask(Sound::defGroupName))
		{
			auto sound = Sound::Task::Create();
			sound->PlayBGM();
		}

		//���S�J�[�h���쐬(���ɑ��݂��Ă���ꍇ�͍쐬���Ȃ�)
		logoCard = TS::taskSystem.GetTaskOne<LogoCard::Task>(LogoCard::defGroupName);
		if (!logoCard)
		{
			logoCard = LogoCard::Task::Create(
				CardID(Suit::Etc, (int)Suit::Etc_Logo, Side::Back),
				Math::Vec2(SystemDefine::windowSizeX / 2.f, -200));
		}
	}

	//----------------------------------------------
	//�I������
	//----------------------------------------------
	void Task::Finalize()
	{
		//���ɃQ�[���^�X�N�𐶐�
		SceneGame::Task::Create(logoCard->GetIsBack());
	}

	//----------------------------------------------
	//�X�V
	//----------------------------------------------
	void Task::Update()
	{
		if (SelectRightCard() &&
			!TS::taskSystem.FindTask(Ranking::defGroupName))
		{
			Ranking::Task::Create();
		}
		if (logoCard->state == TaskState::Kill)
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