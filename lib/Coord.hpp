#ifndef COORD_HPP
#define COORD_HPP

#include <stdexcept>
#include <math.h>
#include <array>
#include <iostream>

template <typename T>
struct Coord;

template <typename T>
std::ostream &operator<< (std::ostream &os, const Coord<T> &coord);


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

    friend std::ostream &operator<< <T>(std::ostream &os, const Coord<T> &coord);
    
    

    template <
        int idx> // Enable only if idx < 3
    T get() const
    {
        static_assert(idx < 3, "Trying to access invalid index");
        return this->*idents[idx];
    }

    ///< Gets the norm of the coordinate vector.
    ///< Otherwise expressible as the euclidean distance from the origin.
    T norm();

    static Coord<T> fromBinary(unsigned char *buf);
    
    // TODO: Make a serialize / print function


    T x = static_cast<T>(0);
    T y = static_cast<T>(0);
    T z = static_cast<T>(0);

    static constexpr std::array<T Coord<T>::*, 3> idents = {
        &Coord<T>::x,
        &Coord<T>::y,
        &Coord<T>::z
    };
    
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const Coord<T> &coord)
{
     os << "(" << coord.template get<0>() << ", " << coord.template get<1>() << ", " << coord.template get<2>() << ")";
     return os;
}


#endif
