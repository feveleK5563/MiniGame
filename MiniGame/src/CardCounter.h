#pragma once
#include "Card.h"

//�����J�[�h���g�p���������`��N���X
class CardCounter
{
private:
	Card card;
	int changeNumber;

public:
	//number��(int)Suit::RedNum�����Z����ƐԐ����ɂȂ�
	CardCounter(int number, const Math::Vec2& startPos, const Math::Vec2& endPos, float scale);
	bool Update(int number, bool isCntStart);	//0~9�̐������w��, false�ŃJ�E���g��~
	void Draw();
};