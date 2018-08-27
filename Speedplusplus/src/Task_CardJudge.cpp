#include "Task_CardJudge.h"
#include <algorithm>
#include "DxLib.h"
#include "SystemDefine.h"
#include "Task_SceneTitle.h"
#include "SystemDefine.h"
#include "Task_JudgeEffect.h"
#include "Task_Sound.h"

#include <iostream>

namespace CardJudge
{
	//��������������������������������������������������������������������������������������������
	//��������������������������������������������������������������������������������������������

	//----------------------------------------------
	//�^�X�N�̃R���X�g���N�^
	Task::Task(Mode mode):
		TaskAbstract(defGroupName, defPriority),
		centerCardNum(0),
		mode(mode)
	{
	}
	//----------------------------------------------
	//�^�X�N�̃f�X�g���N�^
	Task::~Task()
	{

	}
	//----------------------------------------------
	//�^�X�N�̐���
	std::shared_ptr<Task> Task::Create(Mode mode)
	{
		std::shared_ptr<Task> task = std::make_shared<Task>(mode);
		TS::taskSystem.RegistrationTask(task);

		task->Initialize();
		return task;
	}

	//��������������������������������������������������������������������������������������������
	//��������������������������������������������������������������������������������������������

	//----------------------------------------------
	//����������
	//----------------------------------------------
	void Task::Initialize()
	{
		if (auto gt = TS::taskSystem.GetTaskOne<GameTimer::Task>(GameTimer::defGroupName))
		{
			gameState = &gt->GetGameState();
		}

		for (auto& it : handCardData)
		{
			it.destination = CardDestination::Out;
			it.ID = std::make_shared<CardID>(Suit::Etc, 0, Side::Front);
		}

		ResetScoreFluctuation();

		switch (mode)
		{
		case Mode::Single:
			break;

		case Mode::VS:
			CreateHandCard(Hand::Left, false, (int)Suit::Etc_1P);
			CreateHandCard(Hand::Right, false, (int)Suit::Etc_2P);
			break;

		default:
			return;
		}

		CreateRandomCard(Side::Back);
	}

	//----------------------------------------------
	//�I������
	//----------------------------------------------
	void Task::Finalize()
	{

	}

	//----------------------------------------------
	//�X�V
	//----------------------------------------------
	void Task::Update()
	{
		std::cout << centerTopCard->number << " " <<
			handCardData[(int)Hand::Left].ID->number << " " <<
			handCardData[(int)Hand::Right].ID->number << " " << std::endl;

		ResetScoreFluctuation();

		if (*gameState == GameState::Game)
		{
			//���͂���ɃX�R�A�̕ω��ƃG�t�F�N�g�̐������s��
			switch (mode)
			{
			case Mode::Single:
				Judge_SingleMode();
				break;

			case Mode::VS:
				Judge_VSMode();
				break;
			}
		}
	}

	//----------------------------------------------
	//�`��
	//----------------------------------------------
	void Task::Draw()
	{
		
	}

	//----------------------------------------------
	//��D���쐬����(num��-1���߂̐���������Ƃ���Etc�J�[�h�����������)
	void Task::CreateHandCard(Hand hand, bool isRight, int num)
	{
		CardID id;

		//�J�[�h�̏���ݒ�
		if (num <= -1)
		{
			SetNextHandCard(hand, isRight);
			id = *(handCardData[(int)hand].ID);
		}
		else
		{
			id = CardID(Suit::Etc, (int)num, Side::Back);
		}

		//��D�^�X�N�𐶐�
		HandCard::Task::Create(
			id,
			Math::Vec2(SystemDefine::windowSizeX / 2.f, SystemDefine::windowSizeY + 200.f),
			handCardData[(int)hand].destination,
			hand);
		handCardData[(int)hand].destination = CardDestination::Non;
	}

