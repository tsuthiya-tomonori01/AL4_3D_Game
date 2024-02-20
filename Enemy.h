#pragma once
#include "BaseCharacter.h"
#include "Player.h"

class Enemy : public BaseCharacter{
public:

	Enemy();

	~Enemy();

	void Initialize(const std::vector<Model*>& models) override;

	void Update() override;

	void Draw(const ViewProjection& viewProjection) override;

	void OnCollision();

	Vector3 GetWorldPosition();

	Vector3 SetWorldPosition();

	void Reset();

	void SetTarget(const WorldTransform* target) { target_ = target; }

	void SetEnemySpeed(Vector3 EnemySpeed);

private:

	WorldTransform worldTransformEnemy_;

	const WorldTransform* target_ = nullptr;

	ViewProjection* viewProjection_;
	
	Vector3 MoveEnemySpeed = {0.0f, 0.0f, 0.0f};


};
