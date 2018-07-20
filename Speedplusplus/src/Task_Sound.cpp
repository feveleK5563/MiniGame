#include "Task_Sound.h"
#include "DxLib.h"

namespace Sound
{
	std::weak_ptr<Resource> Resource::instance;
	//----------------------------------------------
	//���\�[�X�̃R���X�g���N�^
	Resource::Resource()
	{
		bgm = LoadSoundMem("data/bgm/���ی�͂��َq�ł��܂݂Ȃ���I��BGM.ogg");

		se_turnOver		= LoadSoundMem("data/se/card-turn-over1.ogg", 8);
		se_handOut		= LoadSoundMem("data/se/card-hand-out1.ogg", 8);
		se_shaffle		= LoadSoundMem("data/se/card-shuffle2.ogg", 1);
		se_paperTear	= LoadSoundMem("data/se/paper-tear3.ogg", 8);
	}
	//----------------------------------------------
	//���\�[�X�̃f�X�g���N�^
	Resource::~Resource()
	{
		DeleteSoundMem(bgm);
		DeleteSoundMem(se_turnOver);
		DeleteSoundMem(se_handOut);
		DeleteSoundMem(se_shaffle);
		DeleteSoundMem(se_paperTear);
	}
	//----------------------------------------------
	//���\�[�X�̐���
	std::shared_ptr<Resource> Resource::Create()
	{
		auto sp = instance.lock();
		if (!sp)
		{
			sp = std::make_shared<Resource>();
			instance = sp;
		}
		return sp;
	}

	//��������������������������������������������������������������������������������������������
	//��������������������������������������������������������������������������������������������

	//----------------------------------------------
	//�^�X�N�̃R���X�g���N�^
	Task::Task():
		TaskAbstract(defGroupName, defPriority),
		res(Resource::Create()),
		bgm(res->bgm),
		se_turnOver(res->se_turnOver),
		se_handOut(res->se_handOut),
		se_shaffle(res->se_shaffle),
		se_paperTear(res->se_paperTear)
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
		std::shared_ptr<Task> task = 
			std::make_shared<Task>();
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
		
	}

	//----------------------------------------------
	//�`��
	//----------------------------------------------
	void Task::Draw()
	{
		
	}

	//----------------------------------------------
	//BGM�̍Đ�
	void Task::PlayBGM() const
	{
		if (!CheckSoundMem(bgm))
		{
			PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);
		}
	}

	//----------------------------------------------
	//SE(�J�[�h�߂���)�̍Đ�
	void Task::PlaySE_TurnOver(int volume) const
	{
		ChangeNextPlayVolumeSoundMem(volume, se_turnOver);
		PlaySoundMem(se_turnOver, DX_PLAYTYPE_BACK);
	}
	//----------------------------------------------
	//SE(�J�[�h������)�̍Đ�
	void Task::PlaySE_HandOut(int volume) const
	{
		ChangeNextPlayVolumeSoundMem(volume, se_handOut);
		PlaySoundMem(se_handOut, DX_PLAYTYPE_BACK);
	}
	//----------------------------------------------
	//SE(�V���b�t��)�̍Đ�
	void Task::PlaySE_Shaffle(int volume) const
	{
		ChangeNextPlayVolumeSoundMem(volume, se_shaffle);
		PlaySoundMem(se_shaffle, DX_PLAYTYPE_BACK);
	}
	//----------------------------------------------
	//SE(���j��)�̍Đ�
	void Task::PlaySE_PaperTear(int volume) const
	{
		ChangeNextPlayVolumeSoundMem(volume, se_paperTear);
		PlaySoundMem(se_paperTear, DX_PLAYTYPE_BACK);
	}
}