#include "FadeOut.h"

FadeOut::FadeOut() {}

FadeOut::~FadeOut() {

	delete fadeOutSprite_; 
}

void FadeOut::Initialize() {

	textureHandleFadeOut_ = TextureManager::Load("fade.png");
	fadeOutSprite_ = Sprite::Create(textureHandleFadeOut_, {0, 0});
}

void FadeOut::Update() {

	fadeOutColor_.w += 0.005f;
	fadeOutSprite_->SetColor(fadeOutColor_);
}

void FadeOut::Draw() {

	fadeOutSprite_->Draw(); 
}

void FadeOut::Reset() {

	fadeOutColor_ = {1.0f, 1.0f, 1.0f, 0.0f}; 
}
