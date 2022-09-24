#include "coord.hpp"
#include <iostream>
#include "act_reader.hpp"

#include <fstream>
#include "cell_grid.hpp"

#include <algorithm>
#include <numeric>


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

void averagePTH(CellGrid &grid, std::string description, int start, int end)
{
    std::vector<float> pth_x;
    std::vector<float> pth_z;

    for ( int z = start-1; z < end; z++ )
    {
        for ( int x = 0; x < grid.getDimensions().get<0>(); x++)
        {
            for ( int y = 0; y < grid.getDimensions().get<1>(); y++)
            {
                if ( grid.isValid(x,y,z) ) {
                    pth_x.push_back(grid.atCoordinate(x,y,z).pthx);
                    pth_z.push_back(grid.atCoordinate(x,y,z).pthz);
                }
            }
        }
    }

    std::sort(pth_x.begin(), pth_x.end());
    std::sort(pth_z.begin(), pth_z.end());

    float pth_x_sum = std::accumulate(pth_x.begin(), pth_x.end(), 0.0f);
    float pth_z_sum = std::accumulate(pth_z.begin(), pth_z.end(), 0.0f);

    float pth_x_mean = pth_x_sum / static_cast<float>(pth_x.size());
    float pth_z_mean = pth_z_sum / static_cast<float>(pth_z.size());

    float pth_x_quad_meandiff_sum = 0.0f;

    for ( auto &x : pth_x ) 
    {
        float test = x - pth_x_mean;
        // std::cout << test << std::endl;
        pth_x_quad_meandiff_sum += std::pow(test, 2.0f);
    }

    float pth_x_var = pth_x_quad_meandiff_sum / (pth_x.size() - 1);


    std::cout << "\n" << description << " (" << start << " - " << end << ")\n";
    std::cout << "PTH_X Mean: " << pth_x_mean << "\n";
    std::cout << "Var[PTH_X]: " << pth_x_var << "\n";
    std::cout << "SD[PTH_X]: " << std::sqrt(pth_x_var) << "\n";
}

int main()
{

    std::vector<std::tuple<std::string, int, int>> layers;

    layers.emplace_back("Thick Shale", 217, 232);
    layers.emplace_back("Intrashale 7", 198, 200);
    layers.emplace_back("Intrashale 6", 179, 181);
    layers.emplace_back("Intrashale 5", 159, 161);
    layers.emplace_back("Intrashale 4", 141, 143);
    layers.emplace_back("Intrashale 3", 115, 117);
    layers.emplace_back("Intrashale 2", 97, 99);
    layers.emplace_back("Intrashale 1", 59, 61);


    std::shared_ptr<ACT_File> act_file = ACT_Reader::readFile("testfiles/Sleipner_Dist_369_0015.act");

    auto &extents = act_file->extents;

    std::cout << extents << std::endl;

    std::size_t elementsPerSlice = extents.get<0>() * extents.get<1>();
    std::size_t elementsTotal = elementsPerSlice * extents.get<2>();


    CellGrid grid{extents};

    grid.print();

    std::vector<CellData> vec = *act_file->cellData;

    for ( auto & x : vec )
    {
        grid.atIndex(x.index) = x;
        grid.setValid(x.index);
    }

    for ( auto &x : layers )
    {
        averagePTH(grid,
                std::get<0>(x),
                std::get<1>(x),
                std::get<2>(x));
    }

}
