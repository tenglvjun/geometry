#if !defined(__MATRIX_HEAD_FILE__)
#define __MATRIX_HEAD_FILE__

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

  public:
    bool SetIdentity();

  protected:
    void Clear();
    void Init(const unsigned int row, const unsigned int col);

  private:
    GeoMatrix();

  private:
    unsigned int m_row;
    unsigned int m_col;
    double **m_data;
};

#endif // __MATRIX_HEAD_FILE__
