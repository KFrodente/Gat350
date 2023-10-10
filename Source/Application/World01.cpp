#include "World01.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"

namespace nc
{
    bool World01::Initialize()
    {
        return true;
    }

    void World01::Shutdown()
    {
    }

    void World01::Update(float dt)
    {
        m_angle += 90 * dt;
        m_position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_A) ? -dt : 0;
        m_position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_D) ? dt : 0;
        m_position.y += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_S) ? -dt : 0;
        m_position.y += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_W) ? dt : 0;

        m_angleAmount = ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_E) ? 1.0f : 0;
        m_time += dt;
    }

    void World01::Draw(Renderer& renderer)
    {
        // pre-render
        renderer.BeginFrame();

        // render

        //triangle
        glPushMatrix();
        //glTranslatef(randomf(-0.5f, 0.5f), 0, 0);
        glTranslatef(m_position.x, m_position.y, 0);

        //glScalef((sin(m_time) + 1) * 0.5f, 1, 1);

        glRotatef(m_angle, 0, 0, m_angleAmount);

        glBegin(GL_LINE_LOOP);

        glColor3f(1, 0.5f, 0);
        glVertex2f(-0.5f, -0.5f);
        
        glColor3f(0, 1, 0.5f);
        glVertex2f(0, .5f);
        
        glColor3f(0.5f, 0, 1);
        glVertex2f(0.5f, -0.5f);


        glEnd();
        glPopMatrix();


        //weird shape
        glPushMatrix();
        //glTranslatef(randomf(-0.5f, 0.5f), 0, 0);
        glTranslatef(m_position.x, m_position.y, 0);

        //glScalef((sin(m_time) + 1) * 0.5f, 1, 1);

        glRotatef(m_angle, 0, 1, m_angleAmount);

        glBegin(GL_LINE_LOOP);

        glColor3f(1, 0, 0.5f);
        glVertex2f(-0.25f, -0.25f);
        
        glColor3f(1, 0, 0.5f);
        glVertex2f(-0.25f, 0.125f);

        glColor3f(0.5f, 1, 0);
        glVertex2f(0, .25f);

        glColor3f(0, 0.5f, 1);
        glVertex2f(0.25f, 0.25f);
        
        glColor3f(0, 0.5f, 1);
        glVertex2f(0.25f, -0.125f);


        glEnd();
        glPopMatrix();

        //square
        glPushMatrix();
        //glTranslatef(randomf(-0.5f, 0.5f), 0, 0);
        glTranslatef(m_position.x, m_position.y, 0);

        //glScalef((sin(m_time) + 1) * 0.5f, 1, 1);

        glRotatef(m_angle, 0, 0, m_angleAmount);

        glBegin(GL_QUADS);

        glColor3f(1, 0.5f, 0);
        glVertex2f(-0.125f, -0.125f);

        glColor3f(0, 1, 0.5f);
        glVertex2f(-0.125, 0.125f);

        glColor3f(0.5f, 0, 1);
        glVertex2f(0.125f, 0.125f);
        
        glColor3f(0.5f, 0, 1);
        glVertex2f(0.125f, -0.125f);


        glEnd();
        glPopMatrix();

        // post-render
        renderer.EndFrame();
    }
}
