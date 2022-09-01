#pragma once
#include "Framework/Component.h"
#include "Physics/Collision.h"
#include "Components/CharacterComponent.h"

namespace phoenix
{
	class PlayerComponent : public CharacterComponent
	{
	public:
		PlayerComponent() = default;
		CLASS_DECLARATION(PlayerComponent)

			void Initialize() override;
		void Update() override;

		// Inherited via CharacterComponent
		virtual void OnNotify(const Event& event) override;

		virtual void OnCollisionEnter(Actor* other) override;
		virtual void OnCollisionExit(Actor* other) override;

		virtual bool Write(const rapidjson::Value& value) const;
		virtual bool Read(const rapidjson::Value& value);

		float jump = 0;


	};

}

