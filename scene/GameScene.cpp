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

	enemy_->SetTarget(&player_->GetWorldTransform());

	modelEnemy_1_.reset(Model::CreateFromOBJ("needle_Body", true));

	std::vector<Model*> modelEnemy_1 = {modelEnemy_1_.get()};

	enemy_1_ = std::make_unique<Enemy_1>();
	enemy_1_->Initialize(modelEnemy_1);

	modelEnemy_2_.reset(Model::CreateFromOBJ("needle_Body", true));

	std::vector<Model*> modelEnemy_2 = {modelEnemy_2_.get()};

	enemy_2_ = std::make_unique<Enemy_2>();
	enemy_2_->Initialize(modelEnemy_2);

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
	enemy_1_->Update();
	enemy_2_->Update();

	skydome_->Update();
	ground_->Update();

	CheckAllCollisions();

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

	if (player_->GetPlayerIsDead() == true) {

		isSceneEnd_1 = true;

		player_->Reset();
		enemy_->Reset();
		enemy_1_->Reset();
		enemy_2_->Reset();

		TimerReset();
	} 
	else
	{
		isSceneEnd_1 = false;
	}

	--GamePlayFlame_;

	if (GamePlayFlame_ <= 0) {

		isSceneEnd_2 = true;

		player_->Reset();
		enemy_->Reset();
		enemy_1_->Reset();
		enemy_2_->Reset();

		TimerReset();
	} 
	else 
	{
		isSceneEnd_2 = false;
	}
}

void GameScene::CheckAllCollisions() {

	Vector3 posA, posB;

	posA = player_->GetWorldPosition();
	posB = enemy_->GetWorldPosition();

	float a = posA.x - posB.x;
	float b = posA.y - posB.y;
	float c = posA.z - posB.z;
	float d = sqrt(a * a + b * b + c * c);

	if (d <= PlayerRadius + EnemyRadius) {

		player_->OnCollision();
		enemy_->OnCollision();
	}


	posA = player_->GetWorldPosition();
	posB = enemy_1_->GetWorldPosition();

	float a1 = posA.x - posB.x;
	float b1 = posA.y - posB.y;
	float c1 = posA.z - posB.z;
	float d1 = sqrt(a1 * a1 + b1 * b1 + c1 * c1);

	if (d1 <= PlayerRadius + EnemyRadius_1) {

		player_->OnCollision();
		enemy_1_->OnCollision();
	}


	posA = player_->GetWorldPosition();
	posB = enemy_2_->GetWorldPosition();

	float a2 = posA.x - posB.x;
	float b2 = posA.y - posB.y;
	float c2 = posA.z - posB.z;
	float d2 = sqrt(a2 * a2 + b2 * b2 + c2 * c2);

	if (d2 <= PlayerRadius + EnemyRadius_2) {

		player_->OnCollision();
		enemy_2_->OnCollision();
	}
}

void GameScene::TimerReset() {

	GamePlayFlame_ = 1200;

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
	enemy_1_->Draw(viewProjection_);
	enemy_2_->Draw(viewProjection_);

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



