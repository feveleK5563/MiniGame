#pragma once
#include "TaskSystem.h"
#include "Card.h"
#include "Task_GameTimer.h"

namespace HandCard
{
	const std::string	defGroupName("��D");	//�O���[�v��

	//----------------------------------------------
	class Task : public TaskAbstract
	{
	private:
		Card	card;		//�J�[�h���
		int		progress;	//�i�s�x
		bool	LorR;		//�����J�[�h�ʒu(�E������)
		const GameState* gameState;	//�Q�[���̐i�s��

	public:
		//�R���X�g���N�^
		Task(const CardID& id, const Math::Vec2& pos, bool LorR, const GameState* gameState);

		//�f�X�g���N�^
		~Task();
		
		//�^�X�N�̐���
		static std::shared_ptr<Task> Create(const CardID& id, const Math::Vec2& pos, bool LorR, const GameState* gameState);

		void Initialize();			//����������
		void Finalize() override;	//�I������
		void Update() override;		//�X�V
		void Draw() override;		//�`��
	};
}