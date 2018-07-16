#pragma once
#include "TaskSystem.h"
#include "Task_GameTimer.h"
#include "Task_CardJudge.h"

namespace SceneGame
{
	const std::string	defGroupName("�{��");	//�O���[�v��
	const float			defPriority(0.f);		//�f�t�H���g�̏����D��x

	//----------------------------------------------
	class Task : public TaskAbstract
	{
	private:
		std::shared_ptr<GameTimer::Task> gameTimer;
		std::shared_ptr<CardJudge::Task> cardJudge;

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