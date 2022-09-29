#include "Coord.hpp"

template <typename T>
Coord<T>::Coord(T _x, T _y, T _z)
    : x{_x}, y{_y}, z{_z}
{ }


template <typename T>
Coord<T>::Coord(const Coord<T> &other)
    : x{other.x}, y{other.y}, z{other.z}
{ }

template <typename T>
Coord<T>::Coord(Coord<T> &&other)
    : x{other.x}, y{other.y}, z{other.z}
{ }

template <typename T>
Coord<T> &Coord<T>::operator=(const Coord<T> &other)
{
    x = other.x;
    y = other.y;
    z = other.z;

    return *this;
}

template <typename T>
Coord<T> &Coord<T>::operator=(Coord<T> &&other)
{
    x = other.x;
    y = other.y;
    z = other.z;

    return *this;
}

template <typename T>
T Coord<T>::norm()
{
    return std::sqrt(x*x + y*y + z*z);
}

template <typename T>
Coord<T> Coord<T>::fromBinary(unsigned char *buf)
{
    Coord<T> result{};

    result.x = *(reinterpret_cast<T *>(buf) + 0);
    result.y = *(reinterpret_cast<T *>(buf) + 1);
    result.z = *(reinterpret_cast<T *>(buf) + 2);

    return result;
}

template struct Coord<float>;
template struct Coord<double>;
template struct Coord<int>;


