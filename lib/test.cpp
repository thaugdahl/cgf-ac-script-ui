#include "coord.hpp"
#include <iostream>

int main()
{

    Coord<float> test{1.0f, 2.0f, 3.0f};

    std::cout << test.get<0>() << " " << test.get<1>() << " " << test.get<2>() << std::endl;

    std::cout << test.norm() << std::endl;

    int tempBuf[6] = {
        1,
        2,
        3,
        4,
        5,
        6
    };

    unsigned char *buf = reinterpret_cast<unsigned char *>(tempBuf + 3);

    auto coord = Coord<int>::fromBinary(buf);

    std::cout << coord.get<0>() << " " << coord.get<1>() << " " << coord.get<2>() << std::endl;

}
