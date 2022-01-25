#include "S_myClickeEffect.h"

float MYvertices[] = {
    // positions  1        // p2              // texture coords
     1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f, // top right
     1.0f, -1.0f, 0.0f,   1.0f,-1.0f, 0.0f,   1.0f, 1.0f, // bottom right
    -1.0f, -1.0f, 0.0f,  -1.0f,-1.0f, 0.0f,   0.0f, 1.0f, // bottom left
    -1.0f,  1.0f, 0.0f,  -1.0f, 1.0f, 0.0f,   0.0f, 0.0f  // top left 
};
unsigned int MYindices[] = {
    0, 1, 3,
    1, 2, 3
};

S_MyClickEffect::S_MyClickEffect() {

}

void S_MyClickEffect::initGL()
{
    shader = new Shader("shaders/study/myclickeffect/texture.vs", "shaders/study/myclickeffect/texture.fs");
    ClickEffect_1 = new Shader("shaders/study/myclickeffect/myclickeffect.vs", "shaders/study/myclickeffect/myclickeffect.fs");
    ClickEffect_2 = new Shader("shaders/study/myclickeffect/myclickeffect_2.vs", "shaders/study/myclickeffect/myclickeffect_2.fs");

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(MYvertices), MYvertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(MYindices), MYindices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &effectVBO);
    glBindBuffer(GL_ARRAY_BUFFER, effectVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(MYvertices), MYvertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(1);


    backendTexture = loadTexture("res\\texture\\test\\ETC2_1024_1024.png");
    effect_1 = loadTexture("res\\texture\\clickEffect_7.png");
    effect_2 = loadTexture("res\\texture\\clickEffect_555.png");

    //framebuffer
    glGenBuffers(1, &m_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
    glGenTextures(1, &texture_target);
    glBindTexture(GL_TEXTURE_2D, texture_target);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_target, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    shader->use();
    shader->setInt("back", 0);
    ClickEffect_1->use();
    ClickEffect_1->setInt("backColor", 0);
    ClickEffect_1->setInt("effect1", 1);

    ClickEffect_2->use();
    ClickEffect_2->setInt("effect2", 0);



}
#include <time.h>
#include <windows.h>
#include <stdio.h>
void S_MyClickEffect::paintGL(float deltaTime)
{

    LARGE_INTEGER nFreq;
    LARGE_INTEGER t1;
    LARGE_INTEGER t2;
    
    double dt;
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&t1);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    shader->use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, backendTexture);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    ClickEffect_1->use();
    ClickEffect_1->setVec2("iResolution", glm::vec2(m_width, m_height));
    ClickEffect_1->setFloat("iTime", time);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_target);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, effect_1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


    ClickEffect_2->use();
    ClickEffect_2->setVec2("iResolution", glm::vec2(m_width, m_height));
    ClickEffect_2->setFloat("iTime", time);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, effect_2);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    time += 0.02;
    if (time > 1)
    {
        time = 0.0;
    }

    QueryPerformanceCounter(&t2);
    dt = (t2.QuadPart - t1.QuadPart) / (double)(nFreq.QuadPart);
    printf("The run time is: %10.3lf\n", dt * 1000000, "us\n");

}

void S_MyClickEffect::setCursePos(float x, float y)
{
    mouse_x = x;
    mouse_y = y;
}

void S_MyClickEffect::setScreenSize(int width, int height)
{
    m_width = width;
    m_height = height;
}

void S_MyClickEffect::freeGL()
{
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteTextures(1, &backendTexture);
    glDeleteProgram(shader->ID);

}

S_MyClickEffect::~S_MyClickEffect()
{

}