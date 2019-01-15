#include "matrix.h"
#include "global_def.h"
#include <memory.h>
#include <assert.h>
#include <cmath>
#include <iostream>
#include "tools.h"

GeoMatrix::GeoMatrix(const unsigned int row, const unsigned int col)
    : m_data(nullptr), m_row(0), m_col(0)
{
    Init(row, col);
}

GeoMatrix::GeoMatrix(const unsigned int row, const unsigned int col, const double *data)
    : m_data(nullptr), m_row(0), m_col(0)
{
    Init(row, col);

    for (unsigned int i = 0; i < m_row; i++)
    {
        for (unsigned int j = 0; j < m_col; j++)
        {
            m_data[i][j] = data[m_col * i + j];
        }
    }
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

GeoMatrix GeoMatrix::operator*(const GeoMatrix &m) const
{
    assert(m_col == m.Rows());

    GeoMatrix ret(m_row, m.Cols());

    for (unsigned int i = 0; i < m_row; i++)
    {
        for (unsigned int j = 0; j < m.Cols(); j++)
        {
            for (unsigned int k = 0; k < m_col; k++)
            {
                ret[i][j] += (m_data[i][k] * m[k][j]);
            }
        }
    }

    return ret;
}

void GeoMatrix::operator+=(const GeoMatrix &m)
{
    assert((m_col == m.Cols()) && (m_row == m.Rows()));

    for (unsigned int i = 0; i < m_row; i++)
    {
        for (unsigned int j = 0; j < m_col; j++)
        {
            m_data[i][j] += m[i][j];
        }
    }
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

void GeoMatrix::Zeros()
{
    for (unsigned int row = 0; row < m_row; row++)
    {
        m_data[row] = new double[m_col];
        for (unsigned int col = 0; col < m_col; col++)
        {
            m_data[row][col] = 0.0f;
        }
    }
}

void GeoMatrix::Resharp(const unsigned int row, const unsigned int col)
{
    if (m_row == row && m_col == col)
    {
        Zeros();
        return;
    }

    Clear();
    Init(row, col);
}

void GeoMatrix::Flatten(std::vector<float> &data) const
{
    for (unsigned int j = 0; j < m_col; j++)
    {
        for (unsigned int i = 0; i < m_row; i++)
        {
            data.push_back((float)(m_data[i][j]));
        }
    }
}

GeoMatrix GeoMatrix::SubMatrix(const unsigned int sRow, const unsigned int eRow, const unsigned int sCol, const unsigned int eCol)
{
    GeoMatrix m(eRow - sRow, eCol - sCol);

    for (unsigned int i = sRow; i < eRow; i++)
    {
        for (unsigned int j = sCol; j < eCol; j++)
        {
            m[i - sRow][j - sCol] = m_data[i][j];
        }
    }

    return m;
}

void GeoMatrix::Replace(const unsigned int r, const unsigned int c, const GeoMatrix &m)
{
    unsigned int rows = m.Rows();
    unsigned int cols = m.Cols();

    for (unsigned int i = 0; i < rows; i++)
    {
        for (unsigned int j = 0; j < cols; j++)
        {
            m_data[i + r][j + c] = m[i][j];
        }
    }
}

void GeoMatrix::Dump() const
{
    std::cout.precision(5);
    for (unsigned int i = 0; i < m_row; i++)
    {
        for (unsigned int j = 0; j < m_col; j++)
        {
            std::cout << m_data[i][j] << "  ";
        }

        std::cout << std::endl;
    }
}

unsigned int GeoMatrix::Rows() const
{
    return m_row;
}

unsigned int GeoMatrix::Cols() const
{
    return m_col;
}

bool GeoMatrix::LUDecompose(GeoMatrix &up, GeoMatrix &low)
{
    assert(m_col == m_row);

    if (Tools::GetInstance()->IsZero(m_data[0][0]))
    {
        return false;
    }

    up.Resharp(m_row, m_col);
    low.Resharp(m_row, m_col);

    low.SetIdentity();

    // the first row of up-triangle matrix is equal to
    // the first row of the raw matrix
    for (unsigned int j = 0; j < m_col; j++)
    {
        up[0][j] = m_data[0][j];
        low[j][0] = m_data[j][0] / up[0][0];
    }

    double sum;

    for (size_t i = 1; i < m_row; i++)
    {
        for (size_t j = 1; j < m_col; j++)
        {
            sum = 0.0f;
            for (size_t k = 0; k < i - 1; k++)
            {
                sum += low[i][k] * up[k][j];
            }

            up[i][j] = m_data[i][j] - sum;

            if ((i == j) && (Tools::GetInstance()->IsZero(up[i][j])))
            {
                return false;
            }
        }
    }

    for (size_t i = 1; i < m_row; i++)
    {
        for (size_t j = 1; j < m_col; j++)
        {
            sum = 0.0f;
            for (size_t k = 0; k < j - 1; k++)
            {
                sum += low[i][k] * up[k][j];
            }

            low[i][j] = (m_data[i][j] - sum) * (1 / up[j][j]);
        }
    }

    return true;
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

    Zeros();
}

GeoMatrix GeoMatrix::TranslateMatrix(const GeoVector3D &trans)
{
    GeoMatrix matrix(4, 4);

    matrix[0][3] = trans[0];
    matrix[1][3] = trans[1];
    matrix[2][3] = trans[2];

    return matrix;
}

GeoMatrix GeoMatrix::RotateMatrix(const double angle, const GeoVector3D &axis)
{
    GeoMatrix matrix(4, 4);

    double c = cos(angle);
    double s = sin(angle);

    matrix[0][0] = c + (1 - c) * axis[0] * axis[0];
    matrix[0][1] = (1 - c) * axis[0] * axis[1] - s * axis[2];
    matrix[0][2] = (1 - c) * axis[0] * axis[2] + s * axis[1];

    matrix[1][0] = (1 - c) * axis[0] * axis[1] + s * axis[2];
    matrix[1][1] = c + (1 - c) * axis[1] * axis[1];
    matrix[1][2] = (1 - c) * axis[1] * axis[2] - s * axis[0];

    matrix[2][0] = (1 - c) * axis[0] * axis[2] - s * axis[1];
    matrix[2][1] = (1 - c) * axis[1] * axis[2] + s * axis[0];
    matrix[2][2] = c + (1 - c) * axis[2] * axis[2];

    matrix[3][3] = 1.0f;

    return matrix;
}