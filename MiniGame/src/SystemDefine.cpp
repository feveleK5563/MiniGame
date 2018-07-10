#include "SystemDefine.h"

const int SystemDefine::windowSizeX = 1280;	//�E�B���h�E�T�C�YX
const int SystemDefine::windowSizeY = 720;	//�E�B���h�E�T�C�YY

//��ʊO����(�����ɉ摜�T�C�Y���w��A��ʊO�ɏo�Ă�����true)
bool SystemDefine::WindowOutBox(const Math::Box2D& hitBase)
{
	Math::Box2D windowBox(0, 0, windowSizeX, windowSizeY);
	return !windowBox.Hit(hitBase);
}

//��ʓ�����(�����ɉ摜�T�C�Y���w��A��ʓ��ɂ�����true)
bool SystemDefine::WindowInBox(const Math::Box2D& hitBase)
{
	Math::Box2D windowBox(0, 0, windowSizeX, windowSizeY);
	return windowBox.In(hitBase);
}

//���|�C���^�����S��delete����
template<class T>void SystemDefine::SafeDelete(T& t)
{
	if (t != nullptr)
	{
		delete t;
		t = nullptr;
	}
}

//���|�C���^�����S��delete����(�z���)
template<class T>void SystemDefine::SafeDeleteArr(T& t)
{
	if (t != nullptr)
	{
		delete[] t;
		t = nullptr;
	}
}

std::random_device SystemDefine::rd;
std::mt19937 SystemDefine::mtrand(rd());

//�͈͓��Ń����_���Ȓl���w������擾����
std::shared_ptr<int[]>  SystemDefine::OutputRandomRange(int lowerLimit, int upperLimit, int size)
{
	if (size <= 0) size = 1;

	std::shared_ptr<int[]> arr(new int[size] {});
	std::uniform_int_distribution<> randRange(lowerLimit, upperLimit);

	for (int i = 0; i < size; ++i)
	{
		arr[i] = randRange(mtrand);
	}

	return arr;
}