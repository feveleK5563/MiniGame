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
		bool		isUseCombo;			//�R���{���g�p���邩�ۂ�
		bool		isRedScore;			//�X�R�A�J�[�h��Ԑ����ɂ��邩�ۂ�
		int			combo;				//�R���{��
		int			score;				//�X�R�A��
		Math::Vec2	startPos;			//�������W
		Math::Vec2	endPos;				//�ړ�����W
		float		size;				//�J�[�h�̃T�C�Y

		std::unique_ptr<CardCounter> comboCardCnt;			//�R���{�̕\���p�J�[�h
		std::unique_ptr<CardCounter> scoreCardCnt[cardNum];	//�X�R�A�̕\���p�J�[�h
		const int&			scoreFluctuation;				//�����

	public:
		//�R���X�g���N�^
		Task(const int& setScore, bool isUseCombo, bool isRedScore,
			const Math::Vec2& startPos, const Math::Vec2& endPos, float size);
		
		//�f�X�g���N�^
		~Task();
		
		//�^�X�N�̐���
		static std::shared_ptr<Task> Create(const int& setScore, bool isUseCombo, bool isRedScore,
			const Math::Vec2& startPos, const Math::Vec2& endPos, float size);

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