#include "FadeIn.h"

FadeIn::FadeIn() {}

FadeIn::~FadeIn() {

	delete fadeInSprite_; 
}

void FadeIn::Initialize() {

	textureHandleFadeIn_ = TextureManager::Load("fade.png");
	fadeInSprite_ = Sprite::Create(textureHandleFadeIn_, {0, 0});

}

void FadeIn::Update() {

	fadeInColor_.w -= 0.005f;
	fadeInSprite_->SetColor(fadeInColor_);
}

void FadeIn::Draw() {

	fadeInSprite_->Draw(); }

void FadeIn::Reset() {

	fadeInColor_ = {1.0f, 1.0f, 1.0f, 1.0f}; 
}
