#ifndef ACT_READER
#define ACT_READER

#include <cstdint>
#include <vector>
#include <memory>
#include <string>
#include "coord.hpp"

#include <fstream>
#include <sstream>
#include <iostream>
#include <string_view>

struct PathwayCellData
{
    int32_t index;
    int32_t sub_index;
    float   porosity;
    int32_t invasion_sequence;
    float   invade_temp;
    float   invade_press;
    float   paleo_filling_fraction;
    float   bulk_volume;
    float   paleo_z;
    float   paleo_crit;
    float   pristine_crit;
    int32_t last_expulsion_index;
    int32_t last_expulsion_sub_index;
    float   species_00;
    float   species_01;
    float   scaled_socr;
    float   socr;
    float   swc;
    float   pthx;
    float   pthz;

    void print()
    {
        std::cout << "=====Pathway Cell Data====" << "\n";
        std::cout << "index: " << index << "\n";
        std::cout << "sub_index: " << sub_index << "\n";
        std::cout << "porosity: " << porosity << "\n";
        std::cout << "invasion_sequence: " << invasion_sequence << "\n";
        std::cout << "invade_temp: " << invade_temp << "\n";
        std::cout << "invade_press: " << invade_press << "\n";
        std::cout << "paleo_filling_fraction: " << paleo_filling_fraction << "\n";
        std::cout << "bulk_volume: " << bulk_volume << "\n";
        std::cout << "paleo_z: " << paleo_z << "\n";
        std::cout << "paleo_crit: " << paleo_crit << "\n";
        std::cout << "pristine_crit: " << pristine_crit << "\n";
        std::cout << "last_expulsion_index: " << last_expulsion_index << "\n";
        std::cout << "last_expulsion_sub_index: " << last_expulsion_sub_index << "\n";
        std::cout << "species_00: " << species_00 << "\n";
        std::cout << "species_01: " << species_01 << "\n";
        std::cout << "scaled_socr: " << scaled_socr << "\n";
        std::cout << "socr: " << socr << "\n";
        std::cout << "swc: " << swc << "\n";
        std::cout << "pthx: " << pthx << "\n";
        std::cout << "pthz: " << pthz << "\n";
    }
};

struct CellData
{
    int32_t index;
    int32_t sub_index;
    float   porosity;
    int32_t invasion_sequence;
    float   invade_temp;
    float   invade_press;
    int32_t path_index;
    float   vapor_liquid_z;
    float   meniscus_theta;
    float   meniscus_phi;
    float   paleo_crit;
    float   pristine_crit;
    float   paleo_z;
    float   paleo_filling_fraction;
    float   bulk_volume;
    int32_t is_dry;
    float   cap_pressure;
    float   saturation_0_z;
    float   liq_vol_0;
    float   vap_vol_0;
    float   brv_0;
    float   scaled_socr;
    float   socr;
    float   swc;
    float   pthx;
    float   pthz;

    void print()
    {
        std::cout << "index: " << index << "\n";
        std::cout << "sub_index: " << sub_index << "\n";
        std::cout << "porosity: " << porosity << "\n";
        std::cout << "invasion_sequence: " << invasion_sequence << "\n";
        std::cout << "invade_temp: " << invade_temp << "\n";
        std::cout << "invade_press: " << invade_press << "\n";
        std::cout << "path_index: " << path_index << "\n";
        std::cout << "vapor_liquid_z: " << vapor_liquid_z << "\n";
        std::cout << "meniscus_theta: " << meniscus_theta << "\n";
        std::cout << "meniscus_phi: " << meniscus_phi << "\n";
        std::cout << "paleo_crit: " << paleo_crit << "\n";
        std::cout << "pristine_crit: " << pristine_crit << "\n";
        std::cout << "paleo_z: " << paleo_z << "\n";
        std::cout << "paleo_filling_fraction: " << paleo_filling_fraction << "\n";
        std::cout << "bulk_volume: " << bulk_volume << "\n";
        std::cout << "is_dry: " << is_dry << "\n";
        std::cout << "cap_pressure: " << cap_pressure << "\n";
        std::cout << "saturation_0_z: " << saturation_0_z << "\n";
        std::cout << "liq_vol_0: " << liq_vol_0 << "\n";
        std::cout << "vap_vol_0: " << vap_vol_0 << "\n";
        std::cout << "brv_0: " << brv_0 << "\n";
        std::cout << "scaled_socr: " << scaled_socr << "\n";
        std::cout << "socr: " << socr << "\n";
        std::cout << "swc: " << swc << "\n";
        std::cout << "pthx: " << pthx << "\n";
        std::cout << "pthz: " << pthz << "\n";
    }
};

