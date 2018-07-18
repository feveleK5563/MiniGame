#pragma once
#include "TaskSystem.h"
#include "ImageLoader.h"
#include "ImageDrawer.h"
#include "EasingMover.h"

enum struct MessageType
{
	Ready	= 0,
	Finish	= 1,
	HiScore	= 2,
};

namespace GameMessage
{
	const std::string	defGroupName("�Q�[�����b�Z�[�W");	//�O���[�v��

	//----------------------------------------------
	class Resource
	{
	private:
		static std::weak_ptr<Resource> instance;
		std::string imageName;

	public:
		ImageData imageData;

		Resource();		//�R���X�g���N�^
		~Resource();	//�f�X�g���N�^
		static std::shared_ptr<Resource> Create();	//���\�[�X�̐���
	};

	//----------------------------------------------
	class Task : public TaskAbstract
	{
	private:
		std::shared_ptr<Resource> res;	//�m�ۂ������\�[�X
		EasingMover easeMover;
		ImageDrawer imageDrawer;

		MessageType type;
		TimeCounter waitTimeCnt;
		int progress;

	public:
		//�R���X�g���N�^
		Task(MessageType type, int waitTime);
		
		//�f�X�g���N�^
		~Task();
		
		//�^�X�N�̐���
		static std::shared_ptr<Task> Create(MessageType type, int waitTime);

		void Initialize();			//����������
		void Finalize() override;	//�I������
		void Update() override;		//�X�V
		void Draw() override;		//�`��
	};
}