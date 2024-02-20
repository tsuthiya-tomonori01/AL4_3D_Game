#include "Enemy_2.h"

#include "MathUtility.h"

#define _USE_MATH_DEFINES
#include <math.h>

void Enemy_2::Initialize(const std::vector<Model*>& models) {

	BaseCharacter::Initialize(models);

	worldTransformEnemy_.Initialize();

	worldTransform_.translation_.x = 0.0f;
	worldTransform_.translation_.y = 0.0f;
	worldTransform_.translation_.z = 20.0f;
}

void Enemy_2::Update() {

	BaseCharacter::Update();

	const float speed = 0.1f;

	worldTransform_.rotation_.y += 0.01f;

	Vector3 move = {0.0f, 0.0f, speed};

	Matrix4x4 matRotY = MakeRotateYMatrix(worldTransform_.rotation_.y);

	move = TransformNormal(move, matRotY);

	worldTransform_.translation_ = Add(move, worldTransform_.translation_);

	worldTransform_.UpdateMatrix();

}

void Enemy_2::Draw(const ViewProjection& viewProjection) {

	models_[0]->Draw(worldTransform_, viewProjection);

}

void Enemy_2::OnCollision() {}

Vector3 Enemy_2::GetWorldPosition() {

	Vector3 worldPos = {};

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Enemy_2::Reset() {

	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = { 25.0f, 0.0f, 0.0f }; 
}
