#if !defined(__MATRIX_HEAD_FILE__)
#define __MATRIX_HEAD_FILE__

#include "vector.h"
#include <vector>

class GeoMatrix
{
public:
  GeoMatrix(const unsigned int row, const unsigned int col);
  GeoMatrix(const unsigned int row, const unsigned int col, const double *data);
  GeoMatrix(const GeoMatrix &m);
  virtual ~GeoMatrix();

public:
  GeoMatrix &operator=(const GeoMatrix &m);
  double *operator[](const unsigned int idx) const;
  double *operator[](const unsigned int idx);
  GeoVector3D operator*(const GeoVector3D &v) const;
  GeoVector2D operator*(const GeoVector2D &v) const;
  GeoVector4D operator*(const GeoVector4D &v) const;
  GeoMatrix operator*(const GeoMatrix &m) const;
  void operator*=(const double s);
  GeoMatrix operator*(const double s);
  void operator+=(const GeoMatrix &m);

public:
  void Resharp(const unsigned int row, const unsigned int col);
  void SetIdentity();
  void Zeros();
  void Flatten(std::vector<float> &data) const;
  GeoMatrix SubMatrix(const unsigned int sRow, const unsigned int eRow, const unsigned int sCol, const unsigned int eCol);
  unsigned int Rows() const;
  unsigned int Cols() const;
  bool LUDecompose(GeoMatrix &up, GeoMatrix &low) const;
  double Det() const;
  bool Inverse(GeoMatrix &inverse) const;
  bool IsSquare() const;
  GeoMatrix &Transpose();
  void Transpose(GeoMatrix &transpose) const;
  void SetVector(const unsigned int idx, const GeoVector &v, bool isRow);
  bool SolveLinearEquation(const GeoVector &b, GeoVector &x) const;

public:
  void Dump() const;

protected:
  void Clear();
  void Init(const unsigned int row, const unsigned int col);

private:
  GeoMatrix();

public:
  static GeoMatrix TranslateMatrix(const GeoVector3D &trans);
  static GeoMatrix TranslateMatrix(const GeoVector4D &trans);
  static GeoMatrix RotateMatrix(const double angle, const GeoVector3D &axis);
  static GeoMatrix ScaleMatrix(const double s);
  static GeoVector SolveLinearEquation(const GeoMatrix &up, const GeoMatrix &low, const GeoVector &b);

private:
  unsigned int m_row;
  unsigned int m_col;
  double **m_data;
};

GeoVector4D operator*(const GeoVector4D &v, const GeoMatrix &m);
GeoVector3D operator*(const GeoVector3D &v, const GeoMatrix &m);
GeoVector2D operator*(const GeoVector2D &v, const GeoMatrix &m);

#endif // __MATRIX_HEAD_FILE__
