#pragma once
#include <memory>
#include "TaskSystem.h"
#include "CardBehavior.h"

namespace GameCard
{
	const std::string	defGroupName("�Q�[���J�[�h");	//�O���[�v��

	//----------------------------------------------
	class Task : public TaskAbstract
	{
	private:
		std::unique_ptr<CardBehaviorAbstract> cardBehavior;	//�U�镑��

	public:
		//�R���X�g���N�^
		Task();

		//�f�X�g���N�^
		~Task();
		
		//�^�X�N�̐���
		static std::shared_ptr<Task> Create(CardType cardType, const CardID& id, const Math::Vec2& pos);

		void Initialize(CardType cardType, const CardID& id, const Math::Vec2& pos);	//����������
		void Finalize() override;	//�I������
		void Update() override;		//�X�V
		void Draw() override;		//�`��
	};
}