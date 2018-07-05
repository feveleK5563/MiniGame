#pragma once
#include "TaskSystem.h"
#include "Card.h"

namespace TitleLogo
{
	const std::string	defGroupName("�^�C�g�����S");	//�O���[�v��
	const float			defPriority(1.2f);		//�f�t�H���g�̏����D��x

	//----------------------------------------------
	class Task : public TaskAbstract
	{
	private:
		Card logoCard;

	public:
		Task();		//�R���X�g���N�^
		~Task();	//�f�X�g���N�^
		static const std::shared_ptr<const Task> Create();	//�^�X�N�̐���

		void Initialize() override;	//����������
		void Finalize() override;	//�I������
		void Update() override;		//�X�V
		void Draw() override;		//�`��
	};
}