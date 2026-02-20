#include "game/VNGame.h"

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>

#include "engine/graphics/Shader.h"

namespace
{
    static float rect[] = {
        -0.5f,-0.5f,0.0f,
         0.5f,-0.5f,0.0f,
         0.5f, 0.5f,0.0f,

        -0.5f,-0.5f,0.0f,
         0.5f, 0.5f,0.0f,
        -0.5f, 0.5f,0.0f
    };
}

namespace engine
{
    bool VNGame::Load()
    {
        glGenVertexArrays(1, &mVao);
        glGenBuffers(1, &mVbo);

        glBindVertexArray(mVao);
        glBindBuffer(GL_ARRAY_BUFFER, mVbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindVertexArray(0);

        mShader = new Shader("assets/shaders/basic.vert", "assets/shaders/basic.frag");
        if (!mShader->IsValid())
        {
            delete mShader;
            mShader = nullptr;
            return false;
        }

        return true;
    }

    void VNGame::Render()
    {
        if (!mShader) return;

        mShader->Use();
        mShader->SetVec3("uColor", 0.0f, 1.0f, 0.0f);
        mShader->SetVec2("uScale", 0.5f, 0.5f);
        mShader->SetVec2("uOffset", 0.0f, 0.0f);

        glBindVertexArray(mVao);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }

    void VNGame::Unload()
    {
        if (mVbo)
        {
            glDeleteBuffers(1, &mVbo);
            mVbo = 0;
        }
        if (mVao)
        {
            glDeleteVertexArrays(1, &mVao);
            mVao = 0;
        }
        if (mShader)
        {
            delete mShader;
            mShader = nullptr;
        }
    }
}