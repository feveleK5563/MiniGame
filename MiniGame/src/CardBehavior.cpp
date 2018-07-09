#include "CardBehavior.h"
#include "SystemDefine.h"
#include "InputState.h"
#include "Task_GameCard.h"
#include "Task_CardJudge.h"

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
	card(id, pos, 1.3f, 0.f),
	progress(0),
	LorR(LorR)
{
	if (LorR)
	{
		card.SetEndMove(Math::Vec2(200.f, SystemDefine::windowSizeY - 200.f),
						1.3f,
						-1.f);
	}
	else
	{
		card.SetEndMove(Math::Vec2(SystemDefine::windowSizeX - 200.f, SystemDefine::windowSizeY - 200.f),
						1.3f,
						1.f);
	}
}
bool CB_HandCard::Update()
{
	bool endUpdate = card.Update(20.f);

	switch (progress)
	{
	case 0:
		if ((Input::key[KEY_INPUT_A] == DOWN || Input::joypad1[PadInput::LEFT] == DOWN) &&
			(Input::key[KEY_INPUT_D] == DOWN || Input::joypad1[PadInput::B] == DOWN))
			break;

		//�Ή��������E�{�^�����������璆�S�Ɉړ�
		if ((LorR && (Input::key[KEY_INPUT_A] == DOWN || Input::joypad1[PadInput::LEFT] == DOWN)) ||
			(!LorR && (Input::key[KEY_INPUT_D] == DOWN || Input::joypad1[PadInput::B] == DOWN)))
		{
			GameCard::Task::Create(CardType::CenterCard, card.GetID(), card.GetPos(), 1.3f);
			return true;
		}
		//�t�����{�^�������������ʊO�Ɉړ�
		if ((!LorR && (Input::key[KEY_INPUT_A] == DOWN || Input::joypad1[PadInput::LEFT] == DOWN)) ||
			(LorR && (Input::key[KEY_INPUT_D] == DOWN || Input::joypad1[PadInput::B] == DOWN)))
		{
			if (LorR)
			{
				card.SetEndMove(Math::Vec2(-300.f, SystemDefine::windowSizeY - 200.f),
								1.3f, -90.f);
			}
			else
			{
				card.SetEndMove(Math::Vec2(SystemDefine::windowSizeX + 300.f, SystemDefine::windowSizeY - 200.f),
								1.3f, 90.f);
			}
			++progress;
		}
		break;

	case 1:
		if (endUpdate)
		{
			return true;
		}
		break;
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
			1.3f, 1.f,
			0.f, (float)SystemDefine::OutputRandomRange(-5, 5, 1)[0]),
	progress(0)
{
	if (auto ts = TS::taskSystem.GetTaskOne<CardJudge::Task>("�J�[�h����t"))
	{
		cardOrder = ts->GetCardNum();
	}
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
		if (auto ts = TS::taskSystem.GetTaskOne<CardJudge::Task>("�J�[�h����t"))
		{
			//���S��20���d�Ȃ�����폜
			if (ts->GetCardNum() - cardOrder > 20)
				return true;
		}
		break;
	}

	return false;
}
void CB_CenterCard::Draw()
{
	card.Draw();
}