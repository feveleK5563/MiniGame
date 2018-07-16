#pragma once
#include "TaskSystem.h"
#include "Card.h"

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

	public:
		Task(const CardID& id, const Math::Vec2& pos);		//�R���X�g���N�^
		~Task();	//�f�X�g���N�^
		static std::shared_ptr<Task> Create(const CardID& id, const Math::Vec2& pos);	//�^�X�N�̐���

		void Initialize();			//����������
		void Finalize() override;	//�I������
		void Update() override;		//�X�V
		void Draw() override;		//�`��
	};
}