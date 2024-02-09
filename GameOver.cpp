#include "GameOver.h"

GameOver::GameOver() {}

GameOver::~GameOver() {

	delete spriteGO_; 
}

void GameOver::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	textureHandleGO_ = TextureManager::Load("gameover.png");
	spriteGO_ = Sprite::Create(textureHandleGO_, {0, 0});

}

void GameOver::Update() {

	XINPUT_STATE joyState;
	XINPUT_STATE joyStatePre;

	if (isSceneEnd == false) {

		if (Input::GetInstance()->GetJoystickState(0, joyState)) {
			Input::GetInstance()->GetJoystickStatePrevious(0, joyStatePre);
			if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_B &&
			    joyStatePre.Gamepad.wButtons != XINPUT_GAMEPAD_B) {
				isSceneEnd = true;
			}
		}
	} 
	else 
	{
		isSceneEnd = false;
	}

}

void GameOver::Draw() {

	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	Sprite::PreDraw(commandList);

	spriteGO_->Draw();

	Sprite::PostDraw();

}
