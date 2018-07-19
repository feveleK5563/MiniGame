#include "Task_CenterCard.h"
#include "DxLib.h"
#include "SystemDefine.h"
#include "GameDefine.h"
#include "Task_CardJudge.h"

namespace CenterCard
{
	//��������������������������������������������������������������������������������������������
	//��������������������������������������������������������������������������������������������

	//----------------------------------------------
	//�^�X�N�̃R���X�g���N�^
	Task::Task(const CardID& id, const Math::Vec2& pos):
		TaskAbstract(defGroupName, Priority::countCard),
		card(id,
			pos, Math::Vec2(SystemDefine::windowSizeX / 2.f, SystemDefine::windowSizeY / 2.f),
			1.3f, 1.f,
			0.f, (float)SystemDefine::GetRand(-5, 5)),
		progress(0),
		moveSpeed(15.f),
		centerCardNum(TS::taskSystem.GetTaskOne<CardJudge::Task>(CardJudge::defGroupName)->GetCenterCardNum()),
		cardOrder(centerCardNum),
		gameState(TS::taskSystem.GetTaskOne<GameTimer::Task>(GameTimer::defGroupName)->GetTimeState())
	{
	}
	//----------------------------------------------
	//�^�X�N�̃f�X�g���N�^
	Task::~Task()
	{

	}
	//----------------------------------------------
	//�^�X�N�̐���
	std::shared_ptr<Task> Task::Create(const CardID& id, const Math::Vec2& pos)
	{
		std::shared_ptr<Task> task = std::make_shared<Task>(id, pos);
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
		//�Q�[�����ɃJ�[�h�����Ԃ��Ă�����\�ɂ���
		if (card.GetID().side == Side::Back &&
			gameState == GameState::Game)
		{
			card.ChangeFrontBack();
		}

		bool isMoveEnd = card.Update(moveSpeed);
		switch (progress)
		{
		case 0:
			if (isMoveEnd)
			{
				++progress;
			}
			break;

		case 1:
			//���S��20���d�Ȃ�����폜
			if (centerCardNum - cardOrder > 30)
			{
				KillMe();
			}
			//(��)�^�C�g����ʈڍs���ɃJ�[�h����ʊO�֎U��΂点��
			if (gameState == GameState::End)
			{
				float angle = (float)SystemDefine::GetRand(0, 360);
				card.SetEndMove(
					card.GetPos() +
					Math::Vec2(	1000.f * cos(Math::ToRadian(angle)),
								1000.f * sin(Math::ToRadian(angle))),
					1.f,
					90.f
				);
				moveSpeed = 30.f;
				++progress;
			}
			break;

		case 2:
			if (isMoveEnd)
			{
				KillMe();
			}
			break;
		}
	}

	//----------------------------------------------
	//�`��
	//----------------------------------------------
	void Task::Draw()
	{
		card.Draw();
	}
}