#pragma once
#include "RenderComponent.h"
#include <string>

namespace phoenix
{
	class Model;

	class ModelComponent : public RenderComponent
	{
	public:

		CLASS_DECLARATION(ModelComponent)

		void Update();

		void Draw(Renderer& renderer) override;

		bool Write(const rapidjson::Value& value) const;

		bool Read(const rapidjson::Value& value);

	public:
		std::shared_ptr<Model> m_model;
	};


}
