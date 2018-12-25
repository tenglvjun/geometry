#if !defined(__MATRIX_HEAD_FILE__)
#define __MATRIX_HEAD_FILE__

#include "vector.h"
#include <vector>

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
  GeoVector3D operator*(const GeoVector3D &v) const;
  GeoVector2D operator*(const GeoVector2D &v) const;
  GeoMatrix operator*(const GeoMatrix &m) const;

public:
  void SetIdentity();
  void Flatten(std::vector<float> &data) const;
  GeoMatrix SubMatrix(const unsigned int sRow, const unsigned int eRow, const unsigned int sCol, const unsigned int eCol);
  void Replace(const unsigned int r, const unsigned int c, const GeoMatrix &m);
  void Dump() const;
  unsigned int Rows() const;
  unsigned int Cols() const;

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
