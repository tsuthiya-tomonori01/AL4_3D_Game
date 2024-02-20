#include "TitleScene.h"
#include "TextureManager.h"

TitleScene::TitleScene() {}

TitleScene::~TitleScene() {

	delete fadeOut_; 

	delete sprite_;
	delete spriteM_;
}

void TitleScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	textureHandleMozi_ = TextureManager::Load("titelMozi.png");
	spriteM_ = Sprite::Create(textureHandleMozi_, {540, 200});

	textureHandle_ = TextureManager::Load("title.png");
	sprite_ = Sprite::Create(textureHandle_, {0, 0});

	fadeOut_ = new FadeOut();
	fadeOut_->Initialize();
}

void TitleScene::Update() {

	XINPUT_STATE joyState;
	XINPUT_STATE joyStatePre;

	if (isSceneEnd == false) {

		if (Input::GetInstance()->GetJoystickState(0, joyState)) {
			Input::GetInstance()->GetJoystickStatePrevious(0, joyStatePre);
			if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_B &&
			    joyStatePre.Gamepad.wButtons != XINPUT_GAMEPAD_B) {

				titleMoziFadeIn = true;
			}
		}
		if (Input::GetInstance()->GetJoystickState(0, joyState)) {
			Input::GetInstance()->GetJoystickStatePrevious(0, joyStatePre);
			if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_B && joyStatePre.Gamepad.wButtons !=
			        XINPUT_GAMEPAD_B && titleMoziFadeIn == true && fadeOutMoziColor_.w >= 1.0f) {

				FadeOutFlag = true;
			}
		}
	} 
	else 
	{
		isSceneEnd = false;
    }

	if (titleMoziFadeIn == true)
	{
		fadeOutMoziColor_.w += 0.005f;
		spriteM_->SetColor(fadeOutMoziColor_);

		if (fadeOutMoziColor_.w >= 1.0f) {

			fadeOutMoziColor_.w = 1.0f;
		}
	}

	if (FadeOutFlag == true) {

		fadeOut_->Update();
	}

	if (fadeOut_->GetFadeOutColor().w >= 1.0) {

		isSceneEnd = true;
		FadeOutFlag = false;
		fadeOut_->Reset();
		FadeReset();
	}
}

void TitleScene::Draw() {

	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	Sprite::PreDraw(commandList);

	sprite_->Draw();

	if (titleMoziFadeIn == true) 
	{
		spriteM_->Draw();
	}

	if (FadeOutFlag == true) {

		fadeOut_->Draw();
	}

	Sprite::PostDraw();

}

void TitleScene::FadeReset() {

	fadeOutMoziColor_ = {1.0f, 1.0f, 1.0f, 0.0f}; 
}
