#pragma once
#include "TaskSystem.h"
#include "Card.h"
#include "Task_GameTimer.h"

namespace CenterCard
{
	const std::string	defGroupName("�����J�[�h");	//�O���[�v��

	//----------------------------------------------
	class Task : public TaskAbstract
	{
	private:
		Card	card;				//�J�[�h���
		int		progress;			//�i�s�x
		int		cardOrder;			//���̃J�[�h�̏���
		const int*	centerCardNum;	//�����̃J�[�h����
		const GameState* gameState;	//�Q�[���̐i�s��
		float moveSpeed;			//�J�[�h�̈ړ����x

	public:
		//�R���X�g���N�^
		Task(const CardID& id, const Math::Vec2& pos, const GameState* gameState);
		//�f�X�g���N�^
		~Task();
		//�^�X�N�̐���
		static std::shared_ptr<Task> Create(const CardID& id, const Math::Vec2& pos, const GameState* gameState);

		void Initialize();			//����������
		void Finalize() override;	//�I������
		void Update() override;		//�X�V
		void Draw() override;		//�`��
	};
}