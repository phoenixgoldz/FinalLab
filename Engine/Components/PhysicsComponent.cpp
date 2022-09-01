#include "Engine.h"
#include "PhysicsComponent.h"

namespace phoenix
{

	void PhysicsComponent::Update()
	{
		velocity += m_acceleration * g_time.deltaTime;
		m_owner->m_transform.position += velocity * g_time.deltaTime;
		velocity *= damping;

		m_acceleration = Vector2::zero;

	}


	bool PhysicsComponent::Write(const rapidjson::Value& value) const
	{
		return false;
	}

	bool PhysicsComponent::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, damping);
		READ_DATA(value, velocity);
		READ_DATA(value, m_acceleration);

		return false;
	};

}