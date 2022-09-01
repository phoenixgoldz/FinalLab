#pragma once
#include "Framework/Component.h"
#include "Framework/GameObject.h"
#include "Math/Transform.h"

#include <vector>

namespace phoenix
{
	class Scene;
	class Renderer;

	class Actor : public GameObject, public ISerializable
	{
	public:
		Actor() = default;
		Actor(const Actor& other);
		Actor(const Transform& transform) : m_transform{ transform } {}

		CLASS_DECLARATION(Actor)

		virtual void Initialize();

		virtual void Update() override;
		virtual void Draw(Renderer& renderer);

		// Inherited via ISerializable  
		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		void AddChild(std::unique_ptr<Actor> child);

		virtual void AddComponent(std::unique_ptr<Component> component);

		template<typename T>
		T* GetComponent();

		virtual void OnCollision(Actor* other) {}
		float GetRadius() { return 0; } 

		const std::string& GetTag() { return tag; }
		void SetTag(const std::string& tag) { this->tag = tag; }

		const std::string& GetName() { return name; }
		void SetName(const std::string& name) { this->name = name; }

		bool IsDestroy() { return m_destroy; }
		void SetDestroy(const bool& dest) { m_destroy = dest; }
		void SetDestroy() { m_destroy = true; }
		
		const bool IsActive() { return active; }
		void SetActive(const bool& activ) { active = activ; }
		void SetActive() { active = true; }


		Scene* GetScene() { return m_scene;  }

		friend class Scene;
		friend class Component;

		Transform m_transform;

		std::string name;
		std::string tag;
		bool active = true;

		bool m_destroy = false;

		Vector2 m_velocity;
		float m_damping = 1;

		float lifespan = 0;

		Scene* m_scene = nullptr;
		Actor* m_parent = nullptr;

		std::vector<std::unique_ptr<Component>> m_components;
		std::vector<std::unique_ptr<Actor>> m_children;

	};

	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& component : m_components)
		{
			T* result = dynamic_cast<T*> (component.get());
			if (result) return result;

		}
		return nullptr;
	}
}