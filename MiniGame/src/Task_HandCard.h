#pragma once
#include "TaskSystem.h"
#include "Card.h"

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

	public:
		//�R���X�g���N�^
		Task(const CardID& id, const Math::Vec2& pos, bool LorR);

		//�f�X�g���N�^
		~Task();
		
		//�^�X�N�̐���
		static std::shared_ptr<Task> Create(const CardID& id, const Math::Vec2& pos, bool LorR);

		void Initialize();			//����������
		void Finalize() override;	//�I������
		void Update() override;		//�X�V
		void Draw() override;		//�`��
	};
}