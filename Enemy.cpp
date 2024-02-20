#include "Enemy.h"
#include "MathUtility.h"

#define _USE_MATH_DEFINES
#include <math.h>

Enemy::Enemy() {}

Enemy::~Enemy() {

}

void Enemy::Initialize(const std::vector<Model*>& models) {

	BaseCharacter::Initialize(models);

	worldTransformEnemy_.Initialize();

	worldTransform_.translation_.x = 200.0f;
	worldTransform_.translation_.y = 0.0f;
	worldTransform_.translation_.z = 200.0f;
}

void Enemy::Update() {

	BaseCharacter::Update();

	const Vector3 EnemySpeed = {0.5f, 0.0f, 0.5f};

	MoveEnemySpeed = Normalize(MoveEnemySpeed);

	MoveEnemySpeed = Add(MoveEnemySpeed, EnemySpeed);

	worldTransform_.translation_ = Add(worldTransform_.translation_, MoveEnemySpeed); 

	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection) {

	models_[0]->Draw(worldTransform_, viewProjection);
}

void Enemy::OnCollision() {

	MoveEnemySpeed = {0.0f, 0.0f, 0.0f}; 
}

Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos = {};

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

Vector3 Enemy::SetWorldPosition() { return Vector3(); }

void Enemy::Reset() {

	worldTransform_.translation_ = {200.0f, 0.0f, 200.0f};

}

void Enemy::SetEnemySpeed(Vector3 EnemySpeed) { 
	this->MoveEnemySpeed = EnemySpeed;
}
