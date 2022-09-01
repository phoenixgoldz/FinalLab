#include "Scene.h"
#include "Actor.h"
#include "Framework/Factory.h"
#include "Engine.h"

#include <iostream>
#include <algorithm>

namespace phoenix
{

	void Scene::Initialize()
	{
		for (auto& actor : m_actors) { actor->Initialize(); }
	}

	void Scene::Update()
	{
		auto iter = m_actors.begin();

		while (iter != m_actors.end())
		{
			(*iter)->Update();
			if ((*iter)->m_destroy)
			{
				iter = m_actors.erase(iter);
			}
			else
			{
				iter++;
			}
		}
		//check collision
		for (auto iter1 = m_actors.begin(); iter != m_actors.end(); iter1++)
		{
			for (auto iter2 = m_actors.begin(); iter2 != m_actors.end(); iter2++)
			{
				if (iter == iter2) continue;
				float radius = (*iter1)->GetRadius() + (*iter2)->GetRadius();
				float distance = (*iter1)->m_transform.position.Distance((*iter2)->m_transform.position);

				if (distance < radius)
				{
					(*iter1)->OnCollision((*iter2).get());
					(*iter2)->OnCollision((*iter1).get());

				}
			}
		}
	}

	void Scene::Draw(Renderer& renderer)
	{
		for (auto& actor : m_actors)
		{
			actor->Draw(renderer);
		}
	}

	void Scene::Add(std::unique_ptr<Actor> actor)
	{
		actor->m_scene = this;
		m_actors.push_back(std::move(actor));
	}

	void Scene::RemoveAll()
	{
		for (auto& actor : m_actors) { actor->SetDestroy(); }
		m_actors.clear();
	}
	bool Scene::Write(const rapidjson::Value& value) const
	{
		return true;
	}
	bool Scene::Read(const rapidjson::Value& value)
	{
		if (!value.HasMember("actors") || !value["actors"].IsArray())
		{
			return false;
		}
		//read actors
		for (auto& actorValue : value["actors"].GetArray())
		{
			std::string type;
			READ_DATA(actorValue, type);

			auto actor = Factory::Instance().Create<Actor>(type);
			if (actor) {
				//add actor
				actor->Read(actorValue);
				// error prefab cant locate key coin
				bool prefab = false;
				READ_DATA(actorValue, prefab);
				if (prefab)
				{
					std::string name = actor->GetName();
					Factory::Instance().RegisterPreFab(name, std::move(actor));

				}
				else
				{
					Add(std::move(actor));

				}

			}
		}
		return true;

	}

}