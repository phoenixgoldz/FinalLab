#pragma once
#include "GameObject.h"

namespace phoenix
{
	class Actor;

	class Component : public GameObject, public ISerializable
	{
	public:
		Component() = default;
		~Component() = default;

		friend class Actor;

	protected:
		Actor* m_owner = nullptr;


		void Initialize() override;

		virtual void Update() = 0;



	};

}