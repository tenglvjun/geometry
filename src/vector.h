#if !defined(__VECTOR_HEAD_FILE__)
#define __VECTOR_HEAD_FILE__

#include <vector>

class GeoVector2D
{
public:
  GeoVector2D();
  GeoVector2D(const double x, const double y);
  GeoVector2D(const GeoVector2D &v);
  virtual ~GeoVector2D();

public:
  GeoVector2D &operator=(const GeoVector2D &v);
  double operator[](const unsigned int idx) const;
  double &operator[](const unsigned int idx);
  GeoVector2D &operator+=(const GeoVector2D &v);
  GeoVector2D operator+(const GeoVector2D &v);
  GeoVector2D operator*(const double scale) const;
  GeoVector2D &operator*=(const double scale);
  GeoVector2D operator-(const GeoVector2D &v) const;
  GeoVector2D &operator-=(const GeoVector2D &v);
  bool operator==(const GeoVector2D &v);
  double operator%(const GeoVector2D &v) const;

public:
  void Normalize();
  double Magnitude() const;
  double Magnitude2() const;
  GeoVector2D ProjectTo(const GeoVector2D &v);
  void Flatten(std::vector<float> &data) const;
  void Dump() const;

public:
  static unsigned int
  Size();

protected:
  double m_coord[2];
};

class GeoVector3D
{
public:
  GeoVector3D();
  GeoVector3D(const double x, const double y, const double z);
  GeoVector3D(const GeoVector3D &v);
  virtual ~GeoVector3D();

public:
  GeoVector3D &operator=(const GeoVector3D &v);
  double operator[](const unsigned int idx) const;
  double &operator[](const unsigned int idx);
  GeoVector3D &operator+=(const GeoVector3D &v);
  GeoVector3D operator+(const GeoVector3D &v);
  GeoVector3D operator*(const double scale) const;
  GeoVector3D &operator*=(const double scale);
  GeoVector3D operator-(const GeoVector3D &v) const;
  GeoVector3D &operator-=(const GeoVector3D &v);
  double operator%(const GeoVector3D &v) const;
  GeoVector3D operator*(const GeoVector3D &v) const;
  bool operator==(const GeoVector3D &v);

public:
  void Normalize();
  double Magnitude() const;
  double Magnitude2() const;
  GeoVector3D ProjectTo(const GeoVector3D &v);
  void Flatten(std::vector<float> &data) const;
  void Dump() const;

public:
  static unsigned int Size();

protected:
  double m_coord[3];
};

class GeoVector4D
{
public:
  GeoVector4D();
  GeoVector4D(const double x, const double y, const double z, const double w);
  GeoVector4D(const GeoVector4D &v);
  GeoVector4D(const GeoVector3D &v, const double w);
  virtual ~GeoVector4D();

public:
  GeoVector4D &operator=(const GeoVector4D &v);
  double operator[](const unsigned int idx) const;
  double &operator[](const unsigned int idx);
  GeoVector4D &operator+=(const GeoVector4D &v);
  GeoVector4D operator+(const GeoVector4D &v);
  GeoVector4D operator*(const double scale) const;
  GeoVector4D &operator*=(const double scale);
  GeoVector4D operator-(const GeoVector4D &v) const;
  GeoVector4D &operator-=(const GeoVector4D &v);
  bool operator==(const GeoVector4D &v);

public:
  void Normalize();
  double Magnitude() const;
  double Magnitude2() const;
  void Flatten(std::vector<float> &data) const;
  void Dump() const;

public:
  static unsigned int Size();

protected:
  double m_coord[4];
};

class GeoVector
{
public:
  GeoVector();
  GeoVector(const unsigned int len, const double *data = nullptr);
  GeoVector(const GeoVector &v);
  virtual ~GeoVector();

public:
  GeoVector &operator=(const GeoVector &v);
  double operator[](const unsigned int idx) const;
  double &operator[](const unsigned int idx);
  GeoVector &operator+=(const GeoVector &v);
  GeoVector operator+(const GeoVector &v);
  GeoVector operator*(const double scale) const;
  GeoVector &operator*=(const double scale);
  GeoVector operator-(const GeoVector &v) const;
  GeoVector &operator-=(const GeoVector &v);

public:
  void Normalize();
  double Magnitude() const;
  double Magnitude2() const;
  void Flatten(std::vector<float> &data) const;
  unsigned int Dim() const;

public:
  void Dump() const;

protected:
  void Clear();

protected:
  unsigned int m_dim;
  double *m_coord;
};

#endif // __VECTOR_HEAD_FILE__
