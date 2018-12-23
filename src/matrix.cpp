#include "matrix.h"
#include "global_def.h"
#include <memory.h>
#include <assert.h>

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

bool GeoMatrix::SetIdentity()
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