#pragma once
#include "TaskSystem.h"
#include "Card.h"

namespace HandCard
{
	const std::string	defGroupName("手札");	//グループ名

	//----------------------------------------------
	class Task : public TaskAbstract
	{
	private:
		Card	card;		//カード情報
		int		progress;	//進行度
		bool	LorR;		//初期カード位置(右か左か)

	public:
		//コンストラクタ
		Task(const CardID& id, const Math::Vec2& pos, bool LorR);

		//デストラクタ
		~Task();
		
		//タスクの生成
		static std::shared_ptr<Task> Create(const CardID& id, const Math::Vec2& pos, bool LorR);

		void Initialize();			//初期化処理
		void Finalize() override;	//終了処理
		void Update() override;		//更新
		void Draw() override;		//描画
	};
}