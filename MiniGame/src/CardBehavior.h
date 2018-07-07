#pragma once
#include "Card.h"

enum struct CardType
{
	LogoCard,
};

class CardBehaviorAbstract
{
public:
	virtual ~CardBehaviorAbstract(){}
	virtual bool Update() = 0;
	virtual void Draw() = 0;
};

//-----------------------------------------------------------------------------
//���S�J�[�h(�^�C�g�����)
class CB_LogoCard : public CardBehaviorAbstract
{
private:
	Card	card;		//�J�[�h���
	int		progress;	//�i�s�x

public:
	CB_LogoCard();

	bool Update() override;
	void Draw() override;
};