#pragma once
#include "TaskSystem.h"
#include "ImageDrawer.h"

namespace Back
{
	const std::string	defGroupName("�w�i");	//�O���[�v��
	const float			defPriority(1.f);		//�f�t�H���g�̏����D��x

	const int resourceNum = 2;
	//----------------------------------------------
	class Resource
	{
	private:
		static std::weak_ptr<Resource> instance;

	public:
		std::string	imageName[resourceNum];
		ImageData	imageData[resourceNum];

		Resource();		//�R���X�g���N�^
		~Resource();	//�f�X�g���N�^
		static std::shared_ptr<Resource> Create();	//���\�[�X�̐���
	};

	//----------------------------------------------
	class Task : public TaskAbstract
	{
	private:
		std::shared_ptr<Resource> res;	//�m�ۂ������\�[�X

		ImageDrawer imageBack;
		ImageDrawer imageFrame;

	public:
		Task();		//�R���X�g���N�^
		~Task();	//�f�X�g���N�^
		static std::shared_ptr<Task> Create();	//�^�X�N�̐���

		void Initialize();			//����������
		void Finalize() override;	//�I������
		void Update() override;		//�X�V
		void Draw() override;		//�`��
	};
}