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
	Task::Task():
		TaskAbstract(defGroupName, Priority::countCard),
		score(0),
		combo(0),
		timeCnt(-1),
		scoreFluctuation(TS::taskSystem.GetTaskOne<CardJudge::Task>(CardJudge::defGroupName)->GetScoreFluctuation())
	{
		comboCardCnt = std::make_unique<CardCounter>(
			(int)Suit::Etc_RedNum + 0, Math::Vec2(900.f, SystemDefine::windowSizeX + 100.f),
			Math::Vec2(895.f, 140.f), 0.25f);

		for (int i = 0; i < cardNum; ++i)
		{
			scoreCardCnt[i] = std::make_unique<CardCounter>(
				0,	Math::Vec2(980.f + (80 * ((cardNum - 1) - i)), -150.f),
					Math::Vec2(980.f + (80 * i), 130.f), 0.3f);
		}
	}
	//----------------------------------------------
	//�^�X�N�̃f�X�g���N�^
	Task::~Task()
	{

	}
	//----------------------------------------------
	//�^�X�N�̐���
	std::shared_ptr<Task> Task::Create()
	{
		std::shared_ptr<Task> task = 
			std::make_shared<Task>();
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

		comboCardCnt->Update((int)Suit::Etc_RedNum + combo, true);
		for (int i = 0; i < cardNum; ++i)
		{
			if (timeCnt.GetNowCntTime() > 5 * i)
			{
				int numPlace = (int)powf(10.f, (float)(cardNum - 1 - i));
				scoreCardCnt[i]->Update((score / numPlace) % 10, true);
			}
		}
	}

	//----------------------------------------------
	//�`��
	//----------------------------------------------
	void Task::Draw()
	{
		comboCardCnt->Draw();
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
			combo = std::min(combo + 1, 9);						//�R���{�ő�l 9
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