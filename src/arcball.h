#if !defined(__ARC_BALL_HEAD_FILE__)
#define __ARC_BALL_HEAD_FILE__

#include "vector.h"
#include "matrix.h"

class GeoArcBall
{
public:
  GeoArcBall();
  GeoArcBall(const GeoArcBall &ball);
  virtual ~GeoArcBall();

public:
  GeoArcBall &operator=(const GeoArcBall &ball);

public:
  GeoVector3D ProjectToSphere(const GeoVector3D &pt);
  GeoMatrix GetRotateMatrix(const GeoVector3D &s, const GeoVector3D &e);

protected:
  GeoVector3D m_center;
  double m_radius;
};

#endif // __ARC_BALL_HEAD_FILE__
