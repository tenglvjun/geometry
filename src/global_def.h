#if !defined(__GLOBAL_DEF_HEAD_FILE__)
#define __GLOBAL_DEF_HEAD_FILE__

#if !defined(PI)
#define PI 3.14159265358979323846
#endif // PI

#if !defined(EPSILON)
#define EPSILON 1e-7
#endif // EPSILON

#if !defined(SAFE_DELETE)
#define SAFE_DELETE(p) \
    if (p)             \
    {                  \
        delete p;      \
        p = nullptr;   \
    }
#endif // SAFE_DELETE

#if !defined(SAFE_DELETE_ARRAY)
#define SAFE_DELETE_ARRAY(p) \
    if (p)                   \
    {                        \
        delete[] p;          \
        p = nullptr;         \
    }
#endif // SAFE_DELETE_ARRAY

#if !defined(SINGLETON_DECLARE)
#define SINGLETON_DECLARE(CLASSNAME) \
    static CLASSNAME *GetInstance();
#endif // SINGLETON_DECLARE

#if !defined(SINGLETON_IMPLEMENT)
#define SINGLETON_IMPLEMENT(CLASSNAME)         \
    CLASSNAME *CLASSNAME::GetInstance()        \
    {                                          \
        static CLASSNAME *_instance = nullptr; \
        if (nullptr == _instance)              \
        {                                      \
            _instance = new CLASSNAME;         \
        }                                      \
        return _instance;                      \
    }
#endif // SINGLETON_IMPLEMENT

#endif // __GLOBAL_DEF_HEAD_FILE__