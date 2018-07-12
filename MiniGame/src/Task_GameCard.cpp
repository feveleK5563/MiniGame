#include "Task_GameCard.h"
#include "DxLib.h"

namespace GameCard
{
	//��������������������������������������������������������������������������������������������
	//��������������������������������������������������������������������������������������������

	//----------------------------------------------
	//�^�X�N�̃R���X�g���N�^
	Task::Task():
		TaskAbstract(defGroupName, defPriority)
	{
	}
	//----------------------------------------------
	//�^�X�N�̃f�X�g���N�^
	Task::~Task()
	{

	}
	//----------------------------------------------
	//�^�X�N�̐���
	std::shared_ptr<Task> Task::Create(CardType cardType, const CardID& id, const Math::Vec2& pos)
	{
		std::shared_ptr<Task> task =
			std::make_shared<Task>();
		TS::taskSystem.RegistrationTask(task);

		task->Initialize(cardType, id, pos);
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
			priority = centerPriority;
			cardBehavior = std::make_unique<CB_LogoCard>(id, pos);
			break;

		case CardType::HandCardLeft:	//��D�p�J�[�h��
			cardBehavior = std::make_unique<CB_HandCard>(id, pos, true);
			break;

		case CardType::HandCardRight:	//��D�p�J�[�h�E
			cardBehavior = std::make_unique<CB_HandCard>(id, pos, false);
			break;

		case CardType::CenterCard:		//�����Ɉړ�����J�[�h
			priority = centerPriority;
			cardBehavior = std::make_unique<CB_CenterCard>(id, pos);
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