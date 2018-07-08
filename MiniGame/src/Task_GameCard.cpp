#include "Task_GameCard.h"
#include "DxLib.h"

namespace GameCard
{
	//��������������������������������������������������������������������������������������������
	//��������������������������������������������������������������������������������������������

	//----------------------------------------------
	//�^�X�N�̃R���X�g���N�^
	Task::Task(CardType cardType, const CardID& id, const Math::Vec2& pos, float priority):
		TaskAbstract(defGroupName, priority)
	{
		Initialize(cardType, id, pos);
	}
	//----------------------------------------------
	//�^�X�N�̃f�X�g���N�^
	Task::~Task()
	{

	}
	//----------------------------------------------
	//�^�X�N�̐���
	std::shared_ptr<Task> Task::Create(CardType cardType, const CardID& id, const Math::Vec2& pos, float priority)
	{
		std::shared_ptr<Task> task =
			std::make_shared<Task>(cardType, id, pos, priority);
		TS::taskSystem.RegistrationTask(task);

		return task;
	}

	//��������������������������������������������������������������������������������������������
	//��������������������������������������������������������������������������������������������

	//----------------------------------------------
	//����������
	//----------------------------------------------
	void Task::Initialize(CardType cardType, const CardID& id, const Math::Vec2& pos)
	{
		switch (cardType)
		{
		case CardType::LogoCard:		//���S�J�[�h
			cardBehavior = std::make_unique<CB_LogoCard>(id, pos);
			break;

		case CardType::HandCardLeft:	//�v���C���[����p�J�[�h��
			cardBehavior = std::make_unique<CB_HandCard>(id, pos, true);
			break;

		case CardType::HandCardRight:	//�v���C���[����p�J�[�h�E
			cardBehavior = std::make_unique<CB_HandCard>(id, pos, false);
			break;
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
		if (cardBehavior->Update())
		{
			KillMe();
		}
	}

	//----------------------------------------------
	//�`��
	//----------------------------------------------
	void Task::Draw()
	{
		cardBehavior->Draw();
	}
}