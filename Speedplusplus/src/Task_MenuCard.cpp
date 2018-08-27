#include "Task_MenuCard.h"
#include "DxLib.h"
#include "GameDefine.h"
#include "SystemDefine.h"
#include "Task_Sound.h"

namespace MenuCard
{
	//��������������������������������������������������������������������������������������������
	//��������������������������������������������������������������������������������������������

	//----------------------------------------------
	//�^�X�N�̃R���X�g���N�^
	Task::Task():
		TaskAbstract(defGroupName, Priority::messageCard),
		mode(Mode::Non),
		seVolume(150),
		progress(0),
		timeCnt(0)
	{

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
		centerPos = Math::Vec2(SystemDefine::windowSizeX / 2.f, SystemDefine::windowSizeY / 2.f);
		startPos[0] = Math::Vec2(300.f, -200.f);
		startPos[1] = Math::Vec2(SystemDefine::windowSizeX - 300.f, SystemDefine::windowSizeY + 200.f);
		endPos[0] = Math::Vec2(300.f, SystemDefine::windowSizeY / 2.f);
		endPos[1] = Math::Vec2(SystemDefine::windowSizeX - 300.f, SystemDefine::windowSizeY / 2.f);

		menuMessageCard[(int)Mode::Single] =
			std::make_unique<Card>(CardID(Suit::Etc, (int)Suit::Etc_SingleMode, Side::Back),
				startPos[0],
				1.f,
				0.f);

		menuMessageCard[(int)Mode::VS] =
			std::make_unique<Card>(CardID(Suit::Etc, (int)Suit::Etc_VSMode, Side::Back),
				startPos[1],
				1.f,
				0.f);

		for (int i = 0; i < (int)menuMessageCard.size(); ++i)
		{
			menuMessageCard[i]->ChangeFrontBack(seVolume);
			menuMessageCard[i]->SetEndMove(
				endPos[i],
				1.f,
				(float)SystemDefine::GetRand(-5, 5));
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
		bool endMove = true;
		for (int i = 0; i < (int)menuMessageCard.size(); ++i)
		{
			endMove = menuMessageCard[i]->Update(30.f) && endMove;
		}

		switch (progress)
		{
		case 0:
			if (endMove)
			{
				SelectMode();
			}
			break;

		case 1:
			timeCnt.Run();
			if (timeCnt.IsTimeEnd())
			{
				for (int i = 0; i < (int)menuMessageCard.size(); ++i)
				{
					menuMessageCard[i]->ChangeFrontBack(seVolume);
					menuMessageCard[i]->SetEndMove(
						startPos[i],
						1.f,
						(float)SystemDefine::GetRand(-5, 5));
				}
				++progress;
			}
			break;

		case 2:
			if (endMove)
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
		for (int i = 0; i < (int)menuMessageCard.size(); ++i)
		{
			menuMessageCard[i]->Draw();
		}
	}

	//------------------------------------
	//���[�h�̎擾
	const Mode& Task::GetMode()
	{
		return mode;
	}

	//------------------------------------
	//���[�h�I��
	void Task::SelectMode()
	{
		//��(��l�v���C)�I��
		if (Button::SelectLeftCardP1() ||
			Button::SelectLeftCardP2())
		{
			if (mode != Mode::Single)
			{
				mode = Mode::Single;
				if (menuMessageCard[(int)Mode::Single]->GetID().side != Side::Front)
					menuMessageCard[(int)Mode::Single]->ChangeFrontBack(seVolume);
				if (menuMessageCard[(int)Mode::VS]->GetID().side != Side::Back)
					menuMessageCard[(int)Mode::VS]->ChangeFrontBack(seVolume);
			}
		}
		//�E(��l�v���C)�I��
		else if (Button::SelectRightCardP1() ||
				 Button::SelectRightCardP2())
		{
			if (mode != Mode::VS)
			{
				mode = Mode::VS;
				if (menuMessageCard[(int)Mode::VS]->GetID().side != Side::Front)
					menuMessageCard[(int)Mode::VS]->ChangeFrontBack(seVolume);
				if (menuMessageCard[(int)Mode::Single]->GetID().side != Side::Back)
					menuMessageCard[(int)Mode::Single]->ChangeFrontBack(seVolume);
			}
		}

		//����
		if (Button::PushStartReset())
		{
			switch (mode)
			{
			case Mode::Single:
				menuMessageCard[(int)Mode::Single]->SetEndMove(
					centerPos,
					1.f,
					(float)SystemDefine::GetRand(-5, 5));
				menuMessageCard[(int)Mode::VS]->SetEndMove(
					startPos[(int)Mode::VS],
					1.f,
					0.f);
				break;

			case Mode::VS:
				menuMessageCard[(int)Mode::VS]->SetEndMove(
					centerPos,
					1.f,
					(float)SystemDefine::GetRand(-5, 5));
				menuMessageCard[(int)Mode::Single]->SetEndMove(
					startPos[(int)Mode::Single],
					1.f,
					0.f);
				break;

			case Mode::Non:
				return;
			}
			++progress;
			TS::taskSystem.GetTaskOne<Sound::Task>(Sound::defGroupName)->PlaySE_HandOut(200);
			timeCnt.SetEndTime(60);
		}
	}
}