#include "Task_Ranking.h"
#include "DxLib.h"
#include "SystemDefine.h"

namespace Ranking
{
	std::weak_ptr<Resource> Resource::instance;
	//----------------------------------------------
	//���\�[�X�̃R���X�g���N�^
	Resource::Resource()
	{
		barName = "BarName";
		numName = "NumName";

		Image::imageLoader.LoadOneImage(barName, "data/image/ResultScoreBar.png");
		Image::imageLoader.LoadDivImage(numName, "data/image/ResultScoreNum.png", 20, 10, 2, 32, 40);
		barImg = Image::imageLoader.GetImageData(barName);
		numImg = Image::imageLoader.GetImageData(numName);
	}
	//----------------------------------------------
	//���\�[�X�̃f�X�g���N�^
	Resource::~Resource()
	{
		Image::imageLoader.DeleteImageData(barName);
		Image::imageLoader.DeleteImageData(numName);
	}
	//----------------------------------------------
	//���\�[�X�̐���
	std::shared_ptr<Resource> Resource::Create()
	{
		auto sp = instance.lock();
		if (!sp)
		{
			sp = std::make_shared<Resource>();
			instance = sp;
		}
		return sp;
	}

	//��������������������������������������������������������������������������������������������
	//��������������������������������������������������������������������������������������������

	//----------------------------------------------
	//�^�X�N�̃R���X�g���N�^
	Task::Task():
		TaskAbstract(defGroupName, defPriority),
		res(Resource::Create()),
		bar(res->barImg, false),
		number(res->numImg, true),
		moveTimeCnt(-1)
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
		for (int i = 0; i < rankNum; ++i)
		{
			rankScore[i] = i; //���X�R�A

			settingPos[i] = Math::Vec2(SystemDefine::windowSizeX - 400, 300 + (60 * i));

			easeMove[i] = std::make_unique<EasingMover>
				(Math::Vec2(SystemDefine::windowSizeX, settingPos[i].y), settingPos[i],
					1.f, 1.f, 0.f, 0.f);
		}

		rankRelativePos = Math::Vec2(30, 30);
		for (int i = 0; i < scoreNum; ++i)
		{
			scoreRelativePos[i] = Math::Vec2(100 + (i * 30), 30);
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
		moveTimeCnt.Run();
		for (int i = 0; i < rankNum; ++i)
		{
			if (moveTimeCnt.GetNowCntTime() > 10 * i)
			{
				easeMove[i]->Update(30.f);
			}
		}
	}

	//----------------------------------------------
	//�`��
	//----------------------------------------------
	void Task::Draw()
	{
		for (int i = 0; i < rankNum; ++i)
		{
			//�o�[
			bar.DrawOne(
				easeMove[i]->GetPos(),
				easeMove[i]->GetScale(),
				easeMove[i]->GetAngle(),
				false, 0,
				Color(255, 255, 255, 255));

			//�����N�̐���
			number.DrawOne(
				easeMove[i]->GetPos() + rankRelativePos,
				easeMove[i]->GetAngle(),
				easeMove[i]->GetScale(),
				false,
				10 + i,
				Color(255, 255, 255, 255));

			for (int j = 0; j < scoreNum; ++j)
			{
				//�X�R�A
				int numPlace = (int)powf(10.f, (float)(scoreNum - 1 - i));
				number.DrawOne(
					easeMove[i]->GetPos() + scoreRelativePos[j],
					easeMove[i]->GetAngle(),
					easeMove[i]->GetScale(),
					false,
					(rankScore[i] / numPlace) % 10,
					Color(255, 255, 255, 255));
			}
		}
	}
}