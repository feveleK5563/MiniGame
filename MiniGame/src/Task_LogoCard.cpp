#include "Task_LogoCard.h"
#include "DxLib.h"
#include "SystemDefine.h"
#include "GameDefine.h"

namespace LogoCard
{
	//��������������������������������������������������������������������������������������������
	//��������������������������������������������������������������������������������������������

	//----------------------------------------------
	//�^�X�N�̃R���X�g���N�^
	Task::Task(const CardID& id, const Math::Vec2& pos):
		TaskAbstract(defGroupName, Priority::logoCard),
		card(id, pos, 1.f, (float)SystemDefine::GetRand(-5, 5)),
		progress(0)
	{
		if (card.GetID().side == Side::Back)
		{
			card.ChangeFrontBack();
			card.SetEndMove(
				Math::Vec2(SystemDefine::windowSizeX / 2.f, SystemDefine::windowSizeY / 2.f),
				1.f, (float)SystemDefine::GetRand(-5, 5));
		}
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
		bool endUpdate = card.Update(30.f);

		//�i�s�x�ɂ���ď�����ς���
		switch (progress)
		{
		case 0:	//���S�����S�Ɉړ�
				//�{�^�����������ʉ��ɏ�����
			if (SelectThrowCard())
			{
				card.ChangeFrontBack();
			}
			if (PushStart())
			{
				++progress;
				card.SetEndMove(Math::Vec2(SystemDefine::windowSizeX / 2.f, SystemDefine::windowSizeY + 300.f),
					1.f,
					0.f);
			}
			break;

		case 1:
			//��ʉ��ɏ����������
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