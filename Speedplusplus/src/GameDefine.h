#pragma once

//�����D��x�܂Ƃ�
namespace Priority
{
	const float		backGround	(1.0f);	//�w�i
	const float		messageCard	(1.1f);	//���b�Z�[�W�J�[�h(���S�A���j���[���)
	const float		countCard	(1.2f);	//�v���p�J�[�h
	const float		centerCard	(1.3f);	//���S�̃J�[�h
	const float		judgeEffect	(1.4f);	//���ʃG�t�F�N�g
	const float		handCard	(1.5f);	//��D
	const float		ranking		(1.6f);	//�����L���O	
	const float		message		(1.7f);	//���b�Z�[�W	
}

//�Q�[�����[�h
enum struct Mode
{
	Non		= -1,	//����
	Single	= 0,	//�V���O���v���C
	VS		= 1,	//�ΐ�
};

//�E�����̃J�[�h
enum struct Hand
{
	Center	= -1,	//���S
	Left	= 0,	//����
	Right	= 1,	//�E��
};

//�J�[�h�̈ړ���
enum struct CardDestination
{
	Non,	//�ړ��Ȃ�
	Out,	//��ʊO(�ړ��������)
	Center,	//���S
	Bump,	//�J�[�h���m�̏Փ�
};

//�v���C���[
enum struct Player
{
	Player1	= 0,	//�v���C���[1
	Player2	= 1,	//�v���C���[2
};

//�{�^�����͂܂Ƃ�
namespace Button
{
	bool PushStartReset();		//�X�^�[�g�E���Z�b�g�I��

	bool SelectLeftCardP1();	//P1���J�[�h�I��
	bool SelectRightCardP1();	//P1�E�J�[�h�I��
	bool SelectPassP1();		//P1���p�X�I��

	bool SelectLeftCardP2();	//P2���J�[�h�I��
	bool SelectRightCardP2();	//P2�E�J�[�h�I��
	bool SelectPassP2();		//P2�p�X�I��
}