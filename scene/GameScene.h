#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

#include "Player.h"
#include "Enemy.h"
#include "Enemy_1.h"
#include "Enemy_2.h"
#include "FollowCamera.h"

#include "FadeIn.h"
#include "FadeOut.h"

#include "Skydome.h"
#include "Ground.h"

#include <memory>
#include "DebugCamera.h"

#include "Scene.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void TimerReset();

	void CheckAllCollisions();

	//Vector4 GetFadeColor() { return fadeInColor_; }

	bool IsSceneEnd_1() { return isSceneEnd_1; }
	bool IsSceneEnd_2() { return isSceneEnd_2; }
	SceneType NextScene_1() { return SceneType::kGameOver; }
	SceneType NextScene_2() { return SceneType::kGameClear; }

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	std::unique_ptr<Player> player_;

	std::unique_ptr<Enemy> enemy_;

	std::unique_ptr<Enemy_1> enemy_1_;

	std::unique_ptr<Enemy_2> enemy_2_;

	std::unique_ptr<FollowCamera> followCamera_;

	std::unique_ptr<Skydome> skydome_;

	std::unique_ptr<Ground> ground_;

	FadeIn* fadeIn_ = nullptr;

	FadeOut* fadeOut_ = nullptr;

	DebugCamera* debugCamera_ = nullptr;
	WorldTransform worldTransform_;

	std::unique_ptr<Model> modelPlayer_;

	std::unique_ptr<Model> modelEnemy_;

	std::unique_ptr<Model> modelEnemy_1_;

	std::unique_ptr<Model> modelEnemy_2_;

	std::unique_ptr<Model> modelSkydome_;
	std::unique_ptr<Model> modelGround_;

	std::unique_ptr<Model> modelFighterBody_;
	std::unique_ptr<Model> modelFighterHead_;
	std::unique_ptr<Model> modelFighterL_arm;
	std::unique_ptr<Model> modelFighterR_arm;

	ViewProjection viewProjection_;

	bool isDebugCameraActive_ = false;

	bool isSceneEnd_1 = false;
	bool isSceneEnd_2 = false;

	int GamePlayFlame_ = 900;

	const float PlayerRadius = 0.7f;
	const float EnemyRadius = 0.7f;
	const float EnemyRadius_1 = 0.7f;
	const float EnemyRadius_2 = 0.7f;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
