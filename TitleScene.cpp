#include "TitleScene.h"

void TitleScene::Initialize() {}

void TitleScene::Update() {

	XINPUT_STATE joyState;
	XINPUT_STATE joyStatePre;

	if (isSceneEnd == false) {

		if (Input::GetInstance()->GetJoystickState(0, joyState)) {
			Input::GetInstance()->GetJoystickStatePrevious(0, joyStatePre);
			if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_A &&
			    joyStatePre.Gamepad.wButtons != XINPUT_GAMEPAD_B) {
				isSceneEnd = true;
				
			}
		}
	}
}

void TitleScene::Draw() {

}
