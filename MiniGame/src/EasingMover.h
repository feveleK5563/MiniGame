#pragma once
#include "Math.h"
#include "Easing.h"

class EasingMover
{
private:
	Easing		easing;			//�C�[�W���O

	Math::Vec2	pos;			//���W
	Math::Vec2	startPos;		//�J�n���̈ʒu
	Math::Vec2	diffPos;		//�ڕW�̈ʒu - �J�n���̈ʒu

	float		scale;			//�g�嗦(1.f�ŕW��)
	float		startScale;		//�J�n���̊g�嗦
	float		diffScale;		//�ڕW�̊g�嗦 - �J�n���̊g�嗦

	float		degAngle;		//�p�x(degree)
	float		startDegAngle;	//�J�n���̊p�x
	float		diffDegAngle;	//�ڕW�̊p�x - �J�n���̊p�x
	float		angle;			//�p�x

public:
	EasingMover(const Math::Vec2& pos, float scale, float degAngle);

	EasingMover(const Math::Vec2& startPos, const Math::Vec2& endPos,
				float startScale,			float endScale,
				float startDegAngle,		float endDegAngle);

	bool Update(float speed);

	const Math::Vec2&	GetPos() const;
	const float&		GetScale() const;
	const float&		GetAngle() const;

	void SetEndMove(const Math::Vec2& endPos, float endScale, float endDegAngle);
};