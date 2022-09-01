#pragma once
#include "Renderer.h"
#include "Resource/Resource.h"

#include <string>
#include <vector>

namespace phoenix
{
	struct Vector2;
	struct Color;

	class Model : public Resource
	{
	public:
		Model() = default;
		Model(const std::vector<Vector2>& points, const Color& color) :
			m_points{ points },
			m_color{ color } {}

		Model(const std::string& filename);

		void Draw(Renderer& renderer, const Vector2& position, float angle, const Vector2& scale =  Vector2{1,1});
		void Draw(Renderer& renderer, const Transform& transform);

		bool Load(const std::string& filename);

		float CalculateRadius();

		bool Create( std::string filename,...) override;

		float GetRadius() { return m_radius; }

		std::vector<Vector2> m_points{};

		Color m_color{ 0,0,0,0 };

		float m_radius = 0;
	};


}



