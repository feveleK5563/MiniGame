#pragma once

//�����D��x�܂Ƃ�
namespace Priority
{
	const float		backGround	(1.0f);	//�w�i
	const float		logoCard	(1.1f);	//���S�J�[�h
	const float		countCard	(1.2f);	//�v���p�J�[�h
	const float		centerCard	(1.3f);	//���S�̃J�[�h
	const float		judgeEffect	(1.4f);	//���ʃG�t�F�N�g
	const float		handCard	(1.5f);	//��D
	const float		ranking		(1.6f);	//�����L���O	
	const float		message		(1.7f);	//���b�Z�[�W	
}

bool SelectLeftCard();
bool SelectRightCard();
bool SelectThrowCard();