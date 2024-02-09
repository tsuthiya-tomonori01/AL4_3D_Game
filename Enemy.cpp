#include "Enemy.h"
#include "MathUtility.h"

#define _USE_MATH_DEFINES
#include <math.h>

void Enemy::Initialize(const std::vector<Model*>& models) {

	BaseCharacter::Initialize(models);

	worldTransformEnemy_.Initialize();

	worldTransform_.translation_.x = 0.0f;
	worldTransform_.translation_.y = 0.0f;
	worldTransform_.translation_.z = -20.0f;
}

void Enemy::Update() {

	BaseCharacter::Update();

	const float speed = 0.1f;

	worldTransform_.rotation_.y += 0.01f;

	Vector3 move = {0.0f, 0.0f, speed};

	Matrix4x4 matRotY = MakeRotateYMatrix(worldTransform_.rotation_.y);

	move = TransformNormal(move, matRotY);

	worldTransform_.translation_ = Add(move,worldTransform_.translation_);

	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection) {

	models_[0]->Draw(worldTransform_, viewProjection);

}

void Enemy::OnCollision() {}

Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos = {};

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Enemy::Reset() {

	worldTransform_.translation_ = {0.0f, 0.0f, -25.0f};

}
