#include "Task_Back.h"
#include "DxLib.h"
#include "ImageLoader.h"
#include "SystemDefine.h"

namespace Back
{
	std::weak_ptr<Resource> Resource::instance;
	//----------------------------------------------
	//���\�[�X�̃R���X�g���N�^
	Resource::Resource()
	{
		imageBack = "Back";
		Image::imageLoader.LoadOneImage(imageBack, "data/image/Back.png");
		imageDataBack = Image::imageLoader.GetImageData(imageBack);

		imageFrame = "CardFrame";
		Image::imageLoader.LoadOneImage(imageFrame, "data/image/CardFrame.png");
		imageDataFrame = Image::imageLoader.GetImageData(imageFrame);
	}
	//----------------------------------------------
	//���\�[�X�̃f�X�g���N�^
	Resource::~Resource()
	{
		Image::imageLoader.DeleteImageData(imageBack);
		Image::imageLoader.DeleteImageData(imageFrame);
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
		imageBack(res->imageDataBack, Math::Vec2(0, 0)),
		imageFrame(res->imageDataFrame, Math::Vec2(res->imageDataFrame.rect.w / 2.f, res->imageDataFrame.rect.h / 2.f))
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
		
	}

	//----------------------------------------------
	//�`��
	//----------------------------------------------
	void Task::Draw()
	{
		imageBack.DrawOne(
			Math::Vec2(0, 0),
			1.f,
			0.f,
			false,
			0,
			Color(255, 255, 255, 255)
		);

		imageFrame.DrawOne(
			Math::Vec2(SystemDefine::windowSizeX / 2.f, SystemDefine::windowSizeY / 2.f),
			8.f,
			0.f,
			false,
			0,
			Color(255, 255, 255, 255)
		);
	}
}