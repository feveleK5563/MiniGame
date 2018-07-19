#pragma once
#include "TaskSystem.h"
#include "ImageDrawer.h"
#include "EasingMover.h"
#include "TimeCounter.h"

namespace Ranking
{
	const std::string	defGroupName("�����L���O");	//�O���[�v��
	const float			defPriority(0.f);			//�f�t�H���g�̏����D��x

	//----------------------------------------------
	class Resource
	{
	private:
		static std::weak_ptr<Resource> instance;
		std::string barName;
		std::string numName;

	public:
		ImageData barImg;
		ImageData numImg;

		Resource();		//�R���X�g���N�^
		~Resource();	//�f�X�g���N�^
		static std::shared_ptr<Resource> Create();	//���\�[�X�̐���
	};

	//----------------------------------------------
	class Task : public TaskAbstract
	{
	private:
		std::shared_ptr<Resource> res;	//�m�ۂ������\�[�X
		ImageDrawer bar, number;

		static const int rankNum = 5;	//1��~5��
		int								rankScore[rankNum];
		std::unique_ptr<EasingMover>	easeMove[rankNum];
		Math::Vec2						settingPos[rankNum];

		static const int scoreNum = 4;			//�X�R�A�̕\������
		Math::Vec2	rankRelativePos;			//���ʐ����̕\���ʒu(�o�[�Ƃ̑��΍��W)
		Math::Vec2	scoreRelativePos[scoreNum];	//�X�R�A�̕\���ʒu(�o�[�Ƃ̑��΍��W)

		TimeCounter moveTimeCnt;	//����̂��߂̎��Ԍo��

	public:
		//�R���X�g���N�^
		Task();
		
		//�f�X�g���N�^
		~Task();
		
		//�^�X�N�̐���
		static std::shared_ptr<Task> Create();

		void Initialize();			//����������
		void Finalize() override;	//�I������
		void Update() override;		//�X�V
		void Draw() override;		//�`��
	};
}