struct BodyData
{
    int32_t index;
    int32_t acc_state;
    int32_t pet_phase;
    float   last_flash_temp;
    float   last_flash_press;
    float   liq_volume;
    float   vap_volume;
    float   min_z;
    float   crest_x;
    float   crest_y;
    float   owc_depth_proxy;
    float   liq_ift;
    float   liq_density;
    float   vap_ift;
    float   vap_density;
    float   free_water_level;
    float   liquid_species_00;
    float   liquid_species_01;
    float   vapor_species_00;
    float   vapor_species_01;

    void print()
    {
        std::cout << "index: " << index << "\n";
        std::cout << "acc_state: " << acc_state << "\n";
        std::cout << "pet_phase: " << pet_phase << "\n";
        std::cout << "last_flash_temp: " << last_flash_temp << "\n";
        std::cout << "last_flash_press: " << last_flash_press << "\n";
        std::cout << "liq_volume: " << liq_volume << "\n";
        std::cout << "vap_volume: " << vap_volume << "\n";
        std::cout << "min_z: " << min_z << "\n";
        std::cout << "crest_x: " << crest_x << "\n";
        std::cout << "crest_y: " << crest_y << "\n";
        std::cout << "owc_depth_proxy: " << owc_depth_proxy << "\n";
        std::cout << "liq_ift: " << liq_ift << "\n";
        std::cout << "liq_density: " << liq_density << "\n";
        std::cout << "vap_ift: " << vap_ift << "\n";
        std::cout << "vap_density: " << vap_density << "\n";
        std::cout << "free_water_level: " << free_water_level << "\n";
        std::cout << "liquid_species_00: " << liquid_species_00 << "\n";
        std::cout << "liquid_species_01: " << liquid_species_01 << "\n";
        std::cout << "vapor_species_00: " << vapor_species_00 << "\n";
        std::cout << "vapor_species_01: " << vapor_species_01 << "\n";
    }

};


struct ACT_File
{

    ACT_File();
    ~ACT_File() {}

    void print();

    std::size_t pathwaycelldata_length;
    std::size_t celldata_length;
    std::size_t bodydata_length;

    ///< The .din file this .act file was generated from
    std::string scenario;
    std::string description;
    int version;
    std::string pvt_file;
    float time;

    Coord<int> extents;
    Coord<float> origin;
    Coord<float> cellSize;


    std::shared_ptr<std::vector<PathwayCellData>> pathwayCellData;
    std::shared_ptr<std::vector<CellData>> cellData;
    std::shared_ptr<std::vector<BodyData>> bodyData;
};

class ACT_Reader
{
public:
    ACT_Reader() = delete;
    ACT_Reader(const std::string &_filename);
    ~ACT_Reader() {}

    std::shared_ptr<ACT_File> read();

    template <typename T>
    void readCoord(Coord<T> &coord);


    template <typename T>
    void readField(T &field);

    template <typename T>
    void readBinaryTable(std::vector<T> &vec, std::size_t num_elements);

private:
    std::string filename;

    std::ifstream fh;
    std::stringstream ss;
    std::string current_line;

    std::shared_ptr<ACT_File> result;

    void getNewLine();
    void skipLine();
    void skipLines(int n);

    bool isBinaryTableHeader();
    bool isEndFooter();

    
    


};



#endif

