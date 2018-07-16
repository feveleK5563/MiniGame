#include "Task_JudgeEffect.h"
#include "DxLib.h"
#include "SystemDefine.h"
#include "GameDefine.h"

namespace JudgeEffect
{
	std::weak_ptr<Resource> Resource::instance;
	//----------------------------------------------
	//���\�[�X�̃R���X�g���N�^
	Resource::Resource()
	{
		imageName = "JudgeEffect";
		Image::imageLoader.LoadDivImage(imageName, "data/image/Judge.png", 2, 2, 1, 336, 336);
		imageData = Image::imageLoader.GetImageData(imageName);
	}
	//----------------------------------------------
	//���\�[�X�̃f�X�g���N�^
	Resource::~Resource()
	{
		Image::imageLoader.DeleteImageData(imageName);
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
	Task::Task(JEffect je, float degAngle, float moveLength):
		TaskAbstract(defGroupName, Priority::judgeEffect),
		res(Resource::Create()),
		imageDrawer(res->imageData, true),
		easingMover(Math::Vec2(SystemDefine::windowSizeX / 2.f, SystemDefine::windowSizeY / 2.f),
					Math::Vec2(	SystemDefine::windowSizeX / 2.f + cos(Math::ToRadian(degAngle)) * moveLength,
								SystemDefine::windowSizeY / 2.f + sin(Math::ToRadian(degAngle)) * moveLength),
					1.f, 1.f,
					0.f, (float)SystemDefine::GetRand(-5, 5)),
		je(int(je)),
		progress(0),
		alpha(0.6f)
	{ 
	}
	//----------------------------------------------
	//�^�X�N�̃f�X�g���N�^
	Task::~Task()
	{

	}
	//----------------------------------------------
	//�^�X�N�̐���
	std::shared_ptr<Task> Task::Create(JEffect je, float degAngle, float moveLength)
	{
		std::shared_ptr<Task> task = std::make_shared<Task>(je, degAngle, moveLength);
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
			if (easingMover.Update(30.f))
			{
				++progress;
			}
			break;

		case 1:
			if (alpha <= 0.f)
			{
				KillMe();
			}
			else
			{
				alpha -= 0.1f;
			}
			break;
		}
	}

	//----------------------------------------------
	//�`��
	//----------------------------------------------
	void Task::Draw()
	{
		imageDrawer.DrawOne(
			easingMover.GetPos(),
			easingMover.GetScale(),
			easingMover.GetAngle(),
			false,
			je,
			Color(255, 255, 255, int(255 * alpha)));
	}
}