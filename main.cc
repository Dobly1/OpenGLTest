#include <iostream>
#include <GL/glew.h>

#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"

int main()
{
    Display display(800, 600, "Test Program");

    Shader shader("./res/basicShader");
    
    Vertex vertices[] = {  Vertex(glm::vec3(-0.5,-0.5,0)), Vertex(glm::vec3(0,0.5,0)), Vertex(glm::vec3(0.5,-0.5,0)) };

    Mesh mesh(vertices, sizeof(vertices)/sizeof(vertices[0]));
    
    Texture texture("./res/bricks.jpg");

    while(!display.IsClosed())
    {
        display.Clear(0.15f, 0.0f, 0.3f, 1.0f);

        shader.Bind();

        texture.Bind(0);

        mesh.Draw();

        display.Update();
    }


    return 0;
}