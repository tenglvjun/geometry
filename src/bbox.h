#if !defined(__BOUNDING_BOX_HEAD_FILE__)
#define __BOUNDING_BOX_HEAD_FILE__

#include "vertex.h"

class GeoBBox
{
  public:
    GeoBBox();
    GeoBBox(const GeoVector3D &center, const GeoVector3D &min, const GeoVector3D &max);
    GeoBBox(const GeoBBox &box);
    virtual ~GeoBBox();

  public:
    GeoBBox &operator=(const GeoBBox &box);

  public:
    void CalBBox(std::vector<GeoVertex> &vertices);
    const GeoVector3D &GetMax() const;
    const GeoVector3D &GetMin() const;
    const GeoVector3D &GetCenter() const;

  protected:
    GeoVector3D m_center;
    GeoVector3D m_max;
    GeoVector3D m_min;
};

#endif // __BOUNDING_BOX_HEAD_FILE__
