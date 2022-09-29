#include "Coord.hpp"
#include <cwchar>
#include <iostream>
#include "ACTReader.hpp"

#include <fstream>
#include "CellGrid.hpp"

#include <algorithm>
#include <numeric>

#include <filesystem>
#include <string_view>

#include "MassAuditReader.hpp"
#include "MassCase.hpp"


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


    // std::shared_ptr<ACT_File> act_file = ACT_Reader::readFile("testfiles/Sleipner_Dist_369_0015.act");

    // auto &extents = act_file->extents;

    // std::cout << extents << std::endl;

    // std::size_t elementsPerSlice = extents.get<0>() * extents.get<1>();
    // std::size_t elementsTotal = elementsPerSlice * extents.get<2>();


    // CellGrid grid{extents};

    // grid.print();

    // std::vector<CellData> vec = *act_file->cellData;

    // for ( auto & x : vec )
    // {
    //     grid.atIndex(x.index) = x;
    //     grid.setValid(x.index);
    // }

    // for ( auto &x : layers )
    // {
    //     averagePTH(grid,
    //             std::get<0>(x),
    //             std::get<1>(x),
    //             std::get<2>(x));
    // }


    const std::filesystem::path testfiles{"testfiles"};

    std::vector<MassCase> cases;

    for ( auto const &dir_entry : std::filesystem::directory_iterator(testfiles) )
    {

        std::string filename = dir_entry.path();
        std::string fullFileName = filename;

        if ( fullFileName.find(".tsv") == std::string::npos ) continue;

        std::string needle = "testfiles/";
        auto s = filename.find("testfiles/");
        filename.replace(0, needle.length(), "");

        std::cout << filename << "\n";

        std::string extension = ".tsv";


        std::string noExtension = filename.substr(filename.find_last_of("_")+1);
        noExtension = noExtension.substr(0,noExtension.find("."));

        int caseNumber = std::stoi(noExtension);
        std::cout << caseNumber << std::endl;

        MassAuditReader mar{fullFileName};

        auto rows = mar.getRows();

        MassCase mac{caseNumber, rows};
        cases.push_back(std::move(mac));

    }

    std::fstream aggregate_fh{"aggregate.tsv", std::ios::out};

    aggregate_fh << cases[0].getCSVHeader() << std::endl;


    // std::cout << cases[0].getCSVHeader() << std::endl;

    for ( auto & x : cases )
    {
        aggregate_fh << x.getCSVRow() << "\n";
    }



}
