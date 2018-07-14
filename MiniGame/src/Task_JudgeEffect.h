#pragma once
#include "TaskSystem.h"
#include "EasingMover.h"
#include "ImageDrawer.h"

enum struct JEffect
{
	Right = 0,
	Wrong = 1,
	//Fever = 2,
};

namespace JudgeEffect
{
	const std::string	defGroupName("���ʃG�t�F�N�g");	//�O���[�v��

	//----------------------------------------------
	class Resource
	{
	private:
		static std::weak_ptr<Resource> instance;

	public:
		ImageData imageData;
		std::string imageName;

		Resource();		//�R���X�g���N�^
		~Resource();	//�f�X�g���N�^
		static std::shared_ptr<Resource> Create();	//���\�[�X�̐���
	};

	//----------------------------------------------
	class Task : public TaskAbstract
	{
	private:
		std::shared_ptr<Resource> res;	//�m�ۂ������\�[�X

		int je; //�\������G�t�F�N�g�̎��
		ImageDrawer imageDrawer;
		EasingMover easingMover;

		int progress;	//�i�s�x
		float alpha;	//�A���t�@�l

	public:
		Task(JEffect je, float degAngle, float moveLength);		//�R���X�g���N�^
		~Task();				//�f�X�g���N�^
		static std::shared_ptr<Task> Create(JEffect je, float degAngle, float moveLength);	//�^�X�N�̐���

		void Initialize();			//����������
		void Finalize() override;	//�I������
		void Update() override;		//�X�V
		void Draw() override;		//�`��
	};
}