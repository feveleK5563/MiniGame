#pragma once
#include "TaskSystem.h"
#include "EasingMover.h"
#include "ImageDrawer.h"

namespace JudgeEffect
{
	const std::string	defGroupName("���ʃG�t�F�N�g");	//�O���[�v��
	const float			defPriority(1.4f);				//�f�t�H���g�̏����D��x

	//----------------------------------------------
	class Resource
	{
	private:
		static std::weak_ptr<Resource> instance;

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

		int rw; //�������ԈႢ��
		ImageDrawer imageDrawer;
		EasingMover easingMover;

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