	//----------------------------------------------
	//�I��������D�ɂ���āA�X�R�A�̕ω��ƃG�t�F�N�g�̐������s��(SingleMode)
	void Task::Judge_SingleMode()
	{
		//��D���ړ�����ꍇ�͐V���ɐ�������
		if (handCardData[(int)Hand::Left].destination != CardDestination::Non &&
			handCardData[(int)Hand::Right].destination != CardDestination::Non)
		{
			int isRight = SystemDefine::GetRand(0, 2);
			switch (isRight)
			{
			case 0:
				CreateHandCard(Hand::Left, true, -1);
				CreateHandCard(Hand::Right, false, -1);
				break;

			case 1:
				CreateHandCard(Hand::Left, false, -1);
				CreateHandCard(Hand::Right, true, -1);
				break;

			case 2:
				CreateHandCard(Hand::Left, false, -1);
				CreateHandCard(Hand::Right, false, -1);
				break;
			}
		}

		//���������͖���
		if (Button::SelectLeftCardP1() && Button::SelectRightCardP1())
			return;

		//�p�X
		if (Button::SelectPassP1())
		{
			CheckAndCreateEffect(CardDestination::Out, Hand::Center, Player::Player1, 90.f, 200.f);
			CreateRandomCard(Side::Front);
			++centerCardNum;
			for (auto& it : handCardData)
			{
				it.destination = CardDestination::Out;
			}
			return;
		}

		//�J�[�h��
		if (Button::SelectLeftCardP1())
		{
			CheckAndCreateEffect(CardDestination::Center, Hand::Left, Player::Player1, -30.f, 400.f);
			centerTopCard = handCardData[(int)Hand::Left].ID;
			++centerCardNum;
			handCardData[(int)Hand::Left].destination = CardDestination::Center;
			handCardData[(int)Hand::Right].destination = CardDestination::Out;
			return;
		}

		//�J�[�h�E
		if (Button::SelectRightCardP1())
		{
			CheckAndCreateEffect(CardDestination::Center, Hand::Right, Player::Player1, 210.f, 400.f);
			centerTopCard = handCardData[(int)Hand::Right].ID;
			++centerCardNum;
			handCardData[(int)Hand::Left].destination = CardDestination::Out;
			handCardData[(int)Hand::Right].destination = CardDestination::Center;
			return;
		}
	}
	//----------------------------------------------
	//�{�^�����͂ɂ���āA�X�R�A�̕ω��ƃG�t�F�N�g�̐������s��(VSMode)
	void Task::Judge_VSMode()
	{
		if (handCardData[(int)Hand::Left].destination != CardDestination::Non)
		{
			//���J�[�h����
			CreateHandCard(Hand::Left, SystemDefine::GetRand(0, 1), -1);
		}
		if (handCardData[(int)Hand::Right].destination != CardDestination::Non)
		{
			//�E�J�[�h����
			CreateHandCard(Hand::Right, SystemDefine::GetRand(0, 1), -1);
		}

		//�J�[�h�������ȊO�������ꍇ
		if ((handCardData[(int)Hand::Left].ID->suit >= Suit::Etc) ||
			(handCardData[(int)Hand::Right].ID->suit >= Suit::Etc))
		{
			handCardData[(int)Hand::Left].destination = CardDestination::Out;
			handCardData[(int)Hand::Right].destination = CardDestination::Out;
			return;
		}

		bool selectP1 = Button::SelectLeftCardP1() || Button::SelectRightCardP1();
		bool selectP2 = Button::SelectLeftCardP2() || Button::SelectRightCardP2();

		//�v���C���[1�ƃv���C���[2�������ɓ��͂����ꍇ�͒e�����
		if (selectP1 && selectP2)
		{
			handCardData[(int)Hand::Left].destination = CardDestination::Bump;
			handCardData[(int)Hand::Right].destination = CardDestination::Bump;
			return;
		}

		//�v���C���[1
		if (selectP1)
		{
			//���S�ɃJ�[�h�𑗂�
			CheckAndCreateEffect(CardDestination::Center, Hand::Left, Player::Player1, 210.f, 400.f);
			centerTopCard = handCardData[(int)Hand::Left].ID;
			++centerCardNum;
			handCardData[(int)Hand::Left].destination = CardDestination::Center;
		}
		else if (Button::SelectPassP1())
		{
			//�p�X
			CheckAndCreateEffect(CardDestination::Out, Hand::Left, Player::Player1, 210.f, 400.f);
			handCardData[(int)Hand::Left].destination = CardDestination::Out;
		}

		//�v���C���[2
		if (selectP2)
		{
			//���S�ɃJ�[�h�𑗂�
			CheckAndCreateEffect(CardDestination::Center, Hand::Right, Player::Player2, -30.f, 400.f);
			centerTopCard = handCardData[(int)Hand::Right].ID;
			++centerCardNum;
			handCardData[(int)Hand::Right].destination = CardDestination::Center;
		}
		else if (Button::SelectPassP2())
		{
			//�p�X
			CheckAndCreateEffect(CardDestination::Out, Hand::Right, Player::Player2, -30.f, 400.f);
			handCardData[(int)Hand::Right].destination = CardDestination::Out;
		}
	}

