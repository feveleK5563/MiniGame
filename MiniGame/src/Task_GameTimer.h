#pragma once
#include "TaskSystem.h"
#include "TimeCounter.h"
#include "Card.h"

namespace GameTimer
{
	const std::string	defGroupName("�Q�[���^�C�}�[");	//�O���[�v��
	const float			defPriority(0.f);			//�f�t�H���g�̏����D��x

	//----------------------------------------------
	class Task : public TaskAbstract
	{
	private:
		std::unique_ptr<Card> card[2];
		TimeCounter timeCnt;

	public:
		Task();		//�R���X�g���N�^
		~Task();	//�f�X�g���N�^
		static std::shared_ptr<Task> Create();	//�^�X�N�̐���

		void Initialize();			//����������
		void Finalize() override;	//�I������
		void Update() override;		//�X�V
		void Draw() override;		//�`��
	};
}