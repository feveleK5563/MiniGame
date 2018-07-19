#pragma once
#include "TaskSystem.h"
#include "TimeCounter.h"
#include "CardCounter.h"

namespace GameScore
{
	const std::string	defGroupName("�Q�[���X�R�A");	//�O���[�v��

	//----------------------------------------------
	class Task : public TaskAbstract
	{
	private:
		static const int cardNum = 4;	//�J�[�h����
		TimeCounter timeCnt;			//���Ԍv��
		int combo;						//�R���{��
		int score;						//�X�R�A��

		std::unique_ptr<CardCounter> comboCardCnt;			//�R���{�̕\���p�J�[�h
		std::unique_ptr<CardCounter> scoreCardCnt[cardNum];	//�X�R�A�̕\���p�J�[�h
		const int&			scoreFluctuation;				//�����

	public:
		//�R���X�g���N�^
		Task();
		
		//�f�X�g���N�^
		~Task();
		
		//�^�X�N�̐���
		static std::shared_ptr<Task> Create();

		void Initialize();			//����������
		void Finalize() override;	//�I������
		void Update() override;		//�X�V
		void Draw() override;		//�`��

	private:
		void ScoreUpdate();

	public:
		const int& GetScore() const;
	};
}