	//----------------------------------------------
	//�����_���ɃJ�[�h���쐬�A�����ɒǉ�����
	void Task::CreateRandomCard(Side side)
	{
		std::shared_ptr<CardID> cardID = 
			std::make_shared<CardID>(
			Suit(SystemDefine::GetRand(0, 3)),
			SystemDefine::GetRand(0, 12),
			side);

		CenterCard::Task::Create(
			*cardID, Math::Vec2(SystemDefine::windowSizeX / 2.f, -200.f), false);

		centerTopCard= cardID;
	}

	//----------------------------------------------
	//�w�肵����D���Đݒ肷��
	void Task::SetNextHandCard(Hand hand, bool isRight)
	{
		//���S���w�肵��������ꍇ�͏������Ȃ�
		if (hand == Hand::Center)
			return;

		std::vector<std::shared_ptr<CardID>> right;	//�������i�[
		right.reserve(8);
		std::vector<std::shared_ptr<CardID>> wrong;	//�ԈႢ���i�[
		wrong.reserve(44);

		for (int s = 0; s < 4; ++s)
		{
			for (int n = 0; n < 13; ++n)
			{
				//�擪�J�[�h�A���݂̍��E��D�Ɠ����J�[�h�͏��O
				if ((centerTopCard->suit == Suit(s) && centerTopCard->number == n) ||
					(handCardData[(int)Hand::Left].ID->suit == Suit(s) && handCardData[(int)Hand::Left].ID->number == n) ||
					(handCardData[(int)Hand::Right].ID->suit == Suit(s) && handCardData[(int)Hand::Right].ID->number == n))
					continue;

				if (CheckRightOrWrong(n))
				{
					//�����̃J�[�h���i�[
					right.emplace_back(std::make_shared<CardID>(Suit(s), n, Side::Back));
				}
				else
				{
					//�ԈႢ�̃J�[�h���i�[
					wrong.emplace_back(std::make_shared<CardID>(Suit(s), n, Side::Back));
				}
			}
		}

		if (isRight)	//�����̃J�[�h��ݒ�
		{
			handCardData[(int)hand].ID = right[SystemDefine::GetRand(0, (int)right.size() - 1)];
		}
		else	//�ԈႢ�̃J�[�h��ݒ�
		{
			handCardData[(int)hand].ID = wrong[SystemDefine::GetRand(0, (int)wrong.size() - 1)];
		}
		//��D�̈ړ����𖳌��ɂ���
		handCardData[(int)hand].destination = CardDestination::Out;
	}
	//----------------------------------------------
	//����󋵂����Z�b�g����
	void Task::ResetScoreFluctuation()
	{
		for (auto& it : scoreFluctuation)
		{
			it = 0;
		}
	}
	//----------------------------------------------
	//����ɉ����ăG�t�F�N�g�𔭐�������
	void Task::CheckAndCreateEffect(CardDestination destination, Hand hand, Player player, const float& angle, const float& length)
	{
		bool rightORwrong;

		switch (destination)
		{
		case CardDestination::Out:
			switch (mode)
			{
			case Mode::Single:
				rightORwrong =	!CheckRightOrWrong(handCardData[(int)Hand::Left].ID->number) &&
								!CheckRightOrWrong(handCardData[(int)Hand::Right].ID->number);
				break;

			case Mode::VS:
				rightORwrong = !CheckRightOrWrong(handCardData[(int)hand].ID->number);
				break;
			}
			break;

		case CardDestination::Center:
			rightORwrong = CheckRightOrWrong(handCardData[(int)hand].ID->number);
			break;
		}

		float ang = angle + SystemDefine::GetRand(-20, 20);

		if (rightORwrong)
		{
			//����
			JudgeEffect::Task::Create(
				JEffect::Right, ang, length);
			scoreFluctuation[(int)player] = 1;
		}
		else
		{
			//�ԈႢ
			JudgeEffect::Task::Create(
				JEffect::Wrong, ang, length);
			scoreFluctuation[(int)player] = -1;

			auto sound = TS::taskSystem.GetTaskOne<Sound::Task>(Sound::defGroupName);
			sound->PlaySE_PaperTear(200);
		}
	}
	//----------------------------------------------
	//���S�̃J�[�h�Ǝ�D���r���Đ���𔻒肷��
	bool Task::CheckRightOrWrong(int num)
	{
		//����1��12�̃J�[�h�͐���
		return abs(centerTopCard->number - num) % 11 == 1;
	}

	//----------------------------------------------
	//�����J�[�h�̖������擾
	const int& Task::GetCenterCardNum() const
	{
		return centerCardNum;
	}

	//----------------------------------------------
	//����󋵂��擾
	const int& Task::GetScoreFluctuation(Player player) const
	{
		return scoreFluctuation[(int)player];
	}
}