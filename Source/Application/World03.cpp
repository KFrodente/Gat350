#include "World03.h"
#include "Framework/Framework.h"
#include "Input/InputSystem.h"

#include <glm/glm/gtc/type_ptr.hpp>


namespace nc
{
    bool World03::Initialize()
    {
        m_material = GET_RESOURCE(Material, "materials/quad.mtrl");
        

        //vertex data
        float vertexData[] = {
            -0.8f, -0.8f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
             0.8f, -0.8f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
             0.8f,  0.8f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
             -0.8f, 0.8f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f
        };

        m_vertexBuffer = std::make_shared<VertexBuffer>();
        m_vertexBuffer->CreateVertexBuffer(sizeof(vertexData), 4, vertexData);
        m_vertexBuffer->SetAttribute(0, 3, 8 * sizeof(GLfloat), 0);                  // position 
        m_vertexBuffer->SetAttribute(1, 3, 8 * sizeof(GLfloat), 3 * sizeof(float));  // color 
        m_vertexBuffer->SetAttribute(2, 2, 8 * sizeof(GLfloat), 6 * sizeof(float));  // texcoord

        //GLuint vbo;
        //glGenBuffers(1, &vbo);
        //glBindBuffer(GL_ARRAY_BUFFER, vbo);
        //glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

        //glGenVertexArrays(1, &m_vao);
        //glBindVertexArray(m_vao);

        //glBindVertexBuffer(0, vbo, 0, 8 * sizeof(GLfloat));

        ////position
        //glEnableVertexAttribArray(0);
        //glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
        //glVertexAttribBinding(0, 0);

        ////color
        //glEnableVertexAttribArray(1);
        //glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat));
        //glVertexAttribBinding(1, 0);

        ////texCoord
        //glEnableVertexAttribArray(2);
        //glVertexAttribFormat(2, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat));
        //glVertexAttribBinding(2, 0);
        //m_position.z = -10.0f;

        return true;
    }

    void World03::Shutdown()
    {
    }

    void World03::Update(float dt)
    {
        ENGINE.GetSystem<Gui>()->BeginFrame();

        ImGui::Begin("Transform");
        ImGui::DragFloat3("Position", &m_transform.position[0]);
        ImGui::DragFloat3("Rotation", &m_transform.rotation[0]);
        ImGui::DragFloat3("Scale", &m_transform.scale[0]);
        ImGui::DragFloat("Scroll Amount", &m_scrollAmount);
        ImGui::DragFloat("X Offset", &m_xOffset);
        ImGui::DragFloat("Y Offset", &m_yOffset);
        ImGui::DragInt("xTile", &m_xTile);
        ImGui::DragInt("yTile", &m_yTile);
        ImGui::End();


        //m_transform.rotation.z += 180 * dt;

        m_transform.position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_A) ? m_speed * -dt : 0;
        m_transform.position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_D) ? m_speed * +dt : 0;
        m_transform.position.z += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_W) ? m_speed * -dt : 0;
        m_transform.position.z += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_S) ? m_speed * +dt : 0;
        m_time += dt;

        m_material->ProcessGui();
        m_material->Bind();

        /*m_program->SetUniform("offset", glm::vec2{sin(m_time) * m_scrollAmount + m_xOffset, m_yOffset});
        m_program->SetUniform("tiling", glm::vec2{m_xTile, m_yTile});*/



        //glm::mat4 position = glm::translate(glm::mat4{ 1 }, m_position);
        //glm::mat4 rotation = glm::rotate(glm::mat4{ 1 }, glm::radians(m_angle), glm::vec3{ 0, 0, 1 });

        //model
        //glm::mat4 model = position * rotation;
        m_material->GetProgram()->SetUniform("model", m_transform.GetMatrix());

        //view matrix
        glm::mat4 view = glm::lookAt(glm::vec3{ 0, 0, 3 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 });
        m_material->GetProgram()->SetUniform("view", view);

        //projection
        glm::mat4 projection = glm::perspective(glm::radians(70.0f), 800.0f / 600.0f, .01f, 100.0f);
        m_material->GetProgram()->SetUniform("projection", projection);


        ENGINE.GetSystem<Gui>()->EndFrame();

    }

    void World03::Draw(Renderer& renderer)
    {
        // pre-render
        renderer.BeginFrame();
        // render
        m_vertexBuffer->Draw(GL_QUADS);
        ENGINE.GetSystem<Gui>()->Draw();
        // post-render
        renderer.EndFrame();
        //// pre-render
        //renderer.BeginFrame();

        //// render
        //glBindVertexArray(m_vao);
        //glDrawArrays(GL_QUADS, 0, 4);

        //ENGINE.GetSystem<Gui>()->Draw();

        //
        //// post-render
        //renderer.EndFrame();
    }
}
