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
		Card	card;			//�J�[�h���
		int		progress;		//�i�s�x
		bool	isBumpCard;		//�Փ˂̓�����s�����ۂ�
		bool	isOut;			//��ʊO�ɏ����邩�ۂ�
		float	moveSpeed;		//�J�[�h�̈ړ����x

		const int*	centerCardNum;	//�����̃J�[�h����
		int			cardOrder;		//���̃J�[�h�̏���
		TimeCounter	timeCnt;		//����̎��Ԍv��

		const GameState* gameState;	//�Q�[���̐i�s��

	public:
		//�R���X�g���N�^
		Task(const CardID& id, const Math::Vec2& pos, bool isBumpCard);
		//�f�X�g���N�^
		~Task();
		//�^�X�N�̐���
		static std::shared_ptr<Task> Create(const CardID& id, const Math::Vec2& pos, bool isBumpCard);

		void Initialize();			//����������
		void Finalize() override;	//�I������
		void Update() override;		//�X�V
		void Draw() override;		//�`��

	private:
		void BumpCardMove();
		void WindowOutCard();
	};
}