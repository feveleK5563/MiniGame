#define NOMINMAX
#include "Task_GameScore.h"
#include "DxLib.h"
#include "SystemDefine.h"
#include "GameDefine.h"
#include "Task_CardJudge.h"

namespace GameScore
{
	//��������������������������������������������������������������������������������������������
	//��������������������������������������������������������������������������������������������

	//----------------------------------------------
	//�^�X�N�̃R���X�g���N�^
	Task::Task(const int& setScore, bool isUseCombo, bool isRedScore,
		const Math::Vec2& startPos, const Math::Vec2& endPos, float size):
		TaskAbstract(defGroupName, Priority::countCard),
		isUseCombo(isUseCombo),
		isRedScore(isRedScore),
		combo(0),
		score(0),
		startPos(startPos),
		endPos(endPos),
		size(size),
		timeCnt(-1),
		scoreFluctuation(setScore)
	{
	}
	//----------------------------------------------
	//�^�X�N�̃f�X�g���N�^
	Task::~Task()
	{

	}
	//----------------------------------------------
	//�^�X�N�̐���
	std::shared_ptr<Task> Task::Create(const int& setScore, bool isUseCombo, bool isRedScore,
		const Math::Vec2& startPos, const Math::Vec2& endPos, float size)
	{
		std::shared_ptr<Task> task = 
			std::make_shared<Task>(setScore, isUseCombo, isRedScore, startPos, endPos, size);
		TS::taskSystem.RegistrationTask(task);

		task->Initialize();
		return task;
	}

	//��������������������������������������������������������������������������������������������
	//��������������������������������������������������������������������������������������������

	//----------------------------------------------
	//����������
	//----------------------------------------------
	void Task::Initialize()
	{
		//�e�J�[�h�Ƃ̋��������߂�
		float cdist = float(int((256 / 10) * size + 1) * 10);

		if (isUseCombo)
		{
			comboCardCnt = std::make_unique<CardCounter>(
				(int)Suit::Etc_RedNum + 0, startPos, endPos, size - 0.05f);
		}

		for (int i = 0; i < cardNum; ++i)
		{
			if (isRedScore)
			{
				scoreCardCnt[i] = std::make_unique<CardCounter>(
					(int)Suit::Etc_RedNum + 0,
					Math::Vec2((startPos.x + cdist) + (cdist * ((cardNum - 1) - i)), startPos.y),
					Math::Vec2((endPos.x + cdist) + (cdist * i), endPos.y), size);
			}
			else
			{
				scoreCardCnt[i] = std::make_unique<CardCounter>(
					0, Math::Vec2((startPos.x + cdist) + (cdist * ((cardNum - 1) - i)), startPos.y),
					Math::Vec2((endPos.x + cdist) + (cdist * i), endPos.y), size);
			}
		}
	}

	//----------------------------------------------
	//�I������
	//----------------------------------------------
	void Task::Finalize()
	{

	}

	//----------------------------------------------
	//�X�V
	//----------------------------------------------
	void Task::Update()
	{
		ScoreUpdate();

		timeCnt.Run();

		if (isUseCombo)	comboCardCnt->Update((int)Suit::Etc_RedNum + combo, true);
		
		for (int i = 0; i < cardNum; ++i)
		{
			if (timeCnt.GetNowCntTime() > 5 * i)
			{
				int numPlace = (int)powf(10.f, (float)(cardNum - 1 - i));
				if (isRedScore)
				{
					scoreCardCnt[i]->Update((int)Suit::Etc_RedNum + ((score / numPlace) % 10), true);
				}
				else
				{
					scoreCardCnt[i]->Update((score / numPlace) % 10, true);
				}
			}
		}
	}

	//----------------------------------------------
	//�`��
	//----------------------------------------------
	void Task::Draw()
	{
		if (isUseCombo)
		{
			comboCardCnt->Draw();
		}

		for (int i = 0; i < cardNum; ++i)
		{
			scoreCardCnt[i]->Draw();
		}
	}

	//----------------------------------------------
	//�X�R�A�̍X�V
	void Task::ScoreUpdate()
	{
		if (scoreFluctuation > 0)
		{
			score = std::min(score + (10 + (combo * 2)), 9999);	//�X�R�A�ő�l 9999
			if (isUseCombo) combo = std::min(combo + 1, 9);		//�R���{�ő�l 9
		}
		else if (scoreFluctuation < 0)
		{
			score = std::max(score - 10, 0);	//�X�R�A�ŏ��l 0
			combo = 0;
		}
	}

	//----------------------------------------------
	//�X�R�A�̎擾
	const int& Task::GetScore() const
	{
		return score;
	}
}