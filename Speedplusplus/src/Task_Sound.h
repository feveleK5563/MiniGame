#pragma once
#include "TaskSystem.h"

namespace Sound
{
	const std::string	defGroupName("�T�E���h");	//�O���[�v��
	const float			defPriority(0.f);			//�f�t�H���g�̏����D��x

	//----------------------------------------------
	class Resource
	{
	private:
		static std::weak_ptr<Resource> instance;

	public:
		int bgm;
		int se_turnOver;
		int se_handOut;
		int se_shaffle;
		int se_paperTear;

		Resource();		//�R���X�g���N�^
		~Resource();	//�f�X�g���N�^
		static std::shared_ptr<Resource> Create();	//���\�[�X�̐���
	};

	//----------------------------------------------
	class Task : public TaskAbstract
	{
	private:
		std::shared_ptr<Resource> res;	//�m�ۂ������\�[�X

	public:
		int bgm;
		int se_turnOver;
		int se_handOut;
		int se_shaffle;
		int se_paperTear;

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

		void PlayBGM() const;			//BGM�̍Đ�
		void PlaySE_TurnOver(int volume) const;		//SE(�J�[�h�߂���)�̍Đ�
		void PlaySE_HandOut(int volume) const;		//SE(�J�[�h������)�̍Đ�
		void PlaySE_Shaffle(int volume) const;		//SE(�V���b�t��)�̍Đ�
		void PlaySE_PaperTear(int volume) const;	//SE(���j��)�̍Đ�
	};
}