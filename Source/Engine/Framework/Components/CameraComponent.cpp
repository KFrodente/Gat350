#include "CameraComponent.h"
#include "Framework/Actor.h"
#include "Framework/Engine.h"

namespace nc
{
	CLASS_DEFINITION(CameraComponent)

	bool CameraComponent::Initialize()
	{
		// get aspect from window if not set
		if (aspect == 0)
		{
			aspect = ENGINE.GetSystem<Renderer>()->GetWidth() / (float)ENGINE.GetSystem<Renderer>()->GetHeight();
		}

		return true;
	}

	void CameraComponent::Update(float dt)
	{
		view = glm::lookAt(m_owner->transform.position, m_owner->transform.position + m_owner->transform.Forward(), glm::vec3{ 0, 1, 0 });

		if (projectionType == Perspective)
		{
			projection = glm::perspective(glm::radians(70.0f), ENGINE.GetSystem<Renderer>()->GetWidth() / (float)ENGINE.GetSystem<Renderer>()->GetHeight(), .01f, 1000.0f);
		}
		else
		{
			projection = glm::ortho(-size * 0.5f * aspect, size * 0.5f * aspect, -size * 0.5f, size * 0.5f, near, far);
		}
	}

	void CameraComponent::SetPerspective(float fov, float aspect, float near, float far)
	{
		// set this class fov, aspect, near and far values with parameters (this->fov = fov, ...)
		this->fov = fov;
		this->aspect = aspect;
		this->near = near;
		this->far = far;

		// set projection matrix with glm::perspective function (fov is in degrees, convert to radians)
		projection = glm::perspective(glm::radians(fov), aspect, near, far);
	}

	void CameraComponent::SetLookAt(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up)
	{
		// set view matrix with glm::lookAt function
		view = glm::lookAt(eye, center, up);
	}

	void CameraComponent::SetProgram(res_t<Program> program)
	{
		// set program uniform for "view" with view matrix
		program->SetUniform("view", view);
		// set program uniform for "projection" with projection matrix
		program->SetUniform("projection", projection);
	}

	void CameraComponent::ProcessGui()
	{
		// use ImGui::DragFloat to set fov, aspect, near and far values (use speed of 0.1f)
		//ImGui::Begin("Camera");
		const char* types[] = { "Orthographic", "Perspective" };
		ImGui::Combo("Projection", (int*)(&projectionType), types, 2);

		ImGui::DragFloat("Fov", &fov, 0.1f);
		ImGui::DragFloat("Aspec", &aspect, 0.1f);
		ImGui::DragFloat("Near", &near, 0.1f, 0, far);
		ImGui::DragFloat("Far", &far, 0.1f, near, 1000);
		ImGui::DragFloat("Size", &size, 0.1f, 3, 25);
		//ImGui::End();

	}

	void CameraComponent::Read(const json_t& value)
	{
		// READ_DATA of fov, aspect, near and far values
		READ_DATA(value, fov);
		READ_DATA(value, aspect);
		READ_DATA(value, near);
		READ_DATA(value, far);

		std::string projectionTypeName;
		READ_NAME_DATA(value, "projectionType", projectionTypeName);
		if (StringUtils::IsEqualIgnoreCase("orthographic", projectionTypeName)) projectionType = eProjectionType::Orthographic;
		if (StringUtils::IsEqualIgnoreCase("perspective", projectionTypeName)) projectionType = eProjectionType::Perspective;

		READ_DATA(value, size);
	}
}