#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "TextureManager.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Scene.h"
#include "Sprite.h"

class FadeIn {

public:

	FadeIn();

	~FadeIn();

	void Initialize();

	void Update();

	void Draw();

	void Reset();

private:

	uint32_t textureHandleFadeIn_ = 0;

	Sprite* fadeInSprite_ = nullptr;
	Vector4 fadeInColor_ = {1.0f, 1.0f, 1.0f, 1.0f};

};
