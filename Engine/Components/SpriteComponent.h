#pragma once
#include "Components/RenderComponent.h"
#include "Math/Rect.h"

namespace phoenix
{
	class Texture;

	class SpriteComponent : public RenderComponent
	{

	public:

		CLASS_DECLARATION(SpriteComponent)

		virtual void Update() override;
		virtual void Draw(Renderer& renderer) override;

		// Inherited via ISerializable
		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		std::shared_ptr<Texture> m_texture;

	};
}
