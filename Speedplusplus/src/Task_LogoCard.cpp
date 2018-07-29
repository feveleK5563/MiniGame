#include "Task_LogoCard.h"
#include "DxLib.h"
#include "SystemDefine.h"
#include "GameDefine.h"
#include "Task_Sound.h"

namespace LogoCard
{
	//��������������������������������������������������������������������������������������������
	//��������������������������������������������������������������������������������������������

	//----------------------------------------------
	//�^�X�N�̃R���X�g���N�^
	Task::Task(const CardID& id, const Math::Vec2& pos):
		TaskAbstract(defGroupName, Priority::logoCard),
		card(id, pos, 1.f, (float)SystemDefine::GetRand(-5, 5)),
		progress(0),
		isBack(false)
	{
		if (card.GetID().side == Side::Back)
		{
			card.ChangeFrontBack(150);
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
		case 0:	//���S�����S�Ɉړ��A�{�^�����������ʉ��ɏ�����
			if (SelectThrowCard())
			{
				//�y�B���v�f�zW�L�[(LR)������������𔽓]
				card.ChangeFrontBack(150);
				isBack = !isBack;
			}
			if (PushStart())
			{
				auto sound = TS::taskSystem.GetTaskOne<Sound::Task>(Sound::defGroupName);
				sound->PlaySE_HandOut(200);

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

	//�J�[�h������������true��Ԃ�
	bool Task::GetIsBack() const
	{
		return isBack;
	}
}