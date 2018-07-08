#pragma once
#include "Card.h"

enum struct CardType
{
	LogoCard,
	HandCardLeft,
	HandCardRight,
	CenterCard,
};

class CardBehaviorAbstract
{
public:
	virtual ~CardBehaviorAbstract(){}
	virtual bool Update() = 0;
	virtual void Draw() = 0;
};

//-----------------------------------------------------------------------------
//���S�J�[�h�Ɏg�p���铮��(�w����W���璆�� �� ���������ʘg��)
class CB_LogoCard : public CardBehaviorAbstract
{
private:
	Card	card;		//�J�[�h���
	int		progress;	//�i�s�x

public:
	CB_LogoCard(const CardID& id, const Math::Vec2& pos);

	bool Update() override;
	void Draw() override;
};

//-----------------------------------------------------------------------------
//��D�Ɏg�p���铮��(�w����W�����ʍ��E�� �� �����ړ��J�[�h�𐶐����ď���)
class CB_HandCard : public CardBehaviorAbstract
{
private:
	Card	card;		//�J�[�h���
	bool	LorR;		//�����J�[�h�ʒu(�E������)

public:
	CB_HandCard(const CardID& id, const Math::Vec2& pos, bool LorR);

	bool Update() override;
	void Draw() override;
};

//-----------------------------------------------------------------------------
//�����Ɉړ�����J�[�h
class CB_CenterCard : public CardBehaviorAbstract
{
private:


public:
	CB_CenterCard(const Card& card);

	bool Update() override;
	void Draw() override;
};