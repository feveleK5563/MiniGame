#pragma once
#include <random>
#include <memory>
#include <vector>
#include "Math.h"

class SystemDefine
{
private:
	static std::random_device	rd;
	static std::mt19937			mtrand;

public:
	static const int windowSizeX;	//�E�B���h�E�T�C�YX
	static const int windowSizeY;	//�E�B���h�E�T�C�YY

	//��ʊO����(�����ɋ�`���w��A��ʊO�ɏo�Ă�����true)
	static bool WindowOutBox(const Math::Box2D& hitBase);
	//��ʓ�����(�����ɋ�`���w��A��ʓ��ɂ�����true)
	static bool WindowInBox(const Math::Box2D& hitBase);

	//���|�C���^�����S��delete����
	template<class T> static void SafeDelete(T& t);
	//���|�C���^�����S��delete����(�z���)
	template<class T> static void SafeDeleteArr(T& t);

	//�͈͓��Ń����_���Ȓl���w������擾����
	static std::shared_ptr<int[]> OutputRandomRange(int lowerLimit, int upperLimit, int size);
};