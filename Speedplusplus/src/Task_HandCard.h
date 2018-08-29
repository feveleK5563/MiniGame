#pragma once
#include "TaskSystem.h"
#include "Card.h"
#include "Task_GameTimer.h"
#include "GameDefine.h"
#include "SystemDefine.h"

namespace HandCard
{
	const std::string	defGroupName("��D");	//�O���[�v��

	static const Math::Vec2 LeftSidePos(250.f, SystemDefine::windowSizeY - 200.f);
	static const Math::Vec2 RightSidePos(SystemDefine::windowSizeX - 250.f, SystemDefine::windowSizeY - 200.f);

	//----------------------------------------------
	class Task : public TaskAbstract
	{
	private:
		const GameState& gameState;	//�Q�[���̐i�s��
		Card	card;			//�J�[�h���
		int		progress;		//�i�s�x
		const CardDestination&	destination;	//�Ή�����J�[�h�̈ړ���
		Hand					hand;			//�����J�[�h�ʒu(�E������)

	public:
		//�R���X�g���N�^
		Task(const CardID& id, const Math::Vec2& pos, const CardDestination& destination, Hand hand);

		//�f�X�g���N�^
		~Task();
		
		//�^�X�N�̐���
		static std::shared_ptr<Task> Create(const CardID& id, const Math::Vec2& pos, const CardDestination& destination, Hand hand);

		void Initialize();			//����������
		void Finalize() override;	//�I������
		void Update() override;		//�X�V
		void Draw() override;		//�`��

		void MoveOut();		//��ʊO�Ɉړ�����
		void MoveCenter();	//���S�Ɉړ�����J�[�h�𐶐�
		void MoveBump();	//���t���[�����S�Ɉړ����ʊO�ֈړ�����J�[�h�𐶐�
	};
}