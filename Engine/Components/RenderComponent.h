#pragma once
#include "Framework/Component.h"
#include "Math/Rect.h"
#include "Math/Vector2.h"

namespace phoenix
{
	class Renderer;

	class RenderComponent : public Component
	{
	public:

		virtual void Draw(Renderer& renderer) = 0;

		virtual Rect& GetSource() { return source; }

		void SetflipHorizontal(bool flip = true) { flipHorizontal = flip; }
		bool GetflipHorizontal() { return flipHorizontal; }

	protected:

		Rect source;
		Vector2 regitstration = Vector2{ 0.5f, 0.5f};
		bool flipHorizontal = false;
	
	};
}