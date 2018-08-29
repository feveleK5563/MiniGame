#pragma once
#include "TaskSystem.h"
#include "Task_GameTimer.h"
#include "Task_LogoCard.h"
#include "Task_HandCard.h"
#include "Task_CenterCard.h"
#include "GameDefine.h"
#include <array>

namespace CardJudge
{
	const std::string	defGroupName("�J�[�h����t");	//�O���[�v��
	const float			defPriority(0.f);			//�f�t�H���g�̏����D��x

	//----------------------------------------------
	class Task : public TaskAbstract
	{
	private:
		Mode mode;		//���݂̃Q�[�����[�h

		int centerCardNum;		//�����̃J�[�h����

		struct HandCardData
		{
			CardDestination destination;	//�J�[�h�̈ړ���
			std::shared_ptr<CardID> ID;		//��D�̃J�[�hID
		};
		std::array<HandCardData, 2> handCardData;	//��D���
		std::array<int, 2> scoreFluctuation;		//�e�v���C���[�̐���󋵂��i�[(�������Ă���+1, �Ԉ���Ă�����-1)

		std::shared_ptr<CardID> centerTopCard;	//���S�̐擪�J�[�h

		const GameState* gameState;	//���݂̃Q�[���i�s��
		

	public:
		Task(Mode mode);	//�R���X�g���N�^
		~Task();			//�f�X�g���N�^
		static std::shared_ptr<Task> Create(Mode mode);	//�^�X�N�̐���

		void Initialize();			//����������
		void Finalize() override;	//�I������
		void Update() override;		//�X�V
		void Draw() override;		//�`��

	private:
		//��D���쐬����(num��-1���߂̐���������Ƃ���Etc�J�[�h�����������)
		void CreateHandCard(Hand hand, bool isRight, int num);

		void Judge_SingleMode();	//�I��������D�ɂ���āA�X�R�A�̕ω��ƃG�t�F�N�g�̐������s��(SingleMode)
		void Judge_VSMode();		//�{�^�����͂ɂ���āA�X�R�A�̕ω��ƃG�t�F�N�g�̐������s��(VSMode)

		//�����Ƀ����_���ɃJ�[�h���쐬�A�ǉ�����
		void CreateRandomCard(Side side);
		//��D��ݒ肷��
		void SetNextHandCard(Hand hand, bool isRight);
		//����󋵂����Z�b�g����
		void ResetScoreFluctuation();
		//����𔻒f���A���ʂɉ����ăG�t�F�N�g�𔭐�������
		void CheckAndCreateEffect(CardDestination destination, Hand hand, Player player, const Math::Vec2& pos, const float& angle, const float& length);
		//���S�̃J�[�h�Ǝw�萔�����r���Đ���𔻒肷��
		bool CheckRightOrWrong(int num);

	public:
		const int& GetCenterCardNum() const;					//�����J�[�h�̖������擾
		const int& GetScoreFluctuation(Player player) const;	//�w�肵����̐���󋵂��擾
	};
}