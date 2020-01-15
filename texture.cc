#include "texture.h"
#include "stb_image.h"
#include <assert.h>
#include <iostream>

//Constructor
Texture::Texture(const std::string & fileName)
{
    int width, height, numComponents;

    stbi_uc * imageData = stbi_load( fileName.c_str(), &width, &height, &numComponents, 4 );

    if(!imageData)
    {
        std::cerr<< "Texture loading failed for texture: "<< fileName<< std::endl;
    }

    //Generate texture and give us its address
    glGenTextures(1, &m_texture);

    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTextureParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    stbi_image_free(imageData);
}

//Destructor
Texture::~Texture()
{
    //Deletes texture once we're done with it
    glDeleteTextures(1, &m_texture);
}

void Texture::Bind(unsigned int unit)
{
    assert(unit >= 0 && unit <= 31);

    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, m_texture);
}