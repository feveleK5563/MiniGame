#pragma once
#include "TaskSystem.h"
#include <array>
#include "Card.h"
#include "GameDefine.h"

namespace Result_VSMode
{
	const std::string	defGroupName("���U���g(VS���[�h)");	//�O���[�v��
	const float			defPriority(Priority::handCard);	//�f�t�H���g�̏����D��x

	//----------------------------------------------
	class Task : public TaskAbstract
	{
	private:
		std::array<std::unique_ptr<Card>, 2> resultCard;

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