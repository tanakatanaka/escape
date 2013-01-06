#ifndef VECTOR_OPERATOR_H_
#define VECTOR_OPERATOR_H_

/* vector‚É‰‰ŽZŽq‚Ì’è‹` */

inline VECTOR &operator +=(VECTOR &a, const VECTOR &b)
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return a;
}

inline VECTOR &operator -=(VECTOR &a, const VECTOR &b)
{
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    return a;
}

inline VECTOR &operator *=(VECTOR &a, float b)
{
    a.x *= b;
    a.y *= b;
    a.z *= b;
    return a;
}

inline VECTOR &operator /=(VECTOR &a, float b)
{
    a.x /= b;
    a.y /= b;
    a.z /= b;
    return a;
}

inline VECTOR operator +(const VECTOR &a, const VECTOR &b)
{
    VECTOR c(a);
    c += b;
    return c;
}

inline VECTOR operator -(const VECTOR &a, const VECTOR &b)
{
    VECTOR c(a);
    c -= b;
    return c;
}

inline VECTOR operator *(const VECTOR &a, float b)
{
    VECTOR c(a);
    c *= b;
    return c;
}

inline VECTOR operator /(const VECTOR &a, float b)
{
    VECTOR c(a);
    c /= b;
    return c;
}

#endif /* !defined(VECTOR_OPERATOR_H_) */
