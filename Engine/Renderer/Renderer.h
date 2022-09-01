#pragma once
#include "Texture.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Math/Matrix3x3.h"

struct SDL_Renderer;
struct SDL_Window;

namespace phoenix
{
	struct Transform; //forward declaration	
	struct Rect;


	class Renderer
	{
	public:
		Renderer() = default;
		~Renderer() = default;


		void Initialize();

		void Draw(std::shared_ptr<Texture> texture, const Vector2& position, float angle = 0, const Vector2& scale = Vector2{ 1,1 },
			const Vector2& registration = Vector2{ 0.5f,0.5f });

		void Draw(std::shared_ptr<Texture> texture, const Rect& source, const Transform transform, const Vector2& registration = Vector2{ 0.5f, 0.5f }, bool flipH = false);

		void Draw(std::shared_ptr<Texture> texture, const Transform transform,
			const Vector2& registration = Vector2{ 0.5f,0.5f });

		void Shutdown();

		void CreateWindow(const char* name, int width, int height);

		void SetClearColor(const Color& color) { m_clearColor = color; }

		void BeginFrame();
		void EndFrame();

		void DrawLine(float x1, float y1, float x2, float y2);
		void DrawLine(const Vector2& v1, const Vector2& v2, const Color& color);

		void DrawPoint(float x, float y);
		void DrawPoint(const Vector2& v, const Color& color);


		void SetViewMatrix(const Matrix3x3& view) { m_view = view; }
		void SetViewportMatrix(const Matrix3x3& viewport) { m_viewport = viewport; }

		int GetWidth() { return m_width; }
		int GetHeight() { return m_width; }

		SDL_Renderer* m_renderer = nullptr;
		SDL_Window* m_window = nullptr;

		Color m_clearColor{ 0,0,0,255 };

		int m_width = 0;
		int m_height = 0;

		Matrix3x3 m_view;
		Matrix3x3 m_viewport;

		friend class Text;
		friend class Texture;

	};

}
