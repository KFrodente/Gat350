#pragma once
#include "Framework/World.h"
#include <glm/glm/glm.hpp>

namespace nc
{
	class World01 : public World
	{
	public:
		bool Initialize() override;
		void Shutdown() override;
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

	private:
		float m_angle = 0;
		float m_angleAmount = 0;
		float m_time;
		glm::vec2 m_position;
	};
}