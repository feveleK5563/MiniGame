#pragma once
#include "TaskSystem.h"
#include "Task_GameCard.h"

namespace CardJudge
{
	const std::string	defGroupName("�J�[�h����t");	//�O���[�v��
	const float			defPriority(0.f);			//�f�t�H���g�̏����D��x

	//----------------------------------------------
	class Task : public TaskAbstract
	{
	private:
		int progress;	//�i�s�x
		std::shared_ptr<CardID> handCard[2];					//��D
		std::vector<std::shared_ptr<CardID>> centerCardBundle;	//���S�̃J�[�h��

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
		void SetHandCard();			//�I��������D��o�^����

		//�����_���ɃJ�[�h��ǉ�����
		std::shared_ptr<CardID> RandomNextCard();
		//��D��ݒ肷��
		std::shared_ptr<CardID> ChoiceNextCard(bool isAnswerCard);

	public:
		int GetCardNum() const;		//���S�J�[�h�̖������擾
	};

	bool SelectLeftCard();
	bool SelectRightCard();
	bool SelectThrowCard();
}