#pragma once
#include "TaskSystem.h"
#include "TimeCounter.h"
#include "CardCounter.h"

enum struct GameState
{
	Ready	= 240,
	Game	= 600,
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
		GameState gameState;
		std::unique_ptr<CardCounter> cardCnt[2];
		TimeCounter timeCnt;

	public:
		Task();		//�R���X�g���N�^
		~Task();	//�f�X�g���N�^
		static std::shared_ptr<Task> Create();	//�^�X�N�̐���

		void Initialize();			//����������
		void Finalize() override;	//�I������
		void Update() override;		//�X�V
		void Draw() override;		//�`��

		const GameState& GetTimeState() const;
	};
}