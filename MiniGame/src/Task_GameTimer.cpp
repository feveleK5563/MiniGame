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
		timeCnt((int)GameState::Ready)
	{ 
		cardCnt[0] = std::make_unique<CardCounter>(
			0,	Math::Vec2(250, SystemDefine::windowSizeY + 200.f),
				Math::Vec2(120, 150), 0.5f);

		cardCnt[1] = std::make_unique<CardCounter>(
			(int)Suit::Etc_RedNum + 3,	Math::Vec2(120, SystemDefine::windowSizeY + 200.f),
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
		CountUpdate();

		switch (gameState)
		{
		case GameState::Ready:	//�Q�[���J�n�O
			if (timeCnt.IsTimeEnd())
			{
				gameState = GameState::Game;
				timeCnt.SetEndTime((int)GameState::Game);
				timeCnt.ResetCntTime();
			}
			break;

		case GameState::Game:		//�Q�[����
			if (timeCnt.IsTimeEnd())
			{
				gameState = GameState::GameEnd;
			}
			break;

		case GameState::GameEnd:	//�Q�[���I��
			//gameState = GameState::Result;
			break;

		case GameState::Result:		//���ʉ��
			gameState = GameState::End;
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
	void Task::CountUpdate()
	{
		timeCnt.Run();
		int tenPlace = (timeCnt.GetRemainingTime() + 59) / 60 / 10;
		int unitPlace = (timeCnt.GetRemainingTime() + 59) / 60 % 10;

		cardCnt[0]->Update(tenPlace);

		if (gameState != GameState::Ready ||
			timeCnt.GetNowCntTime() > 5)
		{
			//��̈ʂ́A�c�莞�Ԃ�3�ȉ��̏ꍇ�Ԑ����ɂȂ�
			if (tenPlace == 0 && unitPlace <= 3)
				cardCnt[1]->Update((int)Suit::Etc_RedNum + unitPlace);
			else
				cardCnt[1]->Update(unitPlace);
		}
	}

	//----------------------------------------------
	//��Ԃ̎擾
	const GameState& Task::GetTimeState() const
	{
		return gameState;
	}
}