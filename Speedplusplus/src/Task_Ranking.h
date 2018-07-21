#pragma once
#include <array>
#include "TaskSystem.h"
#include "ImageDrawer.h"
#include "EasingMover.h"
#include "TimeCounter.h"

namespace Ranking
{
	const std::string	defGroupName("�����L���O");	//�O���[�v��
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

		static const int rankNum = 6;	//1��~5�� + �v���C���[�X�R�A
		struct RankData
		{
			int								rank;
			std::unique_ptr<EasingMover>	easeMove;
			int								score;
		};
		std::array<RankData, rankNum>	rankData;
		Math::Vec2						settingPos[rankNum];
		bool playSoundEffect[rankNum - 1];	//SE�Đ��t���O

		static const int scoreNum = 4;			//�X�R�A�̕\������
		Math::Vec2	rankRelativePos;			//���ʐ����̕\���ʒu(�o�[�Ƃ̑��΍��W)
		Math::Vec2	scoreRelativePos[scoreNum];	//�X�R�A�̕\���ʒu(�o�[�Ƃ̑��΍��W)

		TimeCounter moveTimeCnt;	//����̂��߂̎��Ԍo��
		int progress;				//�i�s�x

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

	private:
		bool AppRankMove();		//�����L���O�f�[�^�̏o������
		void LoadScoreData();	//�X�R�A�����L���O�̓ǂݍ���
		void WrightScoreData();	//�X�R�A�����L���O�̏�������
		void RankIn();			//�����N�ɓo�^����
	};
}