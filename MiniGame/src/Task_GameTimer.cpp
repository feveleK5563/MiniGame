#include "Task_GameTimer.h"
#include "DxLib.h"
#include "SystemDefine.h"
#include "GameDefine.h"

namespace GameTimer
{
	//
	//

	//----------------------------------------------
	//^XNΜRXgN^
	Task::Task():
		TaskAbstract(defGroupName, Priority::countCard),
		gameState(GameState::Ready),
		timeCnt((int)GameState::Ready)
	{ 
		cardCnt[0] = std::make_unique<CardCounter>(
			0,
			Math::Vec2(250, SystemDefine::windowSizeY + 200.f),
			Math::Vec2(120, 150), 0.5f);

		cardCnt[1] = std::make_unique<CardCounter>(
			0,
			Math::Vec2(120, SystemDefine::windowSizeY + 200.f),
			Math::Vec2(250, 150), 0.5f);
	}
	//----------------------------------------------
	//^XNΜfXgN^
	Task::~Task()
	{

	}
	//----------------------------------------------
	//^XNΜΆ¬
	std::shared_ptr<Task> Task::Create()
	{
		std::shared_ptr<Task> task = std::make_shared<Task>();
		TS::taskSystem.RegistrationTask(task);

		task->Initialize();
		return task;
	}

	//
	//

	//----------------------------------------------
	//ϊ»
	//----------------------------------------------
	void Task::Initialize()
	{
		gameMessage = GameMessage::Task::Create(MessageType::Ready, 20);
	}

	//----------------------------------------------
	//IΉ
	//----------------------------------------------
	void Task::Finalize()
	{

	}

	//----------------------------------------------
	//XV
	//----------------------------------------------
	void Task::Update()
	{
		CountUpdate(gameMessage->state != TaskState::Active);

		switch (gameState)
		{
		case GameState::Ready:	//Q[JnO
			if (timeCnt.IsTimeEnd())
			{
				gameState = GameState::Game;
				timeCnt.SetEndTime((int)GameState::Game);
				timeCnt.ResetCntTime();
			}
			break;

		case GameState::Game:		//Q[
			if (timeCnt.IsTimeEnd())
			{
				gameState = GameState::GameEnd;
				gameMessage = GameMessage::Task::Create(MessageType::Finish, 90);
			}
			break;

		case GameState::GameEnd:	//Q[IΉ
			if (gameMessage->state == TaskState::Kill)
			{
				gameState = GameState::Result;
			}
			break;

		case GameState::Result:		//ΚζΚ
			gameState = GameState::End;
			break;

		case GameState::End:	//IΉ
			KillMe();
			break;
		}
	}

	//----------------------------------------------
	//`ζ
	//----------------------------------------------
	void Task::Draw()
	{
		for (int i = 0; i < 2; ++i)
		{
			cardCnt[i]->Draw();
		}
	}

	//----------------------------------------------
	//timeCntΜXVΖ\AκΜΚΜvZ
	void Task::CountUpdate(bool isCntStart)
	{
		if (isCntStart)
			timeCnt.Run();

		cardAppTimeCnt.Run();

		int tenPlace = 0, unitPlace = 0;

		if (gameState == GameState::Ready ||
			gameState == GameState::Game)
		{
			tenPlace = (timeCnt.GetRemainingTime() + 60) / 60 / 10;
			unitPlace = (timeCnt.GetRemainingTime() + 60) / 60 % 10;
		}

		cardCnt[0]->Update(tenPlace, isCntStart);

		if (gameState != GameState::Ready ||
			cardAppTimeCnt.GetNowCntTime() > 5)
		{
			//κΜΚΝAcθΤͺ3ΘΊΜκΤΙΘι
			if (tenPlace == 0 && unitPlace <= 3)
				cardCnt[1]->Update((int)Suit::Etc_RedNum + unitPlace, isCntStart);
			else
				cardCnt[1]->Update(unitPlace, isCntStart);
		}
	}

	//----------------------------------------------
	//σΤΜζΎ
	const GameState& Task::GetTimeState() const
	{
		return gameState;
	}
}