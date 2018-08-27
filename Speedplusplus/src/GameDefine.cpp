#include "GameDefine.h"
#include "InputState.h"

namespace Button
{
	//�X�^�[�g�E���Z�b�g�I��
	bool PushStartReset()
	{
		return	Input::key[KEY_INPUT_SPACE] == DOWN ||
				Input::joypad1[PadInput::START] == DOWN;
	}

	//P1���J�[�h�I��
	bool SelectLeftCardP1()
	{
		return	Input::key[KEY_INPUT_A] == DOWN ||
				Input::joypad1[PadInput::LEFT] == DOWN;
	}
	//P1�E�J�[�h�I��
	bool SelectRightCardP1()
	{
		return	Input::key[KEY_INPUT_D] == DOWN ||
				Input::joypad1[PadInput::B] == DOWN;
	}
	//P1�p�X�I��
	bool SelectPassP1()
	{
		return	Input::key[KEY_INPUT_W] == DOWN ||
				Input::joypad1[PadInput::L1] == DOWN ||
				Input::joypad1[PadInput::R1] == DOWN;
	}

	//P2���J�[�h�I��
	bool SelectLeftCardP2()
	{
		return	Input::key[KEY_INPUT_LEFT] == DOWN ||
				Input::joypad2[PadInput::LEFT] == DOWN;
	}
	//P2�E�J�[�h�I��
	bool SelectRightCardP2()
	{
		return	Input::key[KEY_INPUT_RIGHT] == DOWN ||
				Input::joypad2[PadInput::B] == DOWN;
	}
	//P2�p�X�I��
	bool SelectPassP2()
	{
		return	Input::key[KEY_INPUT_UP] == DOWN ||
				Input::joypad2[PadInput::L1] == DOWN ||
				Input::joypad2[PadInput::R1] == DOWN;
	}
}