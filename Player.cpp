#include "Player.h"
#include "MathUtility.h"
#include <cassert>

#define _USE_MATH_DEFINES
#include <math.h>

void Player::Initialize(const std::vector<Model*>& models) {

	BaseCharacter::Initialize(models);

	worldTransformBody_.Initialize();
	worldTransformHead_.Initialize();
	worldTransformL_arm_.Initialize();
	worldTransformR_arm_.Initialize();

	worldTransformBody_.translation_.y = 0.0f;
	worldTransformHead_.translation_.y = 1.2f;

	worldTransformL_arm_.translation_.y = 1.25f;
	worldTransformL_arm_.translation_.x = -0.5f;

	worldTransformR_arm_.translation_.y = 1.25f;
	worldTransformR_arm_.translation_.x = 0.5f;

	InitializeFloatingGimmick();

	worldTransformBody_.parent_ = &worldTransform_;
	worldTransformHead_.parent_ = &worldTransformBody_;
	worldTransformL_arm_.parent_ = &worldTransformBody_;
	worldTransformR_arm_.parent_ = &worldTransformBody_;
}

void Player::Update() {
	if (behaviorRequest_) {

		behavior_ = behaviorRequest_.value();

		switch (behavior_) {
		case Behavior::kRoot:
		default:
			BehaviorRootInitialize();
			break;
		case Behavior::kJump:
			BehaviorJumpInitialize();
			break;
		}
		behaviorRequest_ = std::nullopt;
	}
	switch (behavior_) {
	case Behavior::kRoot:
	default:
		BehaviorRootUpdate();
		break;
	case Behavior::kJump:
		BehaviorJumpUpdate();
		break;
	}

	BaseCharacter::Update();
	worldTransformBody_.UpdateMatrix();
	worldTransformHead_.UpdateMatrix();
	worldTransformL_arm_.UpdateMatrix();
	worldTransformR_arm_.UpdateMatrix();
}

void Player::Draw(const ViewProjection& viewProjection) {

	models_[0]->Draw(worldTransformBody_, viewProjection);
	models_[1]->Draw(worldTransformHead_, viewProjection);
	models_[2]->Draw(worldTransformL_arm_, viewProjection);
	models_[3]->Draw(worldTransformR_arm_, viewProjection);
}

void Player::InitializeFloatingGimmick() { floatingParameter_ = 0.0f; }

void Player::UpdateFloatingGimmick() {

	// 浮遊移動のサイクル
	const uint16_t A_frame = 60;

	// 1フレームでのパラメーター加算値
	const float Step = (float)(2.0f * M_PI / A_frame);
	// static_cast<float>(2.0f* M_PI / A_frame);

	// パラメーターを1ステップ分加算
	floatingParameter_ += Step;

	// ２πを超えたら０に戻す
	floatingParameter_ = (float)std::fmod(floatingParameter_, 2.0f * M_PI);
	//
	const float Width_F = 0.25f;

	//
	worldTransformBody_.translation_.y = std::sin(floatingParameter_) * Width_F;
}

void Player::BehaviorRootInitialize() {}

void Player::BehaviorRootUpdate() {

	XINPUT_STATE joyState;

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {

		const float speed = 0.3f;

		velocity_ = {
		    (float)joyState.Gamepad.sThumbLX / SHRT_MAX, 0.0f,
		    (float)joyState.Gamepad.sThumbLY / SHRT_MAX};

		velocity_ = Multiply(speed, Normalize(velocity_));

		Matrix4x4 rotate = MakeRotateMatrix(viewProjection_->rotation_);

		// ここでカメラの角度分進ベクトルを回転させてる
		velocity_ = TransformNormal(velocity_, rotate);

		worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);

		worldTransform_.rotation_.y = std::atan2(velocity_.x, velocity_.z);
	}

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {

		if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_B) {

			behaviorRequest_ = Behavior::kJump;
		}
	}

	UpdateFloatingGimmick();

}

void Player::BehaviorJumpInitialize() {

	if (behavior_ == Behavior::kJump) {
		
		worldTransform_.translation_.y = 0;
		worldTransformL_arm_.rotation_.x = 0;
		worldTransformR_arm_.rotation_.x = 0;

		const float kJumpFirstSpeed = 3.0f;

		velocity_.y = kJumpFirstSpeed;
	}
}

void Player::BehaviorJumpUpdate() {

	if (behavior_ == Behavior::kJump) {

		worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);

		const float kGravityAcceleration = 0.25f;

		Vector3 accelerationVector = {0, -kGravityAcceleration, 0};

		velocity_ = Add(velocity_, accelerationVector);
	}

	if (worldTransform_.translation_.y <= 0.0f) {
		worldTransform_.translation_.y = 0;

		behaviorRequest_ = Behavior::kRoot;
	}
}

void Player::OnCollision() {

	PlayerIsDead = true;

}

Vector3 Player::GetWorldPosition() {

	Vector3 worldPos = {};

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Player::Reset() {

	PlayerIsDead = false;
	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};
}
