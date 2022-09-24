#include "coord.hpp"
#include <iostream>
#include "act_reader.hpp"

#include <fstream>
#include "cell_grid.hpp"


void exportACTFiles(std::shared_ptr<ACT_File> act_file)
{
    std::ofstream fh{"pwcelldata.csv", std::ios::out};
    if ( ! fh.is_open() )
        throw std::runtime_error("Failed to open pwcelldata.csv");

    fh << (*(act_file->pathwayCellData))[0].csvHeader() << std::endl;
    

    for ( auto &x : *(act_file->pathwayCellData) )
    {
        fh << x.printCSV() << std::endl;
    }

    fh.close();

    fh = std::ofstream{"celldata.csv", std::ios::out};

    if ( ! fh.is_open() )
        throw std::runtime_error("Failed to open celldata.csv");

    fh << (*(act_file->cellData))[0].csvHeader() << std::endl;
    

    for ( auto &x : *(act_file->cellData) )
    {
        fh << x.printCSV() << std::endl;
    }
    fh.close();

}

int main()
{

    std::shared_ptr<ACT_File> act_file = ACT_Reader::readFile("testfiles/test.act");

    auto &extents = act_file->extents;

    std::cout << extents << std::endl;

    std::size_t elementsPerSlice = extents.get<0>() * extents.get<1>();
    std::size_t elementsTotal = elementsPerSlice * extents.get<2>();


    CellGrid grid{extents};
}
