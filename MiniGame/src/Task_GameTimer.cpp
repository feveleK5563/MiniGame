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
		gameState(GameState::Ready),
		waitCountDown	(180),
		waitGame		(3600),
		waitGameEnd		(180),
		waitResult		(20)
	{ 
		cardCnt[0] = std::make_unique<CardCounter>(
			0,
			Math::Vec2(250, SystemDefine::windowSizeY + 200.f),
			Math::Vec2(120, 150), 0.5f);

		cardCnt[1] = std::make_unique<CardCounter>(
			(int)Suit::Etc_RedNum,
			Math::Vec2(120, SystemDefine::windowSizeY + 200.f),
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
		gameMessage = GameMessage::Task::Create(MessageType::Ready, 50);
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
		CountUpdate(gameState == GameState::CountDown ||
					gameState == GameState::Game);

		switch (gameState)
		{
		case GameState::Ready:	//�Q�[���J�n�O
			if (gameMessage->state != TaskState::Active)
			{
				gameState = GameState::CountDown;
				timeCnt.SetEndTime(waitCountDown);
				timeCnt.ResetCntTime();
			}
			break;

		case GameState::CountDown:	//�Q�[���J�n���O�̃J�E���g
			if (timeCnt.IsTimeEnd())
			{
				gameState = GameState::Game;
				timeCnt.SetEndTime(waitGame);
				timeCnt.ResetCntTime();
			}
			break;

		case GameState::Game:		//�Q�[����
			if (timeCnt.IsTimeEnd())
			{
				gameState = GameState::GameEnd;
				gameMessage = GameMessage::Task::Create(MessageType::Finish, 90);

				timeCnt.SetEndTime(waitGameEnd);
				timeCnt.ResetCntTime();
			}
			break;

		case GameState::GameEnd:	//�Q�[���I��
			if (timeCnt.IsTimeEnd())
			{
				gameState = GameState::Result;
				ranking = Ranking::Task::Create();

				timeCnt.SetEndTime(-1);
				timeCnt.ResetCntTime();
			}
			break;

		case GameState::Result:		//���ʉ��
			if (ranking->state == TaskState::Kill)
			{
				timeCnt.SetEndTime(waitResult);
				timeCnt.ResetCntTime();
			}
			if (timeCnt.IsTimeEnd())
			{
				gameState = GameState::End;
			}
			break;

		case GameState::End:	//�I��
			KillMe();
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
	//timeCnt�̍X�V�Ə\�A��̈ʂ̌v�Z
	void Task::CountUpdate(bool showCnt)
	{
		timeCnt.Run();

		cardAppTimeCnt.Run();

		int tenPlace = 0, unitPlace = 0;

		if (showCnt)
		{
			tenPlace = (timeCnt.GetRemainingTime() + 60) / 60 / 10;
			unitPlace = (timeCnt.GetRemainingTime() + 60) / 60 % 10;
		}

		cardCnt[0]->Update(tenPlace, true);

		if (gameState != GameState::Ready ||
			cardAppTimeCnt.GetNowCntTime() > 5)
		{
			//��̈ʂ́A�c�莞�Ԃ�3�ȉ��̏ꍇ�Ԑ����ɂȂ�
			if (tenPlace == 0 && unitPlace <= 3)
				cardCnt[1]->Update((int)Suit::Etc_RedNum + unitPlace, true);
			else
				cardCnt[1]->Update(unitPlace, true);
		}
	}

	//----------------------------------------------
	//��Ԃ̎擾
	const GameState& Task::GetTimeState() const
	{
		return gameState;
	}
}