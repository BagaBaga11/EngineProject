

#include <iostream>
#include "GameEngineProject.h"
#include "SDL.h"
#include "box2d.h"
#include <vector>
#include "Levels.h"
#include "Pawns.h"
#include <random>
#include "glad/glad.h"
#include "stb_image.h"

void GameEngine::Start(int sizeX, int sizeY)
{
    SDL_Init(SDL_INIT_VIDEO);


    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    ev = new SDL_Event;
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = b2Vec2{ myLevel->GetGrav("h"), myLevel->GetGrav("v")};
    b2WorldId* worl = new b2WorldId(b2CreateWorld(&worldDef));
    myLevel->SetWorld(worl);

    b2BodyDef groundBodyDef = b2DefaultBodyDef();
    groundBodyDef.position = b2Vec2{ 240.0f, 680.0f };
    b2BodyId groundId = b2CreateBody(*worl, &groundBodyDef);
    b2Polygon groundBox = b2MakeBox(1500.0f, 1.0f);
    b2ShapeDef groundShapeDef = b2DefaultShapeDef();
    b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);

    window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, sizeY, sizeX, 0);
    SDL_GLContext context = SDL_GL_CreateContext(window);

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        SDL_Quit();
    }
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    myLevel->SetRender(render);

    SDL_Surface* windowSurface = SDL_GetWindowSurface(window);

    float vertices[] = {
        // positions         // colors   
        0.1f,  0.1f, 0.0f,   1.0f, 0.0f, 0.0f,// top right
        0.1f, -0.1f, 0.0f,   0.0f, 1.0f, 0.0f,// bottom right
       -0.1f, -0.1f, 0.0f,   0.0f, 0.0f, 1.0f,// bottom left
       -0.1f,  0.1f, 0.0f,   1.0f, 1.0f, 0.0f // top left
    };

    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    vbo = new GLuint; // vertex buffer object
    glGenBuffers(1, vbo); // Generate 1 buffer

    ebo = new GLuint;
    glGenBuffers(1, ebo);

   vao = new GLuint;
    glGenVertexArrays(1, vao);

    glBindVertexArray(*vao);

    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    const char* vertexShaderSource = R"glsl(
		#version 330 core

        in vec3 position;
        in vec3 color;
        
        out vec3 Color;
        out vec2 TexCoord;

        uniform vec2 texCoordStart;
        uniform vec2 texCoordEnd;

        void main()
        {
            Color = color;
            TexCoord = vec2(position.x * (texCoordEnd.x - texCoordStart.x) + texCoordStart.x,
                             position.y * (texCoordEnd.y - texCoordStart.y) + texCoordStart.y);
            gl_Position = vec4(position, 1.0);
        }
    )glsl";


    // Vertex Shader

    *vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(*vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(*vertexShader);

    GLint  success;
    char infoLog[512];
    glGetShaderiv(*vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(*vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Fragment Shader

    const char* fragmentShaderSource = R"glsl(
		#version 330 core
		in vec3 Color;
		in vec2 TexCoord;

		out vec4 outColor;

		uniform sampler2D ourTexture;
		uniform float scaleFactor;

		void main()
		{
			 vec2 scaledTexCoord = TexCoord * scaleFactor; // Scale texture by 2x
			outColor = texture(ourTexture, scaledTexCoord);

			 if (outColor == vec4(1.0f, 0.0f, 1.0f, 1.0f)) 
				 discard;
		}
    )glsl";

    *fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(*fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(*fragmentShader);

    glGetShaderiv(*fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(*fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    shaderProgram = new GLuint;
    *shaderProgram = glCreateProgram();

    glAttachShader(*shaderProgram, *vertexShader);
    glAttachShader(*shaderProgram, *fragmentShader);
    glLinkProgram(*shaderProgram);

    glDeleteShader(*vertexShader);
    glDeleteShader(*fragmentShader);

    glGetProgramiv(*shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(*shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // 3. then set our vertex attributes pointers
    GLint posAttrib = glGetAttribLocation(*shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

    GLint colorAttrib = glGetAttribLocation(*shaderProgram, "color");
    glEnableVertexAttribArray(colorAttrib);
    glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

}
bool GameEngine::Update(float deltaTime)
{          

        while (SDL_PollEvent(ev))
        {
            if (ev->type == SDL_QUIT)
            return false;
        }
        myLevel->Update(deltaTime);
        for (size_t i = 0; i < myLevel->bmpArray.size(); ++i)
        { 
            myLevel->everyArray.Draw(*shaderProgram);
        }
        SDL_GL_SwapWindow(window);

        return true;
}

void GameEngine::End()
{
    delete shaderProgram;
    delete vbo;
    delete ebo;
    delete vao;
    delete ev;
    glBindVertexArray(0);
    b2DestroyWorld(*myLevel->GetWorld());
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
}

void GameEngine::SetLevel(Level* level)
{
    myLevel = level;
}

int GameEngine::Tick()
{
    return SDL_GetTicks();
}

float GameEngine::getRandomFloat(float min, float max) 
{
    static std::random_device rd;          
    static std::mt19937 gen(rd());           
    std::uniform_real_distribution<float> dis(min, max);

    return dis(gen);                    
}

bool GameEngine::RandomBool()
{
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::bernoulli_distribution dist(0.5);

    return dist(gen);
}

