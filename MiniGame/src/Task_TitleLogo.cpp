#include "Task_TitleLogo.h"
#include "DxLib.h"
#include "SystemDefine.h"
#include "InputState.h"

namespace TitleLogo
{
	//----------------------------------------------
	//�^�X�N�̃R���X�g���N�^
	Task::Task():
		TaskAbstract(defGroupName, defPriority),
		logoCard(	CardID(Suit::Etc, 0, Side::Front),
					Math::Vec2(SystemDefine::windowSizeX - 230.f, SystemDefine::windowSizeY - 150.f),
					Math::Vec2(SystemDefine::windowSizeX / 2.f, SystemDefine::windowSizeY / 2.f),
					1.5f, 1.f,
					0.f, 0.f)
	{
		Initialize();
	}
	//----------------------------------------------
	//�^�X�N�̃f�X�g���N�^
	Task::~Task()
	{

	}
	//----------------------------------------------
	//�^�X�N�̐���
	const std::shared_ptr<const Task> Task::Create()
	{
		std::shared_ptr<Task> task = std::make_shared<Task>();
		TS::taskSystem.RegistrationTask(task);

		return task;
	}

	//��������������������������������������������������������������������������������������������
	//��������������������������������������������������������������������������������������������

	//----------------------------------------------
	//����������
	//----------------------------------------------
	void Task::Initialize()
	{
		logoCard.ChangeFrontBack();
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
		logoCard.Update();
		if (Input::key[KEY_INPUT_S] == DOWN)
		{
			logoCard.ChangeFrontBack();
		}
	}

	//----------------------------------------------
	//�`��
	//----------------------------------------------
	void Task::Draw()
	{
		logoCard.Draw();
	}
}