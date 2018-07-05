#include "Card.h"
#include "DxLib.h"

CardID::CardID():
	suit(Suit::Spade),
	number(0),
	side(Side::Front){}

CardID::CardID(Suit suit, int number, Side side):
	suit(suit),
	number(number),
	side(side){}

//-----------------------------------------------------------------------------
//�R���X�g���N�^(�J�[�h�̎��ʁA���W�A�`��T�C�Y�A�p�x���w��)
Card::Card(const CardID& id, const Math::Vec2& pos, float scale, float degAngle):
	res(CardR::Resource::Create()),
	id(id),
	emover(pos, scale, degAngle),
	scaleX(1.f),
	imageDrawer(res->imageData, true){}

//-----------------------------------------------------------------------------
//�R���X�g���N�^(�J�[�h�̎��ʁA���W�̈ړ����A�`��T�C�Y�̕ύX���A�p�x�̕ύX�����w��)
Card::Card(	const CardID& id,
			const Math::Vec2& startPos, const Math::Vec2& endPos,
			float startScale, float endScale,
			float startDegAngle, float endDegAngle):
	res(CardR::Resource::Create()),
	id(id),
	emover(startPos, endPos, startScale, endScale, startDegAngle, endDegAngle),
	scaleX(1.f),
	imageDrawer(res->imageData, true) {}


//-----------------------------------------------------------------------------
//�X�V
bool Card::Update()
{
	emover.Update();
	return TurnCard();
}

//-----------------------------------------------------------------------------
//�`��
void Card::Draw()
{
	int showCard;
	if (id.side == Side::Back ||
		id.side == Side::NextFront)
	{
		showCard = static_cast<int>(Suit::Back);
	}
	else
	{
		showCard = static_cast<int>(id.suit) * 13 + id.number;
	}

	SetDrawMode(DX_DRAWMODE_BILINEAR);
	imageDrawer.DrawOne(
		emover.GetPos(),
		emover.GetScale() * 1.f * scaleX,
		emover.GetScale() * 1.f,
		emover.GetAngle(),
		false,
		showCard,
		Color(255, 255, 255, 255)
	);
	SetDrawMode(DX_DRAWMODE_NEAREST);
}

//-----------------------------------------------------------------------------
//�J�[�h�̗��\��ύX����
void Card::ChangeFrontBack()
{
	if (scaleX != 1.f)
		return;

	if (id.side == Side::Front)
	{
		id.side = Side::NextBack;
	}
	else if(id.side == Side::Back)
	{
		id.side = Side::NextFront;
	}
}

//-----------------------------------------------------------------------------
//�J�[�h�̈ړ����ݒ肷��
void Card::SetEndPos(const Math::Vec2& endPos)
{
	/*startPos = pos;
	diffPos = endPos - pos;*/
}

//-----------------------------------------------------------------------------
//�J�[�h�̍ő�T�C�Y��ݒ肷��
void Card::SetEndSize(float endSize)
{
	/*startScale = scale;
	diffScale = endSize - scale;*/
}


//-----------------------------------------------------------------------------
//�J�[�h�̗��\���ɉ������J�[�h�߂��菈��(�I��������true��Ԃ�)
bool Card::TurnCard()
{
	//�J�[�h���J��
	if (id.side == Side::Front ||
		id.side == Side::Back)
	{
		scaleX += 0.3f;

		if (scaleX >= 1.f)
		{
			scaleX = 1.f;
			return true;
		}
		return false;
	}

	//�J�[�h������
	scaleX -= 0.3f;
	if (scaleX <= 0.f)
	{
		scaleX = 0.f;
		if (id.side == Side::NextBack)
			id.side = Side::Back;
		else
			id.side = Side::Front;
	}
	return false;
}