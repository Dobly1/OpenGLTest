#include "display.h"
#include <iostream>
#include <GL/glew.h>

//Default Constructor
Display::Display(int width, int height, const std::string & title)
{
    //Starts SDL
    SDL_Init(SDL_INIT_EVERYTHING);

    //Set OpenGL Attributes
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    //Create SDL Window
    m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,SDL_WINDOW_OPENGL);

    //Create Context (Lets us draw using GPU - Useful apperantly)
    m_glContext = SDL_GL_CreateContext(m_window);

    GLenum status = glewInit();

    if(status != GLEW_OK)
    {
        std::cerr << "Glew didn't initalize!" << std::endl;
    }

    m_isClosed = false;

}

//Destructor
Display::~Display()
{
    //Cleans up resources
    SDL_GL_DeleteContext(m_glContext);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Display::Clear(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}


bool Display::IsClosed()
{
    return m_isClosed;
}

//Swaps the buffers being drawn on for efficiency sake so OpenGL can constantly draw on a window thats not being drawn
void Display::Update()
{
    SDL_GL_SwapWindow(m_window);

    SDL_Event e;

    while(SDL_PollEvent(&e))
    {
        if( e.type == SDL_QUIT)
        {
            m_isClosed = true;
        }
    }
}