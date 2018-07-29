#include "Task_HandCard.h"
#include "DxLib.h"
#include "GameDefine.h"
#include "SystemDefine.h"
#include "Task_CenterCard.h"
#include "Task_Sound.h"
#include "Task_SceneGame.h"

namespace HandCard
{
	//��������������������������������������������������������������������������������������������
	//��������������������������������������������������������������������������������������������

	//----------------------------------------------
	//�^�X�N�̃R���X�g���N�^
	Task::Task(const CardID& id, const Math::Vec2& pos, bool LorR):
		TaskAbstract(defGroupName, Priority::handCard),
		card(id,
			pos,
			Math::Vec2(SystemDefine::windowSizeX / 2.f, SystemDefine::windowSizeY / 2.f),
			1.f, 1.f,
			0.f, (float)SystemDefine::GetRand(-5, 5)),
		progress(0),
		LorR(LorR),
		gameState(TS::taskSystem.GetTaskOne<GameTimer::Task>(GameTimer::defGroupName)->GetTimeState())
	{
		if (LorR)
		{
			card.SetEndMove(Math::Vec2(250.f, SystemDefine::windowSizeY - 200.f),
				1.3f,
				-1.f);
		}
		else
		{
			card.SetEndMove(Math::Vec2(SystemDefine::windowSizeX - 250.f, SystemDefine::windowSizeY - 200.f),
				1.3f,
				1.f);
		}
		card.ChangeFrontBack(100);
	}
	//----------------------------------------------
	//�^�X�N�̃f�X�g���N�^
	Task::~Task()
	{

	}
	//----------------------------------------------
	//�^�X�N�̐���
	std::shared_ptr<Task> Task::Create(const CardID& id, const Math::Vec2& pos, bool LorR)
	{
		std::shared_ptr<Task> task =
			std::make_shared<Task>(id, pos, LorR);
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
		bool endUpdate = card.Update(20.f);

		switch (progress)
		{
		case 0:
			//���������͖���
			if (SelectLeftCard() && SelectRightCard())
				break;

			//�Q�[���{�ҏI�������A
			//��{�^�����t�����{�^�������������ʊO�Ɉړ�
			if (SelectThrowCard() ||
				(!LorR && SelectLeftCard()) ||
				(LorR && SelectRightCard()) ||
				gameState != GameState::Game)
			{
				auto sound = TS::taskSystem.GetTaskOne<Sound::Task>(Sound::defGroupName);
				sound->PlaySE_HandOut(100);
				if (LorR)
				{
					card.SetEndMove(Math::Vec2(-300.f, SystemDefine::windowSizeY - 200.f),
						1.3f, -90.f);
				}
				else
				{
					card.SetEndMove(Math::Vec2(SystemDefine::windowSizeX + 300.f, SystemDefine::windowSizeY - 200.f),
						1.3f, 90.f);
				}
				++progress;
				return;
			}
			//�Ή��������E�{�^�����������璆�S�Ɉړ�����J�[�h���쐬����
			if ((LorR && SelectLeftCard()) ||
				(!LorR && SelectRightCard()))
			{
				if (TS::taskSystem.GetTaskOne<SceneGame::Task>(SceneGame::defGroupName)->GetIsBackMode())
				{
					CenterCard::Task::Create(card.GetID(), card.GetPos(), Side::Back);
				}
				else
				{
					CenterCard::Task::Create(card.GetID(), card.GetPos(), Side::Front);
				}
				KillMe();
			}
			break;

		case 1:
			if (endUpdate)
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