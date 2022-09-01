#include "PlayerComponent.h"
#include "Engine.h"
#include <iostream>

namespace phoenix {
	void PlayerComponent::Initialize()
	{
		CharacterComponent::Initialize();
	}

	void PlayerComponent::Update()
	{
		float thrust = 0;

		Vector2 direction = Vector2::zero;

		// set camera 
		auto camera = m_owner->GetScene()->GetActorFromName("Camera");
		if (camera)
		{
			camera->m_transform.position = m_owner->m_transform.position;
		}

		m_owner->m_transform.position += direction * 300 * g_time.deltaTime;
		//update transform with input controls
		if (g_inputSystem.GetKeyState(key_left) == InputSystem::KeyState::Held)
		{
			direction = Vector2::left;
		}

		if (g_inputSystem.GetKeyState(key_right) == phoenix::InputSystem::KeyState::Held)
		{
			direction = Vector2::right;
		}

		if (g_inputSystem.GetKeyState(key_up) == phoenix::InputSystem::KeyState::Held)
		{
			direction = Vector2::up;
		}

		if (g_inputSystem.GetKeyState(key_down) == phoenix::InputSystem::KeyState::Held)
		{
			direction = Vector2::down;
		}

		Vector2 velocity;
		auto component = m_owner->GetComponent<phoenix::PhysicsComponent>();
		if (component)
		{
			component->ApplyForce(direction * speed);
			velocity = component->velocity;
		}

			// apply attack sprite image and set to damage enemy
		if (g_inputSystem.GetKeyState(key_space) == InputSystem::KeyState::Pressed)
		{
			auto animComponent = m_owner->GetComponent<SpriteAnimComponent>();
			if (animComponent)
			{
				animComponent->SetSequence("Attack");
			}
		}


		auto animComponent = m_owner->GetComponent<SpriteAnimComponent>();
		if (animComponent)
		{
			if (velocity.x != 0) animComponent->SetflipHorizontal(velocity.x < 0);
			if (std::fabs(velocity.x) > 0)
			{
				animComponent->SetSequence("run");
			}
			else
			{
				animComponent->SetSequence("idle");
			}
		}
	}
}

bool phoenix::PlayerComponent::Write(const rapidjson::Value& value) const
{

	return true;
}

bool phoenix::PlayerComponent::Read(const rapidjson::Value& value)
{
	CharacterComponent::Read(value);
	READ_DATA(value, jump);

	return true;
}

void phoenix::PlayerComponent::OnNotify(const Event& event)
{
	if (event.name == "EVENT_DAMAGE")
	{
		health -= std::get<float>(event.data);

		if (health -= 0)
		{
			m_owner->SetDestroy();

			Event event;
			event.name = "EVENT_PLAYER_DEAD";

			g_eventManager.Notify(event);

		}

	}
}
int m_groundCount = 0;

void phoenix::PlayerComponent::OnCollisionEnter(Actor* other)
{
	if (other->GetName() == "Coin")
	{
		Event event;
		event.name = "EVENT_ADD_POINTS";
		event.data = 100;

		g_eventManager.Notify(event);
		other->SetDestroy();
	}

	if (other->GetTag() == "Enemy")
	{
		Event event;
		event.name = "EVENT_DAMAGE";
		event.data = damage;
		event.reciever = other;
	}
	if (other->GetTag() == "Ground")
	{
		m_groundCount++;
	}
}


void phoenix::PlayerComponent::OnCollisionExit(Actor* other)
{
	if (other->GetTag() == "Enemy")
	{
		Event event;
		event.name = "EVENT_DAMAGE";
		event.data = damage;
		event.reciever = other;
	}
	if (other->GetName() == "Coin")
	{
		Event event;
		event.name = "EVENT_ADD_POINTS";
		event.data = 100;

		g_eventManager.Notify(event);
		other->SetDestroy();
	}
	if (other->GetTag() == "Ground")
	{
		m_groundCount--;
	}




}

