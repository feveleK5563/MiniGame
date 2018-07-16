#pragma once
#include "TaskSystem.h"
#include "Task_GameTimer.h"
#include "Task_LogoCard.h"
#include "Task_HandCard.h"
#include "Task_CenterCard.h"

namespace CardJudge
{
	const std::string	defGroupName("�J�[�h����t");	//�O���[�v��
	const float			defPriority(0.f);			//�f�t�H���g�̏����D��x

	//----------------------------------------------
	class Task : public TaskAbstract
	{
	private:
		bool isHaveHandCard;	//��D�������Ă��邩�ǂ���
		int centerCardNum;		//�����̃J�[�h����
		std::pair<bool, std::shared_ptr<CardID>> handCard[2];	//��D
		std::vector<std::shared_ptr<CardID>> centerCardBundle;	//���S�̃J�[�h��

		std::shared_ptr<GameTimer::Task> gameTimer;	//�Q�[���i�s���Ǘ�����^�C�}�[

	public:
		Task();		//�R���X�g���N�^
		~Task();	//�f�X�g���N�^
		static std::shared_ptr<Task> Create();	//�^�X�N�̐���

		void Initialize();			//����������
		void Finalize() override;	//�I������
		void Update() override;		//�X�V
		void Draw() override;		//�`��

	private:
		void CreateHandCard();		//��D���쐬����
		void Judge();				//�I��������D�ɂ���āA�X�R�A�̕ω��ƃG�t�F�N�g�̐������s��

		//�����_���ɃJ�[�h���쐬�A�ǉ�����
		void CreateRandomCard(Side side);
		//��D��ݒ肷��
		void SetNextHandCard();
		//�G�t�F�N�g�𔭐�������
		void CreateEffect(float angle, float length, bool rw);

	public:
		const int* GetCenterCardNum() const;		//�����J�[�h�̖������擾
	};
}