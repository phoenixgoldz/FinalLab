#pragma once
#include "PhysicsComponent.h"
#include "Physics/PhysicsSystem.h"

namespace phoenix
{
	struct Vector2;

	class RBPhysicsComponent : public PhysicsComponent
	{
	public:
		RBPhysicsComponent() = default;
		~RBPhysicsComponent();

		CLASS_DECLARATION(RBPhysicsComponent)

		void Initialize();

		void Update() override;
		virtual void ApplyForce(const Vector2& force);

		bool Write(const rapidjson::Value& value) const;
		bool Read(const rapidjson::Value& value);

		friend class CollisionComponent;

	private:
		PhysicsSystem::RigidBodyData data;
		b2Body* m_body = nullptr;

	};
















}