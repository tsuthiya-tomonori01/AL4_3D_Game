#pragma once
#include "BaseCharacter.h"

class Enemy : public BaseCharacter{
public:

	void Initialize(const std::vector<Model*>& models) override;

	void Update() override;

	void Draw(const ViewProjection& viewProjection) override;

	void OnCollision();

	Vector3 GetWorldPosition();

	void Reset();

	void SetTarget(const WorldTransform* target) { target_ = target; }

private:

	WorldTransform worldTransformEnemy_;

	const WorldTransform* target_ = nullptr;

	ViewProjection* viewProjection_;

	
};
