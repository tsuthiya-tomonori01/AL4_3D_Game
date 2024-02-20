#include "GameClear.h"

GameClear::GameClear() {}

GameClear::~GameClear() {

	delete spriteGC_;

	delete fadeIn_;
	delete fadeOut_;
}

void GameClear::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	textureHandleGC_ = TextureManager::Load("GameClear.png");
	spriteGC_ = Sprite::Create(textureHandleGC_, {0, 0});

	fadeIn_ = new FadeIn();
	fadeIn_->Initialize();

	fadeOut_ = new FadeOut();
	fadeOut_->Initialize();
}

void GameClear::Update() {

	

	fadeIn_->Update();

	/*fadeInColorGC_.w -= 0.005f;
	fadeSpriteGC_->SetColor(fadeInColorGC_);*/

	if (isSceneEnd == false) {

		if (Input::GetInstance()->GetJoystickState(0, joyState)) {
			Input::GetInstance()->GetJoystickStatePrevious(0, joyStatePre);
			if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_B &&
			    joyStatePre.Gamepad.wButtons != XINPUT_GAMEPAD_B) {

				FadeOutFlag = true;
			}
		}
	} 
	else 
	{
		isSceneEnd = false;
	}

	if (FadeOutFlag == true) {

		fadeOut_->Update();
	}

	if (fadeOut_->GetFadeOutColor().w >= 1.0) {

		isSceneEnd = true;
		FadeOutFlag = false;
		fadeIn_->Reset();
		fadeOut_->Reset();
	}

}

void GameClear::Draw() {

	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	Sprite::PreDraw(commandList);

	spriteGC_->Draw();

	fadeIn_->Draw();

	if (FadeOutFlag == true) 
	{
		fadeOut_->Draw();
	}

	Sprite::PostDraw();

}