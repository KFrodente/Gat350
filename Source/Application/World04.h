#pragma once
#include "Framework/World.h"
#include "Renderer/Renderer.h"
#include "Core/Math/Transform.h"
#include <vector>


namespace nc
{

	class World04 : public World	
	{
	struct light_t
	{
		enum eType
		{
			Point,
			Directional,
			Spot
		};

		eType type;
		glm::vec3 position;
		glm::vec3 direction;
		glm::vec3 color;
		float intensity;
		float range;
		float innerAngle;
		float outerAngle;
	};
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

		//light_t m_light;
		light_t m_lights[3];
		int m_selected = 0;

		glm::vec3 m_ambientColor{0.25f, 0.25f, 0.25f};

		Transform m_transform;
		res_t<Model> m_model;
	};
}