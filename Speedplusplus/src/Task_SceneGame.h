#pragma once
#include "TaskSystem.h"
#include "Task_GameTimer.h"
#include "Task_CardJudge.h"
#include "Task_GameScore.h"
#include "GameDefine.h"

namespace SceneGame
{
	const std::string	defGroupName("�{��");	//�O���[�v��
	const float			defPriority(0.f);		//�f�t�H���g�̏����D��x

	//----------------------------------------------
	class Task : public TaskAbstract
	{
	private:
		Mode mode;			//���[�h
		std::shared_ptr<GameTimer::Task> gameTimer;
		std::shared_ptr<CardJudge::Task> cardJudge;
		std::array<std::shared_ptr<GameScore::Task>, 2> gameScore;

	public:
		Task(Mode mode);			//�R���X�g���N�^
		~Task();					//�f�X�g���N�^
		static std::shared_ptr<Task> Create(Mode mode);	//�^�X�N�̐���

		void Initialize();			//����������
		void Finalize() override;	//�I������
		void Update() override;		//�X�V
		void Draw() override;		//�`��
	};
}