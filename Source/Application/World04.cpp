#include "World04.h"
#include "Framework/Framework.h"
#include "Input/InputSystem.h"

#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtx/color_space.hpp>


namespace nc
{
    bool World04::Initialize()
    {
        //m_material = GET_RESOURCE(Material, "materials/quad.mtrl");
        auto material = GET_RESOURCE(Material, "materials/squirrel.mtrl");
        m_model = std::make_shared<Model>();
        m_model->SetMaterial(material);
        //m_model->Load("models/sphere.obj", glm::vec3{0}, glm::vec3{ 0, 0, 0});
        //m_model->Load("models/plane.obj");
        //m_model->Load("models/buddha.obj", glm::vec3{0}, glm::vec3{ -90, 0, 0});
        m_model->Load("models/squirrel.glb");
        m_transform.position.y = -1;

        for (int i = 0; i < 3; i++)
        {
            m_lights[i].type = light_t::eType::Point;
            m_lights[i].position = glm::vec3{ randomf(-5.0f, 5.0f), randomf(1.0f, 8.0f), randomf(-5.0f, 5.0f) };
            m_lights[i].direction = glm::vec3{ 0, -1, 0 };
            m_lights[i].color = glm::rgbColor(glm::vec3{ randomf() * 360, 1, 1 });
            m_lights[i].range = 10000;
            m_lights[i].intensity = 1;
            m_lights[i].innerAngle = 10.0f;
            m_lights[i].outerAngle = 30.0f;

        }

        return true;
    }

    void World04::Shutdown()
    {
    }

    void World04::Update(float dt)
    {
        ENGINE.GetSystem<Gui>()->BeginFrame();

        
        ImGui::Begin("Transform");
        ImGui::DragFloat("Scroll Amount", &m_scrollAmount);
        ImGui::DragFloat("X Offset", &m_xOffset);
        ImGui::DragFloat("Y Offset", &m_yOffset);
        ImGui::DragInt("xTile", &m_xTile);
        ImGui::DragInt("yTile", &m_yTile);
        ImGui::End();

        ImGui::Begin("Scene");
        ImGui::ColorEdit3("Ambient Color", glm::value_ptr(m_ambientColor));
        ImGui::Separator();

        for (int i = 0; i < 3; i++)
        {
            std::string name = "light" + std::to_string(i);
            if (ImGui::Selectable(name.c_str(), m_selected == i)) m_selected = i;
        }
        ImGui::End();

        ImGui::Begin("Lights");
        const char* types[] = {"Point", "Directional", "Spot"};
        ImGui::Combo("Type", (int*)(&m_lights[m_selected].type), types, 3);

        if (m_lights[m_selected].type != light_t::Directional) ImGui::DragFloat3("Position", glm::value_ptr(m_lights[m_selected].position), 0.1f);
        if (m_lights[m_selected].type != light_t::Point) ImGui::DragFloat3("Direction", glm::value_ptr(m_lights[m_selected].direction), 0.1f);
        if (m_lights[m_selected].type == light_t::Spot)
        {
            ImGui::DragFloat("Inner Angle", &m_lights[m_selected].innerAngle, 0.1f, 0, m_lights[m_selected].outerAngle);
            ImGui::DragFloat("Outer Angle", &m_lights[m_selected].outerAngle, 0.1f, m_lights[m_selected].innerAngle, 2000);
        }
        ImGui::DragFloat("Intensity", &m_lights[m_selected].intensity, 0.1f, 0, 10);

        if (m_lights[m_selected].type != light_t::Directional) {
            ImGui::DragFloat("Range", &m_lights[m_selected].range, 0.1f, 0.1f, 100);
        }
        ImGui::ColorEdit3("Ambient Color", glm::value_ptr(m_lights[m_selected].color));
        ImGui::ColorEdit3("Diffuse Color", glm::value_ptr(m_ambientColor));
        ImGui::End();


        //m_transform.rotation.z += 180 * dt;

        


        m_transform.position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_A) ? m_speed * -dt : 0;
        m_transform.position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_D) ? m_speed * +dt : 0;
        m_transform.position.z += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_W) ? m_speed * -dt : 0;
        m_transform.position.z += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_S) ? m_speed * +dt : 0;
        m_time += dt;

        auto material = m_model->GetMaterial();
        material->ProcessGui();
        material->Bind();

        /*m_program->SetUniform("offset", glm::vec2{sin(m_time) * m_scrollAmount + m_xOffset, m_yOffset});
        m_program->SetUniform("tiling", glm::vec2{m_xTile, m_yTile});*/



        //glm::mat4 position = glm::translate(glm::mat4{ 1 }, m_position);
        //glm::mat4 rotation = glm::rotate(glm::mat4{ 1 }, glm::radians(m_angle), glm::vec3{ 0, 0, 1 });

        //model
        //glm::mat4 model = position * rotation;
        material->GetProgram()->SetUniform("model", m_transform.GetMatrix());

        //view matrix
        glm::mat4 view = glm::lookAt(glm::vec3{ 0, 0, 3 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 });
        material->GetProgram()->SetUniform("view", view);

        //projection
        glm::mat4 projection = glm::perspective(glm::radians(70.0f), ENGINE.GetSystem<Renderer>()->GetWidth() / (float)ENGINE.GetSystem<Renderer>()->GetHeight(), .01f, 1000.0f);
        material->GetProgram()->SetUniform("projection", projection);

        for (int i = 0; i < 3; i++)
        {
            std::string name = "lights[" + std::to_string(i) + "]";
            material->GetProgram()->SetUniform(name + ".type", m_lights[i].type);
            material->GetProgram()->SetUniform(name + ".position", m_lights[i].position);
            material->GetProgram()->SetUniform(name + ".intensity", m_lights[i].intensity);
            material->GetProgram()->SetUniform(name + ".range", m_lights[i].range);
            material->GetProgram()->SetUniform(name + ".direction", glm::normalize(m_lights[i].direction));
            material->GetProgram()->SetUniform(name + ".innerAngle", glm::radians(m_lights[i].innerAngle));
            material->GetProgram()->SetUniform(name + ".outerAngle", glm::radians(m_lights[i].outerAngle));

            material->GetProgram()->SetUniform(name + ".color", m_lights[i].color);
            material->GetProgram()->SetUniform("ambientLight", m_ambientColor);
        }

        ENGINE.GetSystem<Gui>()->EndFrame();

    }

    void World04::Draw(Renderer& renderer)
    {
        // pre-render
        renderer.BeginFrame();
        // render
        //m_vertexBuffer->Draw(GL_QUADS);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        m_model->Draw();
        ENGINE.GetSystem<Gui>()->Draw();
        // post-render
        renderer.EndFrame();

    }
}
