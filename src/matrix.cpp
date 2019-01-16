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

void GeoMatrix::operator*=(const double s)
{
    for (unsigned int i = 0; i < m_row; i++)
    {
        for (unsigned int j = 0; j < m_col; j++)
        {
            m_data[i][j] *= s;
        }
    }
}

GeoMatrix GeoMatrix::operator*(const double s)
{
    GeoMatrix ret(m_row, m_col);

    for (unsigned int i = 0; i < m_row; i++)
    {
        for (unsigned int j = 0; j < m_col; j++)
        {
            ret[i][j] *= s;
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

bool GeoMatrix::LUDecompose(GeoMatrix &up, GeoMatrix &low) const
{
    if (!IsSquare())
    {
        return false;
    }

    up.Resharp(m_row, m_col);
    low.Resharp(m_row, m_col);

    unsigned int n = m_row;
    double sum;

    for (unsigned int i = 0; i < n; i++)
    {
        // Upper Triangular
        for (unsigned int k = i; k < n; k++)
        {
            // Summation of L(i, j) * U(j, k)
            sum = 0.0f;
            for (unsigned int j = 0; j < i; j++)
                sum += (low[i][j] * up[j][k]);

            // Evaluating U(i, k)
            up[i][k] = m_data[i][k] - sum;

            if ((i == k) && (Tools::GetInstance()->IsZero(up[i][k])))
            {
                return false;
            }
        }

        // Lower Triangular
        for (unsigned int k = i; k < n; k++)
        {
            if (i == k)
            {
                low[i][i] = 1; // Diagonal as 1
            }
            else
            {

                // Summation of L(k, j) * U(j, i)
                sum = 0;
                for (unsigned int j = 0; j < i; j++)
                {
                    sum += (low[k][j] * up[j][i]);
                }

                // Evaluating L(k, i)
                low[k][i] = (m_data[k][i] - sum) / up[i][i];
            }
        }
    }

    return true;
}

double GeoMatrix::Det() const
{
    GeoMatrix up(m_row, m_col);
    GeoMatrix low(m_row, m_col);

    if (!LUDecompose(up, low))
    {
        return 0;
    }

    double det = 1.0f;

    for (size_t i = 0; i < m_row; i++)
    {
        det *= up[i][i];
    }

    return det;
}

bool GeoMatrix::Inverse(GeoMatrix &inverse) const
{

    GeoMatrix up(m_row, m_col);
    GeoMatrix low(m_row, m_col);

    if (!LUDecompose(up, low))
    {
        return false;
    }

    GeoMatrix l_inverse(m_row, m_col);
    GeoMatrix u_inverse(m_row, m_col);
    double s = 0.0f;

    for (int i = 0; i < m_row; i++)
    {
        u_inverse[i][i] = 1 / up[i][i];
        for (int k = i - 1; k >= 0; k--)
        {
            s = 0;
            for (int j = k + 1; j <= i; j++)
                s = s + up[k][j] * u_inverse[j][i];
            u_inverse[k][i] = -s / up[k][k];
        }
    }
    for (int i = 0; i < m_row; i++)
    {
        l_inverse[i][i] = 1;
        for (int k = i + 1; k < m_row; k++)
        {
            for (int j = i; j <= k - 1; j++)
            {
                l_inverse[k][i] = l_inverse[k][i] - low[k][j] * l_inverse[j][i];
            }
        }
    }

    inverse = u_inverse * l_inverse;

    return true;
}

bool GeoMatrix::IsSquare() const
{
    assert((m_col > 0) && (m_col > 0));

    return (m_col == m_row);
}

void GeoMatrix::Transpose()
{
    assert((m_col > 0) && (m_col > 0));

    GeoMatrix tmp(m_col, m_row);
    Transpose(tmp);

    (*this) = (tmp);
}

void GeoMatrix::Transpose(GeoMatrix &transpose) const
{
    transpose.Resharp(m_col, m_row);

    for (size_t row = 0; row < m_row; row++)
    {
        for (size_t col = 0; col < m_col; col++)
        {
            transpose[col][row] = m_data[row][col];
        }
    }
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