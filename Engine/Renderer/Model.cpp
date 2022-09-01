#include "Model.h"
#include "Core/File.h"
#include "Core/Logger.h"
#include "Framework/Actor.h"
#include "Math/MathUtils.h"
#include "Math/Transform.h"
#include "Math/Color.h"

#include <iostream>
#include <sstream>

using namespace std;

namespace phoenix
{
	Model::Model(const std::string& filename)
	{
		Load(filename);
		m_radius = CalculateRadius();
	}

	void Model::Draw(Renderer& renderer, const Vector2& position, float angle, const Vector2& scale)
	{
		//draw model
		for (int i = 0; i <m_points.size() - 1; i++)
		{
			Vector2 p1 = Vector2::Rotate((m_points[i] * scale), angle) + position;
			Vector2 p2 = Vector2::Rotate((m_points[static_cast<std::vector<phoenix::Vector2,
				std::allocator<phoenix::Vector2>>::size_type>(i) + 1] * scale), angle) + position;
			renderer.DrawLine(p1, p2, m_color);
		}
	}
	void Model::Draw(Renderer& renderer, const Transform& transform)
	{
		Matrix3x3 mx = transform.matrix;
		//if (m_points.size() == 0) return;

		for (size_t i = 0; i <m_points.size() - 1; i++)
		{
			Vector2 p1 = mx * m_points[i];
			Vector2 p2 = mx * m_points[i + 1];

			renderer.DrawLine(p1, p2, m_color);
		}
	}

	bool Model::Load(const string& filename)
	{
		std::string buffer;

		if (!phoenix::ReadFile(filename, buffer))
		{
			LOG("Error could not load model %s", filename.c_str());
			return false;
		}

		// read color 
		stringstream stream(buffer);
		//stream >> m_color;

		// read number of points 
		string line;
		getline(stream, line);
		size_t numPoints = stoi(line);

		// read model points 
		for (size_t i = 0; i < numPoints; i++)
		{
			Vector2 point;

			stream >> point;

			m_points.push_back(point);
		}
		return true;
	}

	float Model::CalculateRadius()
	{
		float radius = 0;

		//find the largest length
		for (auto& point : m_points)
		{
			if (point.Length() > radius) radius = point.Length();
		}

		return radius;
	}

	bool Model::Create(std::string filename, ...)
	{
		if (!Load(filename))
		{
			LOG("File unable to load\n");
				return false;
		}
		return true;
	}

}