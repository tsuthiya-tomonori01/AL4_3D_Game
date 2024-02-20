#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Scene.h"
#include "Sprite.h"
#include "TextureManager.h"

class FadeOut {

public:
	FadeOut();

	~FadeOut();

	void Initialize();

	void Update();

	void Draw();

	void Reset();

	Vector4 GetFadeOutColor() { return fadeOutColor_; }

private:
	uint32_t textureHandleFadeOut_ = 0;

	Sprite* fadeOutSprite_ = nullptr;
	Vector4 fadeOutColor_ = {1.0f, 1.0f, 1.0f, 0.0f};
};
