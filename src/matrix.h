#if !defined(__MATRIX_HEAD_FILE__)
#define __MATRIX_HEAD_FILE__

#include "vector.h"

class GeoMatrix
{
public:
  GeoMatrix(const unsigned int row, const unsigned int col);
  GeoMatrix(const GeoMatrix &m);
  virtual ~GeoMatrix();

public:
  GeoMatrix &operator=(const GeoMatrix &m);
  double *operator[](const unsigned int idx) const;
  double *operator[](const unsigned int idx);
  GeoVector3D operator*(const GeoVector3D &v);
  GeoVector2D operator*(const GeoVector2D &v);

public:
  void SetIdentity();

protected:
  void Clear();
  void Init(const unsigned int row, const unsigned int col);

private:
  GeoMatrix();

public:
  static GeoMatrix RotateMatrix(const double angle, const GeoVector3D &axis);

private:
  unsigned int m_row;
  unsigned int m_col;
  double **m_data;
};

#endif // __MATRIX_HEAD_FILE__
