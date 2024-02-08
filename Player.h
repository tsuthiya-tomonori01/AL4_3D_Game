#pragma once

#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include <optional>

#include "BaseCharacter.h"

class Player : public BaseCharacter{

	public:
	void Initialize(const std::vector<Model*>& model) override;

	void Update() override;

	void Draw(const ViewProjection& viewProjectio) override;

	const WorldTransform& GetWorldTransform() { return worldTransform_; }

	void SetViewProjection(const ViewProjection* viewProjection) {
		viewProjection_ = viewProjection;
	}

	// 浮遊ギミック初期化
	void InitializeFloatingGimmick();

	// 浮遊ギミックに更新
	void UpdateFloatingGimmick();

	//通常行動初期化
	void BehaviorRootInitialize();

	//通常行動更新
	void BehaviorRootUpdate();

	//ジャンプ行動初期化
	void BehaviorJumpInitialize();

	//ジャンプ行動更新
	void BehaviorJumpUpdate();

private:

	WorldTransform worldTransformBody_;
	WorldTransform worldTransformHead_;
	WorldTransform worldTransformL_arm_;
	WorldTransform worldTransformR_arm_;

	Model* modelBody_;
	Model* modelHead_;
	Model* modelL_arm_;
	Model* modelR_arm_;

	const ViewProjection* viewProjection_ = nullptr;

	Vector3 velocity_ = {};

	float floatingParameter_ = 0.0f;

	enum class Behavior {
		kRoot,
		kJump,
	};

	/*enum class modeles_ {
		kModelIndexBody,
		kModelIndexHead,
		kModelIndexL_arm,
		kModelIndexR_arm,
	};*/

	Behavior behavior_ = Behavior::kRoot;

	bool playerFlag = true;

	std::optional<Behavior> behaviorRequest_ = std::nullopt;
};
