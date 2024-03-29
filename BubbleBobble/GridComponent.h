#pragma once
#include "UpdateComponent.h"
#include <string>

namespace dae
{
	class TransformComponent;
	class GridComponent final : public UpdateComponent
	{
	public:
		GridComponent(GameObject* pOwner);
		~GridComponent() = default;
		GridComponent(const GridComponent& other) = delete;
		GridComponent(GridComponent&& other) = delete;
		GridComponent& operator=(const GridComponent& other) = delete;
		GridComponent& operator=(GridComponent&& other) = delete;


		virtual void Update() override {};
		virtual void Render() const override; // for debug only

		void SetTileLayout(const std::string& newTileLayout) { m_TileLayout = newTileLayout; }
		void Resize(int newWidth, int newHeight);
		int GetWidth() { return m_Width; }
		int GetHeight() { return m_Height; }
		int GetPixelSize() {return m_PixelSize;}

	private:
		void CreateTiles();


		TransformComponent* m_pTransform{}; // top left

		
		int m_Width{ 10 };
		int m_Height{ 10 };
		int m_PixelSize{ 24 }; // cells are 24x24 px

		std::string m_TileLayout{};

	};
}

