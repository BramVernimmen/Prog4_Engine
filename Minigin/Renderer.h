#pragma once
#include <SDL.h>
#include "Singleton.h"

namespace dae
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* m_renderer{};
		SDL_Window* m_window{};
		SDL_Color m_clearColor{};	
	public:
		void Init(SDL_Window* window);
		void Render();
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y, bool flip = false) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height, bool flip = false) const;

		SDL_Renderer* GetSDLRenderer() const;

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }

		void SwitchDrawMode() { m_ShowDebug = !m_ShowDebug; }
		bool DrawDebug() { return m_ShowDebug; }

	private:
		// imgui demo
		//bool m_ShowDemo{ true };
		bool m_ShowDebug{ false };
	};
}

