#if !defined(__COLOR_HEAD_FILE__)
#define __COLOR_HEAD_FILE__

class GeoColor
{
public:
  GeoColor();
  GeoColor(const double r, const double g, const double b, const double a);
  GeoColor(const GeoColor &color);
  virtual ~GeoColor();

public:
  GeoColor &operator=(const GeoColor &color);
  double operator[](const unsigned int idx) const;
  double &operator[](const unsigned int idx);

public:
  static unsigned int Size();

protected:
  double m_rgba[4];
};

#endif // __COLOR_HEAD_FILE__