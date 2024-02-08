#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	viewProjection_.Initialize();
	viewProjection_.farZ = 1600.0f;
	viewProjection_.UpdateMatrix();

	modelFighterBody_.reset(Model::CreateFromOBJ("float_Body", true));
	modelFighterHead_.reset(Model::CreateFromOBJ("float_Head", true));
	modelFighterL_arm.reset(Model::CreateFromOBJ("float_L_arm", true));
	modelFighterR_arm.reset(Model::CreateFromOBJ("float_R_arm", true));

	std::vector<Model*> modelPlayer = {
	    modelFighterBody_.get(), modelFighterHead_.get(), modelFighterL_arm.get(),
	    modelFighterR_arm.get()};

	player_ = std::make_unique<Player>();
	player_->Initialize(modelPlayer);

	modelEnemy_.reset(Model::CreateFromOBJ("needle_Body", true));

	std::vector<Model*> modelEnemy = {modelEnemy_.get()};

	enemy_ = std::make_unique<Enemy>();
	enemy_->Initialize(modelEnemy);

	followCamera_ = std::make_unique<FollowCamera>();
	followCamera_->Initialize();
	followCamera_->SetTarget(&player_->GetWorldTransform());

	player_->SetViewProjection(&followCamera_->GetViewProjection());

	modelSkydome_.reset(Model::CreateFromOBJ("skydome", true));

	skydome_ = std::make_unique<Skydome>();
	skydome_->Initialize(modelSkydome_.get());

	modelGround_.reset(Model::CreateFromOBJ("ground", true));

	ground_ = std::make_unique<Ground>();
	ground_->Initialize(modelGround_.get());
}

void GameScene::Update() {

	player_->Update(); 
	enemy_->Update();
	skydome_->Update();
	ground_->Update();

	if (isDebugCameraActive_) {
		debugCamera_->Update();

		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;

		viewProjection_.UpdateMatrix();
	} else 
	{
		followCamera_->Update();

		viewProjection_.matView = followCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = followCamera_->GetViewProjection().matProjection;

		viewProjection_.TransferMatrix();
	}

	if (isSceneEnd == false) {



	}

}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	player_->Draw(viewProjection_);
	enemy_->Draw(viewProjection_);
	skydome_->Draw(viewProjection_);
	ground_->Draw(viewProjection_);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
