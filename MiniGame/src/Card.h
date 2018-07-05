#pragma once
#include "Math.h"
#include "ImageDrawer.h"
#include "Resource_Card.h"
#include "EasingMover.h"

enum struct Suit
{
	Spade	= 0,	//�X�y�[�h
	Club	= 1,	//�N���u
	Heart	= 2,	//�n�[�g
	Diamond	= 3,	//�_�C��
	Etc		= 4,	//���̑�

	Back	= 54,	//��
};

enum struct Side
{
	Front,		//�\(�����̕`���Ă����)
	Back,		//��
	NextFront,	//������\�ւ̑J�ړr��
	NextBack,	//�\���痠�ւ̑J�ړr��
};

struct CardID
{
	Suit	suit;	//�X�[�g
	int		number;	//����
	Side	side;	//���\
	CardID();
	CardID(Suit suit, int number, Side side);
};

//�J�[�h�N���X
class Card
{
private:
	std::shared_ptr<CardR::Resource> res;	//�m�ۂ������\�[�X

	CardID		id;				//�J�[�h�̎���

	EasingMover	emover;			//�C�[�W���O�𗘗p��������
	float		scaleX;			//����(�߂��鏈���Ɏg�p����)
	ImageDrawer	imageDrawer;	//�`�揈������

public:
	//�R���X�g���N�^(�J�[�h�̎��ʁA���W�A�`��T�C�Y�A�p�x���w��)
	Card(const CardID& id, const Math::Vec2& pos, float scale, float degAngle);
	//�R���X�g���N�^(�J�[�h�̎��ʁA���W�̈ړ����A�`��T�C�Y�̕ύX���A�p�x�̕ύX�����w��)
	Card(	const CardID& id,
			const Math::Vec2& startPos, const Math::Vec2& endPos,
			float startScale,			float endScale,
			float startDegAngle,		float endDegAngle);

	//�X�V(�J�[�h���߂���I�������true��Ԃ�)
	bool Update();

	//�`��
	void Draw();

	//�J�[�h�̗��\��ύX����
	void ChangeFrontBack();

	//�J�[�h�̈ړ����ݒ肷��
	void SetEndPos(const Math::Vec2& endPos);

	//�J�[�h�̖ڕW�T�C�Y��ݒ肷��
	void SetEndSize(float endSize);

	//�J�[�h�̖ڕW�p�x��ݒ肷��
	void SetEndDegAngle(float endDegAngle);

private:
	//�J�[�h�̗��\���ɉ������J�[�h�߂��菈��(�I��������true��Ԃ�)
	bool TurnCard();
};