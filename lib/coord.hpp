#ifndef COORD_HPP
#define COORD_HPP

#include <stdexcept>
#include <math.h>
#include <array>

template <typename T>
struct Coord
{

    Coord() = default;
    Coord(T _x, T _y, T _z);
    ~Coord() = default;

    // Copy Constructor
    Coord(const Coord<T> &other);

    // Move Constructor
    Coord(Coord<T> &&other);

    // Copy Assignment
    Coord &operator=(const Coord<T> &other);

    // Move Assignment
    Coord &operator=(Coord<T> &&other);

    template <
        int idx> // Enable only if idx < 3
    T get()
    {
        static_assert(idx < 3, "Trying to access invalid index");
        return this->*idents[idx];
    }

    ///< Gets the norm of the coordinate vector.
    ///< Otherwise expressible as the euclidean distance from the origin.
    T norm();

    static Coord<T> fromBinary(unsigned char *buf);
    


    T x = static_cast<T>(0);
    T y = static_cast<T>(0);
    T z = static_cast<T>(0);

    static constexpr std::array<T Coord<T>::*, 3> idents = {
        &Coord<T>::x,
        &Coord<T>::y,
        &Coord<T>::z
    };
    
};

#endif
