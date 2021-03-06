#include "Task_SceneTitle.h"
#include "DxLib.h"
#include "SystemDefine.h"
#include "Task_Back.h"
#include "Task_SceneMenu.h"
#include "GameDefine.h"
#include "Task_Result_Ranking.h"
#include "Task_Sound.h"

namespace SceneTitle
{
	//☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★
	//★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆

	//----------------------------------------------
	//タスクのコンストラクタ
	Task::Task():
		TaskAbstract(defGroupName, defPriority)
	{ 
	}
	//----------------------------------------------
	//タスクのデストラクタ
	Task::~Task()
	{

	}
	//----------------------------------------------
	//タスクの生成
	std::shared_ptr<Task> Task::Create()
	{
		std::shared_ptr<Task> task = std::make_shared<Task>();
		TS::taskSystem.RegistrationTask(task);

		task->Initialize();
		return task;
	}

	//◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆
	//◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇◆◇

	//----------------------------------------------
	//初期化処理
	//----------------------------------------------
	void Task::Initialize()
	{
		//背景を作成
		if (!TS::taskSystem.FindTask(Back::defGroupName))
		{
			Back::Task::Create();
		}
		
		//サウンド再生タスクを作成
		if (!TS::taskSystem.FindTask(Sound::defGroupName))
		{
			auto sound = Sound::Task::Create();
			sound->PlayBGM();
		}

		//ロゴカードを作成(既に存在している場合は作成しない)
		logoCard = TS::taskSystem.GetTaskOne<LogoCard::Task>(LogoCard::defGroupName);
		if (!logoCard)
		{
			logoCard = LogoCard::Task::Create(
				CardID(Suit::Etc, (int)Suit::Etc_Logo, Side::Back),
				Math::Vec2(SystemDefine::windowSizeX / 2.f, -200));
		}
	}

	//----------------------------------------------
	//終了処理
	//----------------------------------------------
	void Task::Finalize()
	{
		//次にゲームタスクを生成
		SceneMenu::Task::Create();
	}

	//----------------------------------------------
	//更新
	//----------------------------------------------
	void Task::Update()
	{
		if (logoCard->GetIsNoOut() &&
			Button::SelectRightCardP1() &&
			!TS::taskSystem.FindTask(Result_Ranking::defGroupName))
		{
			Result_Ranking::Task::Create();
		}
		if (logoCard->state == TaskState::Kill)
		{
			KillMe();
		}
	}

	//----------------------------------------------
	//描画
	//----------------------------------------------
	void Task::Draw()
	{

	}
}