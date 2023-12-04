#pragma once
#include "Framework/World.h"
#include "Renderer/Renderer.h"
#include "Core/Math/Transform.h"
#include <vector>


namespace nc
{

	class World05 : public World	
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

		float m_refraction = 1;


		glm::vec3 m_ambientColor{0.25f, 0.25f, 0.25f};

	};
}