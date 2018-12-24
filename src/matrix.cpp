#include "matrix.h"
#include "global_def.h"
#include <memory.h>
#include <assert.h>
#include <math.h>
#include <iostream>

GeoMatrix::GeoMatrix(const unsigned int row, const unsigned int col)
    : m_data(nullptr), m_row(0), m_col(0)
{
    Init(row, col);
}

GeoMatrix::GeoMatrix(const GeoMatrix &m)
{
    Init(m.m_row, m.m_col);

    for (unsigned int row = 0; row < m_row; row++)
    {
        for (unsigned int col = 0; col < m_col; col++)
        {
            m_data[row][col] = m[row][col];
        }
    }
}

GeoMatrix::~GeoMatrix()
{
    Clear();
}

GeoMatrix &GeoMatrix::operator=(const GeoMatrix &m)
{

    if (&m == this)
    {
        return *this;
    }

    Clear();
    Init(m.m_row, m.m_col);

    for (unsigned int row = 0; row < m_row; row++)
    {
        for (unsigned int col = 0; col < m_col; col++)
        {
            m_data[row][col] = m[row][col];
        }
    }

    return *this;
}

double *GeoMatrix::operator[](const unsigned int idx) const
{
    assert(m_data && (idx < m_row));

    return m_data[idx];
}

double *GeoMatrix::operator[](const unsigned int idx)
{
    assert(m_data && (idx < m_row));

    return m_data[idx];
}

GeoVector3D GeoMatrix::operator*(const GeoVector3D &v) const
{
    assert((GeoVector3D::Size() == m_col) && (m_col == m_row));

    GeoVector3D ret;
    ret[0] = m_data[0][0] * v[0] + m_data[0][1] * v[1] + m_data[0][2] * v[2];
    ret[1] = m_data[1][0] * v[0] + m_data[1][1] * v[1] + m_data[1][2] * v[2];
    ret[2] = m_data[2][0] * v[0] + m_data[2][1] * v[1] + m_data[2][2] * v[2];

    return ret;
}

GeoVector2D GeoMatrix::operator*(const GeoVector2D &v) const
{
    assert((GeoVector2D::Size() == m_col) && (m_col == m_row));

    GeoVector2D ret;
    ret[0] = m_data[0][0] * v[0] + m_data[0][1] * v[1];
    ret[1] = m_data[1][0] * v[0] + m_data[1][1] * v[1];

    return ret;
}

void GeoMatrix::SetIdentity()
{
    assert((m_row == m_col) && (m_row > 0));

    for (unsigned int row = 0; row < m_row; row++)
    {
        for (unsigned int col = 0; col < m_col; col++)
        {
            if (row == col)
            {
                m_data[row][col] = 1.0f;
            }
            else
            {
                m_data[row][col] = 0.0f;
            }
        }
    }
}

void GeoMatrix::Flatten(std::vector<float>& data)
{
    for(size_t j = 0; j < m_col; j++)
    {
        for(size_t i = 0; i < m_row; i++)
        {
            data.push_back(m_data[i][j]);
        }
    }
}

void GeoMatrix::Dump()
{
    for(size_t i = 0; i < m_row; i++)
    {
        for(size_t j = 0; j < m_col; j++)
        {
            std::cout << m_data[i][j] << "  ";
        }

        std::cout << std::endl;
    }
}

GeoMatrix GeoMatrix::SubMatrix(const unsigned int sRow, const unsigned int eRow, const unsigned int sCol, const unsigned int eCol)
{
    GeoMatrix m(eRow - sRow, eCol - sCol);

    for(size_t i = sRow; i < eRow; i++)
    {
        for(size_t j = sCol; j < eCol; j++)
        {
            m[i-sRow][j-sCol] =  m_data[i][j];
        }
    }

    return m;
}

void GeoMatrix::Clear()
{
    for (unsigned int row = 0; row < m_row; row++)
    {
        SAFE_DELETE_ARRAY(m_data[row]);
    }

    SAFE_DELETE(m_data);

    m_row = 0;
    m_col = 0;
}

void GeoMatrix::Init(const unsigned int row, const unsigned int col)
{
    m_row = row;
    m_col = col;

    m_data = new double *[m_row];

    for (unsigned int row = 0; row < m_row; row++)
    {
        m_data[row] = new double[m_col];
        memset(m_data[row], 0, sizeof(double) * m_col);
    }
}

GeoMatrix GeoMatrix::RotateMatrix(const double angle, const GeoVector3D &axis)
{
    GeoMatrix matrix(3, 3);

    double c = cos(angle);
    double s = sin(angle);

    matrix[0][0] = c + (1 - c) * pow(axis[0], 2.0f);
    matrix[0][1] = (1 - c) * axis[0] * axis[1] - s * axis[2];
    matrix[0][2] = (1 - c) * axis[0] * axis[2] + s * axis[1];

    matrix[1][0] = (1 - c) * axis[0] * axis[1] + s * axis[2];
    matrix[1][1] = c + (1 - c) * pow(axis[1], 2.0f);
    matrix[1][2] = (1 - c) * axis[1] * axis[2] - s * axis[0];

    matrix[2][0] = (1 - c) * axis[0] * axis[2] - s * axis[1];
    matrix[2][1] = (1 - c) * axis[1] * axis[2] + s * axis[0];
    matrix[2][2] = c + (1 - c) * pow(axis[2], 2.0f);

    return matrix;
}