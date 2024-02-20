#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Scene.h"
#include "Sprite.h"

#include "FadeOut.h"

class TitleScene {
public:

	TitleScene();

	~TitleScene();

	void Initialize();

	void Update();

	void Draw();

	void FadeReset();

	bool IsSceneEnd() { return isSceneEnd; }
	SceneType NextScene() { return SceneType::kGamePlay; }

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	Model* model_ = nullptr;

	bool isSceneEnd = false;

	bool FadeOutFlag = false;

	bool titleMoziFadeIn = false;

	FadeOut* fadeOut_ = nullptr;

	uint32_t textureHandle_ = 0;

	uint32_t textureHandleMozi_ = 0;

	Sprite* sprite_ = nullptr;

	Sprite* spriteM_ = nullptr;

	Vector4 fadeOutMoziColor_ = {1.0f, 1.0f, 1.0f, 0.0f};
};
