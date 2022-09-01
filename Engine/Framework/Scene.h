#pragma once
#include "Actor.h"
#include "Json.h"

#include <list>
#include <memory>

namespace phoenix
{
	class Actor;
	class Renderer;
	class Game;

	class Scene : public GameObject, public ISerializable
	{
	public:
		Scene() = default;
		Scene(Game* game) : m_game(game) {}

		Scene(const Scene& other) {}

		~Scene() = default;

		CLASS_DECLARATION(Scene)

			void Initialize();
		void Update();
		void Draw(Renderer& renderer);

		void RemoveAll();

		bool Write(const rapidjson::Value& value) const;
		bool Read(const rapidjson::Value& value);

		void Add(std::unique_ptr<Actor> actor);

		template<typename T>
		T* GetActor();

		template<typename T = Actor>
		T* GetActorFromName(const std::string& name);

		template<typename T = Actor>
		std::vector<T*> GetActorsFromTag(const std::string& tag);

		Game* GetGame() { return m_game; }

	private:
		std::list<std::unique_ptr<Actor>> m_actors;
		Game* m_game;
	};

	template<typename T>
	inline T* Scene::GetActor()
	{
		for (auto& actor : m_actors)
		{
			T* result = dynamic_cast<T*>(actor.get());
			if (result) return result;
		}
		return nullptr;
	}


	template<typename T>
	inline T* Scene::GetActorFromName(const std::string& name)
	{
		for (auto& actor : m_actors)
		{

			if (actor->GetName() == name)
			{
				return dynamic_cast<T*>(actor.get());

			}
		}
		return nullptr;
	}

	//template<typename t>
	//inline std::vector<t*> GetActorsFromTag(const std::string& tag)
	//{
	//	std::vector<T*> result;

	//	for(auto& tagactor : m_actors)// for loop (range based) through m_actors 
	//	{
	//		if (tagactor->GetName()==name)//  !! compare name to actor GetName()) 
	//			{
	//			 T * tagActor = dynamic_cast<T*>(//  !! get() actor pointer); 
	//			 if (tagActor.pushback()) //  !! push back tagActor to result vector 
	//				 }
	//	}

	//	return result;

	//}
}

