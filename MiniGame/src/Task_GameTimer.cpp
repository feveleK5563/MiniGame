#include "Task_GameTimer.h"
#include "DxLib.h"
#include "SystemDefine.h"
#include "GameDefine.h"

namespace GameTimer
{
	//��������������������������������������������������������������������������������������������
	//��������������������������������������������������������������������������������������������

	//----------------------------------------------
	//�^�X�N�̃R���X�g���N�^
	Task::Task():
		TaskAbstract(defGroupName, Priority::countCard),
		state(TimeState::Ready),
		timeCnt(120)
	{ 
		cardCnt[0] = std::make_unique<CardCounter>(6,	Math::Vec2(250, SystemDefine::windowSizeY + 200.f),
														Math::Vec2(120, 150), 0.5f);

		cardCnt[1] = std::make_unique<CardCounter>(0,	Math::Vec2(120, SystemDefine::windowSizeY + 200.f),
														Math::Vec2(250, 150), 0.5f);
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
		timeCnt.Run();
		switch (state)
		{
		case TimeState::Ready:	//�Q�[���J�n�O
			cardCnt[0]->Update(6);
			if (timeCnt.GetNowCntTime() > 5)
				cardCnt[1]->Update(0);

			if (timeCnt.IsTimeEnd())
			{
				state = TimeState::Game;
				timeCnt.SetEndTime(3600);
				timeCnt.ResetCntTime();
			}
			break;

		case TimeState::Game:	//�Q�[����
		case TimeState::End:	//�Q�[���I��
			cardCnt[0]->Update(timeCnt.GetRemainingTime() / 60 / 10);
			cardCnt[1]->Update(timeCnt.GetRemainingTime() / 60 % 10);
			if (timeCnt.GetRemainingTime() < 60)
			{
				state = TimeState::End;
			}
			break;
		}
	}

	//----------------------------------------------
	//�`��
	//----------------------------------------------
	void Task::Draw()
	{
		for (int i = 0; i < 2; ++i)
		{
			cardCnt[i]->Draw();
		}
	}

	//----------------------------------------------
	//��Ԃ̎擾
	TimeState Task::GetTimeState() const
	{
		return state;
	}
}