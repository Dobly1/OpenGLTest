#include "shader.h"
#include <string>
#include <fstream>
#include <iostream>


//static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
//static std::string LoadShader(const std::string& fileName);
//static GLuint CreateShader(const std::string & text, GLenum shaderType);

//Constructor
Shader::Shader(const std::string & fileName)
{
    m_program = glCreateProgram();

    //Initalize Shaders
    m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
    m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

    //Add shaders to program
    for(unsigned int i = 0; i< NUM_SHADERS; i++)
    {
        glAttachShader(m_program, m_shaders[i]);
    }

    //Bind Attribute Location
    glBindAttribLocation(m_program, 0, "Position");

    //Link Shaders
    glLinkProgram(m_program);
    CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Program failed to link: ");

    //Validate Program
    glValidateProgram(m_program);
    CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Program failed to validate: ");

}

//Destructor
Shader::~Shader()
{
    for(unsigned int i = 0; i< NUM_SHADERS; i++)
    {
        glDetachShader(m_program, m_shaders[i]);
        glDeleteShader(m_shaders[i]);
    }

    glDeleteProgram(m_program);
}

//Nothing can be wrong here
void Shader::Bind()
{
    glUseProgram(m_program);
}

//NOT MY CODE - FROM VIDEO TO LOAD SHADER - by thebennybox
std::string Shader::LoadShader(const std::string& fileName)
{
    std::ifstream file;
    file.open((fileName).c_str());

    std::string output;
    std::string line;

    if(file.is_open())
    {
        while(file.good())
        {
            getline(file, line);
			output.append(line + "\n");
        }
    }
    else
    {
		std::cerr << "Unable to load shader: " << fileName << std::endl;
    }

    return output;
}

//NOT MY CODE - FROM VIDEO TO LOAD SHADER - by thebennybox
void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
    GLint success = 0;
    GLchar error[1024] = { 0 };

    if(isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);

    if(success == GL_FALSE)
    {
        if(isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);

        std::cerr << errorMessage << ": '" << error << "'" << std::endl;
    }
}

GLuint Shader::CreateShader(const std::string & text, GLenum shaderType)
{
    GLuint shader = glCreateShader(shaderType);

    if(shader == 0)
        std::cerr << "Error: Shader creation failed!" << std::endl;

    const GLchar * shaderSourceStrings[1];
    GLint shaderSourceStringsLengths[1];

    shaderSourceStrings[0] = text.c_str();    
    shaderSourceStringsLengths[0] = text.length();
    
    glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringsLengths);

    glCompileShader(shader);

    CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader Compilation Failed: ");

    return shader;
}








