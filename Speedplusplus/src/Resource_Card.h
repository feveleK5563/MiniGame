#pragma once
#pragma once
#include "ImageDrawer.h"

namespace CardR
{
	class Resource
	{
	private:
		static std::weak_ptr<Resource> instance;

	public:
		std::string	imageName;
		ImageData	imageData;

		Resource();		//�R���X�g���N�^
		~Resource();	//�f�X�g���N�^
		static std::shared_ptr<Resource> Create();	//���\�[�X�̐���
	};
}