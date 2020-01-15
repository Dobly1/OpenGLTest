#include "mesh.h"


//Constructor
Mesh::Mesh(Vertex * vertices, unsigned int numVertices)
{
    m_drawCount = numVertices;

    glGenVertexArrays(1, &m_vertexArrayObject);

    glBindVertexArray(m_vertexArrayObject);

    //Generates Buffer
    glGenBuffers( NUM_BUFFERS, m_vertexArrayBuffers );

    //Tells OpenGL to consider the data an array
    glBindBuffer( GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB] );

    //Takes data and puts it in buffer on GPU
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);

    //Data is now on GPU and we have to tel open GL how to interprit it
    
    glEnableVertexAttribArray(0);
    
    //Tell open GL to look at var as an array
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindVertexArray(0);
}

//Destructor
Mesh::~Mesh()
{
    glDeleteBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
    glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::Draw()
{
    glBindVertexArray(m_vertexArrayObject);

    glDrawArrays(GL_TRIANGLES, 0, m_drawCount);

    //glDrawElementsBaseVertex(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0, 0);

    glBindVertexArray(0);
}