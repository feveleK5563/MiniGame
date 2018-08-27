#pragma once
#include <array>
#include "TaskSystem.h"
#include "Card.h"
#include "GameDefine.h"

namespace MenuCard
{
	const std::string	defGroupName("���j���[��ʃJ�[�h");	//�O���[�v��

	//----------------------------------------------
	class Task : public TaskAbstract
	{
	private:
		Mode mode;	//�I�𒆂̃��[�h
		std::array<std::unique_ptr<Card>, 2> menuMessageCard;	//���j���[�p�J�[�h

		const int	seVolume;		//���ʉ��̉���
		Math::Vec2	centerPos;		//���S�̍��W
		Math::Vec2	startPos[2];	//�J�[�h�̊J�n�ʒu
		Math::Vec2	endPos[2];		//�J�[�h�̈ړ��I���ʒu

		int progress;			//�i�s�x
		TimeCounter timeCnt;	//���Ԍv��

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

		//���[�h�̎擾
		const Mode& GetMode();

	private:
		//���[�h�I��
		void SelectMode();
	};
}