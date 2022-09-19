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
};


struct ACT_File
{

    ACT_File() {}
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
    void readBinaryTable(std::vector<T> &vec);

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

