#include "S_WaterWave.h"

float vertices[] = {
    // positions          // colors           // texture coords
     1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, // top right
     1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f, // bottom right
    -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f, // bottom left
    -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f  // top left 
};
unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3 
};

S_WaterWave::S_WaterWave() {

}

void S_WaterWave::initGL()
{
    //shader = new Shader("shaders/study/waterwave/waterwave.vs", "shaders/study/waterwave/waterwave.fs");
    shader = new Shader("shaders/study/waterwave/waterwave.vs", "shaders/study/waterwave/waterwave.fs");
    computeShader = new Shader("shaders/study/waterwave/ImageSamplerExample.comp");

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //backendTexture = loadTexture("res\\texture\\mumu.jpg");
    backendTexture = CreateTextureBuffer();
    anotherTex = CreateTextureBufferEX();
}

GLuint S_WaterWave::CreateTextureBufferEX()
{
    // 2x2 Image, 3 bytes per pixel (R, G, B)
    GLubyte pixels[] =
    {
       255,   255,   122, 255, // Red
         0, 255,   122, 255, // Green
         0,   0, 255, 255, // Blue
       255, 255,   0, 255  // Yellow
    };

    GLuint tex;
    GLuint tbo;
    glGenTextures(1, &tex);
    glGenBuffers(1, &tbo);
    glActiveTexture(GL_TEXTURE1);
    glBindBuffer(GL_TEXTURE_BUFFER, tbo);
    glBindTexture(GL_TEXTURE_BUFFER, tex);
    glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA8, tbo);
    glBufferData(GL_TEXTURE_BUFFER, sizeof(pixels), pixels, GL_STATIC_DRAW);
    glBindImageTexture(1, tex, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA8);

    return tex;
}

GLuint S_WaterWave::CreateTextureBuffer()
{
    // 2x2 Image, 3 bytes per pixel (R, G, B)
    GLubyte pixels[] =
    {
       45,   255,   122, 255, // Red
         0, 255,   122, 255, // Green
         0,   0, 255, 255, // Blue
       255, 255,   0, 255  // Yellow
    };

    GLuint tex;
    GLuint tbo;
    glGenTextures(1, &tex);
    glGenBuffers(1, &tbo);
    glActiveTexture(GL_TEXTURE0);
    glBindBuffer(GL_TEXTURE_BUFFER, tbo);
    glBindTexture(GL_TEXTURE_BUFFER, tex);
    glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA8, tbo);
    glBufferData(GL_TEXTURE_BUFFER, sizeof(pixels), pixels, GL_STATIC_DRAW);
    glBindImageTexture(0, tex, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA8);

    return tex;
}

void S_WaterWave::paintGL(float deltaTime)
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //compute shader
    computeShader->use();
    //glBindImageTexture(0, backendTexture, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA8);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_BUFFER, backendTexture);
    computeShader->setInt("texture", 0);
    glDispatchCompute(1, 1, 1);
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

    shader->use();
    shader->setVec2("iResolution", glm::vec2(m_width, m_height));
    shader->setFloat("u_Boundary", 0.08f);

    Mutex.lock();
    int i = 0;
    for (auto it = drawingElements.begin(); it != drawingElements.end(); it++)
    {
        shader->setFloat("p[" + std::to_string(i) + "].iTime", it->iTime);
        shader->setInt("p[" + std::to_string(i) + "].x", it->x);
        shader->setInt("p[" + std::to_string(i) + "].y", it->y);
        i++;
        float a = it->iTime;
        it->iTime += deltaTime;
        float b = it->iTime;

        shader->setFloat("test", it->iTime);
    }
    if (drawingElements.size())
    {
        while (drawingElements[0].iTime > 2)
        {
            drawingElements.pop_front();
            if (!drawingElements.size())break;
        }
    }
    int a = drawingElements.size();
    shader->setInt("renderingNum", drawingElements.size());
    Mutex.unlock();
    //of += 0.01;
    //if (of > 4)of = of - 3;
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_BUFFER, backendTexture);
    shader->setInt("texture", 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_BUFFER, anotherTex);
    shader->setInt("texture1", 1);

    //shader->setInt("offset", (int)(of));
    //glActiveTexture(GL_TEXTURE0);
    //glBindTexture(GL_TEXTURE_2D, backendTexture);
    //glBindTexture(GL_TEXTURE_BUFFER, backendTexture);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
}

void S_WaterWave::setCursePos(float x, float y)
{
    mouse_x = x;
    mouse_y = y;
    ClickEffectParams p = {
        0.0,
        mouse_x,
        mouse_y
    };

    Mutex.lock();
    if (drawingElements.size() < MAX_DEQUE_SIZE)
    {
        drawingElements.push_back(p);
    }
    else
    {
        drawingElements.pop_front();
        drawingElements.push_back(p);
    }

    std::cout << "deque size: " << drawingElements.size() << std::endl;
    Mutex.unlock();
}

void S_WaterWave::freeGL()
{
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteTextures(1, &backendTexture);
    glDeleteProgram(shader->ID);
        
}

void S_WaterWave::setScreenSize(int width, int height)
{
    m_width = width;
    m_height = height;
}

S_WaterWave::~S_WaterWave()
{

}