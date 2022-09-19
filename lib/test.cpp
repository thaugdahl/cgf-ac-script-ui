#include "coord.hpp"
#include <iostream>
#include "act_reader.hpp"

int main()
{

    ACT_Reader reader{"testfiles/test.act"};
    std::shared_ptr<ACT_File> act_file = reader.read();
    
}
