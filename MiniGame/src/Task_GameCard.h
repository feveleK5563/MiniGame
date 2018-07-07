#pragma once
#include <memory>
#include "TaskSystem.h"
#include "CardBehavior.h"

namespace GameCard
{
	const std::string	defGroupName("�Q�[���J�[�h");	//�O���[�v��
	const float			defPriority(1.5f);			//�f�t�H���g�̏����D��x

	//----------------------------------------------
	class Task : public TaskAbstract
	{
	private:
		CardType cardType;	//�J�[�h�̎��
		std::unique_ptr<CardBehaviorAbstract> cardBehavior;	//�U�镑��

	public:
		//�R���X�g���N�^
		Task(CardType cardType);

		//�f�X�g���N�^
		~Task();
		
		//�^�X�N�̐���
		static std::shared_ptr<const Task> Create(CardType cardType);

		void Initialize() override;	//����������
		void Finalize() override;	//�I������
		void Update() override;		//�X�V
		void Draw() override;		//�`��
	};
}