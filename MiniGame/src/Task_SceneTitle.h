#pragma once
#include "TaskSystem.h"
#include "Task_GameCard.h"

namespace SceneTitle
{
	const std::string	defGroupName("�^�C�g��");	//�O���[�v��
	const float			defPriority(0.f);			//�f�t�H���g�̏����D��x

	//----------------------------------------------
	class Task : public TaskAbstract
	{
	private:
		std::shared_ptr<const GameCard::Task> logoCardRef;

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