#include "ImageDrawer.h"
#include "DxLib.h"

Color::Color(): r(255), g(255), b(255), alpha(255){}

Color::Color(int r, int g, int b, int alpha): r(r), g(g), b(b), alpha(alpha){}

Color::Color(const Color& color): r(color.r), g(color.g), b(color.b), alpha(color.alpha){}

//-----------------------------------------------------------------------------

//コンストラクタ(描画したい画像データとループするか否かを指定)
ImageDrawer::ImageDrawer(const ImageData& imageData, const Math::Vec2& criterionPos):
	imageData(imageData),
	criterionPos(criterionPos),
	nowAnimPattern(0),
	nowAnimImage(0) {}

//アニメーションさせる
bool ImageDrawer::Run()
{
	nowAnimImage += 1.0f / imageData.anim[nowAnimPattern]->waitTime;

	if (int(nowAnimImage) > abs(imageData.anim[nowAnimPattern]->relativeSheet))
	{
		if (imageData.anim[nowAnimPattern]->isLoop)
		{
			nowAnimImage = 0;
		}
		else
		{
			nowAnimImage = fabsf((float)imageData.anim[nowAnimPattern]->relativeSheet);
		}
		return true;
	}

	return false;
}

//アニメーションパターン番号の変更
void ImageDrawer::ChangeAnimPattern(int pattern, bool isResetTime)
{
	nowAnimPattern = pattern;

	if (isResetTime == true)
	{
		nowAnimImage = 0;
	}
}

//描画する
void ImageDrawer::Draw(const Math::Vec2& pos, float scale, float angle, bool isTurn, const Color& color)
{
	SetDrawBright(color.r, color.g, color.b);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, color.alpha);

	int nai = (int)nowAnimImage;
	if (imageData.anim[nowAnimPattern]->relativeSheet < 0)
	{
		nai *= -1;
	}

	DrawRotaGraph2F(
		pos.x, pos.y,
		criterionPos.x, criterionPos.y,
		(double)scale,
		(double)angle,
		imageData.handle[imageData.anim[nowAnimPattern]->startSheet + nai],
		true,
		isTurn,
		false);

	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//指定番号の画像を描画する(アニメーションしない)
void ImageDrawer::DrawOne(const Math::Vec2& pos, float scale, float angle, bool isTurn, int imageSheet, const Color& color)
{
	SetDrawBright(color.r, color.g, color.b);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, color.alpha);

	DrawRotaGraph2F(
		pos.x, pos.y,
		criterionPos.x, criterionPos.y,
		(double)scale,
		(double)angle,
		imageData.handle[imageSheet],
		true,
		isTurn,
		false);

	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//画像データを取得
const ImageData& ImageDrawer::GetImageData() const
{
	return imageData;
}