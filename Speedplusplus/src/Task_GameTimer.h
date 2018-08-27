#pragma once
#include "TaskSystem.h"
#include "TimeCounter.h"
#include "CardCounter.h"
#include "Task_GameMessage.h"
#include "Task_Ranking.h"
#include "GameDefine.h"

enum struct GameState
{
	Ready,
	CountDown,
	Game,
	GameEnd,
	Result,
	End,
};

namespace GameTimer
{
	const std::string	defGroupName("�Q�[���^�C�}�[");	//�O���[�v��

	//----------------------------------------------
	class Task : public TaskAbstract
	{
	private:
		const int waitCountDown;
		const int waitGame;
		const int waitGameEnd;
		const int waitResult;

		GameState gameState;
		std::unique_ptr<CardCounter> cardCnt[2];
		TimeCounter timeCnt;
		TimeCounter cardAppTimeCnt;
		std::shared_ptr<GameMessage::Task> gameMessage;

		std::shared_ptr<Ranking::Task> ranking;

		Mode mode;

	public:
		Task(Mode mode);		//�R���X�g���N�^
		~Task();	//�f�X�g���N�^
		static std::shared_ptr<Task> Create(Mode mode);	//�^�X�N�̐���

		void Initialize();			//����������
		void Finalize() override;	//�I������
		void Update() override;		//�X�V
		void Draw() override;		//�`��

	private:
		void CountUpdate(bool isCntStart);

	public:
		const GameState& GetGameState() const;
	};
}