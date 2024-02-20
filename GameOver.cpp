#include "GameOver.h"

GameOver::GameOver() {}

GameOver::~GameOver() {

	delete spriteGO_; 

	delete fadeIn_;
	delete fadeOut_;
}

void GameOver::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	textureHandleGO_ = TextureManager::Load("gameover.png");
	spriteGO_ = Sprite::Create(textureHandleGO_, {0, 0});

	fadeIn_ = new FadeIn();
	fadeIn_->Initialize();

	fadeOut_ = new FadeOut();
	fadeOut_->Initialize();
}

void GameOver::Update() {

	fadeIn_->Update();

	XINPUT_STATE joyState;
	XINPUT_STATE joyStatePre;

	if (isSceneEnd == false) {

		if (Input::GetInstance()->GetJoystickState(0, joyState)) {
			Input::GetInstance()->GetJoystickStatePrevious(0, joyStatePre);
			if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_B &&
			    joyStatePre.Gamepad.wButtons != XINPUT_GAMEPAD_B) {
				FadeInFlag = true;
			}
		}
	} 
	else 
	{
		isSceneEnd = false;
	}

	if (FadeInFlag == true) {

		fadeOut_->Update();
	}

	if (fadeOut_->GetFadeOutColor().w >= 1.0) {

		isSceneEnd = true;
		FadeInFlag = false;
		fadeIn_->Reset();
		fadeOut_->Reset();
	}
}

void GameOver::Draw() {

	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	Sprite::PreDraw(commandList);

	spriteGO_->Draw();

	fadeIn_->Draw();

	if (FadeInFlag == true) 
	{
		fadeOut_->Draw();
	}

	Sprite::PostDraw();

}
