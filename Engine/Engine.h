#pragma once
#include "Serialization/Json.h" 

#include "Audio/AudioSystem.h"

#include "Core/File.h"
#include "Core/Memory.h"
#include "Core/Logger.h"
#include "Core/Time.h"

#include "Components/AudioComponent.h"
#include "Components/CameraComponent.h"
#include "Components/CollisionComponent.h"
#include "Components/CharacterComponent.h"
#include "Components/PlayerComponent.h"
#include "Components/ModelComponent.h"
#include "Components/PhysicsComponent.h"
#include "Components/RBPhysicisComponent.h"
#include "Components/RenderComponent.h"  
#include "Components/SpriteComponent.h"
#include "Components/SpriteAnimComponent.h"
#include "Components/TextComponent.h"
#include "Components/TilemapComponent.h"

#include "Framework/Game.h"
#include "Framework/Factory.h"
#include "Framework/Scene.h"
#include "Framework/Singleton.h"
#include "Framework/EventManager.h"

#include "Input/InputSystem.h"

#include "Math/MathUtils.h"
#include "Math/Random.h"

#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"
#include "Renderer/Texture.h"

#include "Resource/ResourceManager.h"

#include "Physics/PhysicsSystem.h"

#include <list>
#include <memory>
#include <vector>
#include <variant>

namespace phoenix
{
	extern Renderer g_renderer;
	extern InputSystem g_inputSystem;
	extern Time g_time;
	extern AudioSystem g_audioSystem;
	extern ResourceManager g_resources;
	extern PhysicsSystem g_physicsSystem;
	extern EventManager g_eventManager;

	class Engine : public Singleton<Engine>
	{
		public:
			void Register();

	};

}
