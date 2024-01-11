#pragma once
#include "BaseCharacter.h"

class Enemy : public BaseCharacter{
public:

	void Initialize(const std::vector<Model*>& models) override;

	void Update() override;

	void Draw(const ViewProjection& viewProjection) override;

private:

	WorldTransform worldTransformEnemy_;

	ViewProjection* viewProjection_;
};
