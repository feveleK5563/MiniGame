#include "CardBehavior.h"
#include "SystemDefine.h"
#include "InputState.h"
#include "Task_GameCard.h"

//-----------------------------------------------------------------------------
//���S�J�[�h(�^�C�g�����)
CB_LogoCard::CB_LogoCard(const CardID& id, const Math::Vec2& pos):
	card(	id,
			pos,
			Math::Vec2(SystemDefine::windowSizeX / 2.f, SystemDefine::windowSizeY / 2.f),
			1.f, 1.f,
			0.f, (float)SystemDefine::OutputRandomRange(-5, 5, 1)[0]),
	progress(0)
{
	card.ChangeFrontBack();
}
bool CB_LogoCard::Update()
{
	bool endUpdate = card.Update(30.f);

	//�i�s�x�ɂ���ď�����ς���
	switch (progress)
	{
	case 0:	//���S�����S�Ɉړ�
			//�{�^�����������ʉ��ɏ�����
		if (Input::key[KEY_INPUT_S] == DOWN)
		{
			card.ChangeFrontBack();
		}
		if (Input::key[KEY_INPUT_SPACE] == DOWN ||
			Input::joypad1[PadInput::START] == DOWN)
		{
			++progress;
			card.SetEndMove(Math::Vec2(SystemDefine::windowSizeX / 2.f, SystemDefine::windowSizeY + 300.f),
							1.f,
							0.f);
		}
		break;

	case 1:
		//��ʉ��ɏ����������
		if (endUpdate)
		{
			return true;
		}
		break;
	}

	return false;
}
void CB_LogoCard::Draw()
{
	card.Draw();
}


//-----------------------------------------------------------------------------
//��D(�Q�[���{��)
CB_HandCard::CB_HandCard(const CardID& id, const Math::Vec2& pos, bool LorR) :
	card(id, pos, 1.4f, 0.f),
	LorR(LorR)
{
	if (LorR)
	{
		card.SetEndMove(Math::Vec2(240.f, SystemDefine::windowSizeY - 200.f),
						1.4f,
						0.f);
	}
	else
	{
		card.SetEndMove(Math::Vec2(SystemDefine::windowSizeX - 240.f, SystemDefine::windowSizeY - 200.f),
						1.4f,
						0.f);
	}
}
bool CB_HandCard::Update()
{
	card.Update(20.f);
	if ((LorR && (Input::key[KEY_INPUT_A] == DOWN || Input::joypad1[PadInput::LEFT] == DOWN)) ||
		(!LorR && (Input::key[KEY_INPUT_D] == DOWN || Input::joypad1[PadInput::B] == DOWN)))
	{
		GameCard::Task::Create(CardType::CenterCard, card.GetID(), card.GetPos(), 1.4f);
		return true;
	}

	return false;
}
void CB_HandCard::Draw()
{
	card.Draw();
}

//-----------------------------------------------------------------------------
//�����Ɉړ�����J�[�h
CB_CenterCard::CB_CenterCard(const CardID& id, const Math::Vec2& pos):
	card(	id,
			pos, Math::Vec2(SystemDefine::windowSizeX / 2.f, SystemDefine::windowSizeY / 2.f),
			1.4f, 1.f,
			0.f, (float)SystemDefine::OutputRandomRange(-5, 5, 1)[0]),
	progress(0)
{

}
bool CB_CenterCard::Update()
{
	switch (progress)
	{
	case 0:
		if (card.Update(10.f))
		{
			++progress;
		}
		break;

	case 1:
		break;
	}

	return false;
}
void CB_CenterCard::Draw()
{
	card.Draw();
}