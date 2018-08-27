#include "Task_HandCard.h"
#include "DxLib.h"
#include "SystemDefine.h"
#include "Task_CenterCard.h"
#include "Task_Sound.h"

namespace HandCard
{
	//��������������������������������������������������������������������������������������������
	//��������������������������������������������������������������������������������������������

	//----------------------------------------------
	//�^�X�N�̃R���X�g���N�^
	Task::Task(const CardID& id, const Math::Vec2& pos, const CardDestination& destination, Hand hand):
		TaskAbstract(defGroupName, Priority::handCard),
		card(id,
			pos,
			Math::Vec2(SystemDefine::windowSizeX / 2.f, SystemDefine::windowSizeY / 2.f),
			1.f, 1.f,
			0.f, (float)SystemDefine::GetRand(-5, 5)),
		progress(0),
		destination(destination),
		hand(hand),
		gameState(TS::taskSystem.GetTaskOne<GameTimer::Task>(GameTimer::defGroupName)->GetGameState())
	{
		
	}
	//----------------------------------------------
	//�^�X�N�̃f�X�g���N�^
	Task::~Task()
	{

	}
	//----------------------------------------------
	//�^�X�N�̐���
	std::shared_ptr<Task> Task::Create(const CardID& id, const Math::Vec2& pos, const CardDestination& destination, Hand hand)
	{
		std::shared_ptr<Task> task =
			std::make_shared<Task>(id, pos, destination, hand);
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
		switch (hand)
		{
		case Hand::Left:
			card.SetEndMove(Math::Vec2(250.f, SystemDefine::windowSizeY - 200.f),
				1.3f,
				-1.f);
			break;

		case Hand::Right:
			card.SetEndMove(Math::Vec2(SystemDefine::windowSizeX - 250.f, SystemDefine::windowSizeY - 200.f),
				1.3f,
				1.f);
			break;
		}

		card.ChangeFrontBack(100);
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
			if (Button::SelectLeftCardP1() && Button::SelectRightCardP1())
				break;

			if (gameState == GameState::End)
			{
				MoveOut();
				break;
			}

			switch (destination)
			{
			case CardDestination::Out:
				MoveOut();
				break;

			case CardDestination::Center:
				MoveCenter();
				break;

			case CardDestination::Bump:
				MoveBump();
				break;
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


	//----------------------------------------------
	//��ʊO�Ɉړ�����
	void Task::MoveOut()
	{
		//�Q�[���{�ҏI�������A
		//�p�X�{�^�����t�����{�^�������������ʊO�Ɉړ�
		auto sound = TS::taskSystem.GetTaskOne<Sound::Task>(Sound::defGroupName);
		sound->PlaySE_HandOut(100);
		switch (hand)
		{
		case Hand::Left:
			card.SetEndMove(Math::Vec2(-300.f, SystemDefine::windowSizeY - 200.f),
				1.3f, -90.f);
			break;

		case Hand::Right:
			card.SetEndMove(Math::Vec2(SystemDefine::windowSizeX + 300.f, SystemDefine::windowSizeY - 200.f),
				1.3f, 90.f);
			break;
		}
		++progress;
	}

	//----------------------------------------------
	//���S�Ɉړ�����J�[�h�𐶐�
	void Task::MoveCenter()
	{
		//�J�[�h�ړ���񂪒��S�ɂȂ����璆�S�Ɉړ�����J�[�h�𐶐����ď���
		CenterCard::Task::Create(card.GetID(), card.GetPos(), false);
		KillMe();
	}

	//----------------------------------------------
	//���t���[�����S�Ɉړ����ʊO�ֈړ�����J�[�h�𐶐�
	void Task::MoveBump()
	{
		CenterCard::Task::Create(card.GetID(), card.GetPos(), true);
		KillMe();
	}
}