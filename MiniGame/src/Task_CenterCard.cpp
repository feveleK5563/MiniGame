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
		progress(0)
	{
		if (auto ts = TS::taskSystem.GetTaskOne<CardJudge::Task>("�J�[�h����t"))
		{
			centerCardNum = ts->GetCenterCardNum();
			cardOrder = *centerCardNum;
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
		switch (progress)
		{
		case 0:
			if (card.Update(10.f))
			{
				++progress;
			}
			break;

		case 1:
			//���S��20���d�Ȃ�����폜
			if (*centerCardNum - cardOrder > 20)
				KillMe();
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