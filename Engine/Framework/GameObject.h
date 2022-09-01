#pragma once
#include "../Math/Transform.h"
#include "../Engine/Serialization/Serializable.h"

#define CLASS_DECLARATION(class) \
 std::unique_ptr<GameObject> Clone() override { return std::make_unique<class>(*this); }

#define REGISTER_CLASS(class) phoenix::Factory::Instance().Register<class>(#class)

namespace phoenix
{
	class GameObject
	{
	public:
		GameObject() = default;


		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual std::unique_ptr<GameObject> Clone() = 0;

	};

}
