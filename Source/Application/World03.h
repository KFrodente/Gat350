#pragma once
#include "Framework/World.h"
#include "Renderer/Renderer.h"
#include "Core/Math/Transform.h"


namespace nc
{
	class World03 : public World	
	{
	public:
		bool Initialize() override;
		void Shutdown() override;
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

	private:
		float m_time;
		float m_speed = 5.0f;
		float m_scrollAmount = 1.0f;
		float m_xOffset = 0.0f;
		float m_yOffset = 0.0f;
		int m_xTile = 1;
		int m_yTile = 1;

		Transform m_transform;

		res_t<Material> m_material;

		res_t<VertexBuffer> m_vertexBuffer;
		res_t<Program> m_program;

		res_t<Texture> m_texture;
	};
}