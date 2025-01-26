#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "common.h"

#include "Math.hpp"
#include "./Q3BspRenderHelpers.hpp"

#include "./Q3Bsp.hpp"

#include "graphic/texture/Texture.h"

#include "./Q3BspPatch.hpp"


void Q3BspBiquadPatch::Tesselate(int tessLevel)
{
    m_tesselationLevel = tessLevel;
    m_vertices.resize( (m_tesselationLevel + 1) * (m_tesselationLevel + 1) );

    for (int i = 0; i <= m_tesselationLevel; ++i)
    {
        float a = (float)i / m_tesselationLevel;
        float b = 1.f - a;

        m_vertices[i]= controlPoints[0] * (b * b) +
                       controlPoints[3] * (2 * b * a) +
                       controlPoints[6] * (a * a);
    }

    for (int i = 1; i <= m_tesselationLevel; ++i)
    {
        float a = (float)i / m_tesselationLevel;
        float b = 1.f - a;

        Q3BspVertexLump temp[3];

        for (int j = 0, k = 0; j < 3; ++j, k = 3 * j)
        {
            temp[j] = controlPoints[k + 0] * ( b * b ) +
                      controlPoints[k + 1] * ( 2 * b * a) +
                      controlPoints[k + 2] * ( a * a );
        }

        for (int j = 0; j <= m_tesselationLevel; ++j)
        {
            float a = (float)j / m_tesselationLevel;
            float b = 1.f - a;

            m_vertices[i * (m_tesselationLevel + 1) + j] = temp[0] * ( b * b ) +
                                                           temp[1] * ( 2 * b * a ) +
                                                           temp[2] * ( a * a );
        }
    }

    m_indices.resize( m_tesselationLevel * ( m_tesselationLevel + 1 ) * 2 );

    for (int row = 0; row < m_tesselationLevel; ++row)
    {
        for (int col = 0; col <= m_tesselationLevel; ++col)
        {
            m_indices[( row * (m_tesselationLevel + 1) + col ) * 2 + 1] =  row      * (m_tesselationLevel + 1) + col;
            m_indices[( row * (m_tesselationLevel + 1) + col ) * 2]     = (row + 1) * (m_tesselationLevel + 1) + col;
        }
    }

    m_trianglesPerRow  = new int[m_tesselationLevel];
    m_rowIndexPointers = new unsigned int *[m_tesselationLevel];

    for (int row = 0; row < m_tesselationLevel; ++row)
    {
        m_trianglesPerRow[row] = 2 * (m_tesselationLevel + 1);
        m_rowIndexPointers[row] = &m_indices[row * 2 * (m_tesselationLevel + 1)];
    }
}


void Q3BspBiquadPatch::Render()
{
    // // render the patch
    // if (!GL_EXT_multi_draw_arrays)
    // {
        for (int row = 0; row < m_tesselationLevel; ++row)
        {
            glDrawElements(GL_TRIANGLE_STRIP, 2 * (m_tesselationLevel + 1), GL_UNSIGNED_INT,
                            &m_indices[row * 2 * (m_tesselationLevel + 1)]);
        }
    // }
    // else
    // {
    //     glMultiDrawElementsEXT(GL_TRIANGLE_STRIP, m_trianglesPerRow,
    //                            GL_UNSIGNED_INT, (const void **)m_rowIndexPointers,
    //                            m_tesselationLevel);
    // }
}
