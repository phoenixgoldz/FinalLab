#pragma once
#include "Framework/Component.h"
#include "Math/Vector2.h"

namespace phoenix
{
	class PhysicsComponent : public Component
	{
	public:
		PhysicsComponent() = default;

		CLASS_DECLARATION(PhysicsComponent)

		void Update() override;

		virtual void ApplyForce(const Vector2& force) { m_acceleration += force; }

		bool Write(const rapidjson::Value& value) const override;
		bool Read(const rapidjson::Value& value) override;

		Vector2 velocity;
		Vector2 m_acceleration;

		float damping = 1;

	};

}