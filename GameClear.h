#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "TextureManager.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Scene.h"
#include "Sprite.h"

#include "FadeIn.h"
#include "FadeOut.h"

class GameClear {
public:

	GameClear();

	~GameClear();

	void Initialize();

	void Update();

	void Draw();

	bool IsSceneEnd() { return isSceneEnd; }
	SceneType NextScene() { return SceneType::kTitle; }

private:

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	Model* model_ = nullptr;

	bool isSceneEnd = false;

	bool FadeOutFlag = false;

	uint32_t textureHandleGC_ = 0;

	Sprite* spriteGC_ = nullptr;

	FadeIn* fadeIn_ = nullptr;
	FadeOut* fadeOut_ = nullptr;

	XINPUT_STATE joyState;
	XINPUT_STATE joyStatePre;
};
