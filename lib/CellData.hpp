#ifndef CELLDATA_HPP
#define CELLDATA_HPP

#include <cstdint>
#include <string>
#include <iostream>
#include <sstream>

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

    void print() const
    {
        std::cout << "=====Cell Data====" << "\n";
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

    std::string csvHeader()
    {

        std::ostringstream ss{};
    ss << "index" << "\t"
    << "sub_index" << "\t"
    << "porosity" << "\t"
    << "invasion_sequence" << "\t"
    << "invade_temp" << "\t"
    << "invade_press" << "\t"
    << "path_index" << "\t"
    << "vapor_liquid_z" << "\t"
    << "meniscus_theta" << "\t"
    << "meniscus_phi" << "\t"
    << "paleo_crit" << "\t"
    << "pristine_crit" << "\t"
    << "paleo_z" << "\t"
    << "paleo_filling_fraction" << "\t"
    << "bulk_volume" << "\t"
    << "is_dry" << "\t"
    << "cap_pressure" << "\t"
    << "saturation_0_z" << "\t"
    << "liq_vol_0" << "\t"
    << "vap_vol_0" << "\t"
    << "brv_0" << "\t"
    << "scaled_socr" << "\t"
    << "socr" << "\t"
    << "swc" << "\t"
    << "pthx" << "\t"
    << "pthz" << "\t";

    return ss.str();

    }

    std::string printCSV()
    {
        std::ostringstream ss{};
    ss << index << "\t"
    << sub_index << "\t"
    << porosity << "\t"
    << invasion_sequence << "\t"
    << invade_temp << "\t"
    << invade_press << "\t"
    << path_index << "\t"
    << vapor_liquid_z << "\t"
    << meniscus_theta << "\t"
    << meniscus_phi << "\t"
    << paleo_crit << "\t"
    << pristine_crit << "\t"
    << paleo_z << "\t"
    << paleo_filling_fraction << "\t"
    << bulk_volume << "\t"
    << is_dry << "\t"
    << cap_pressure << "\t"
    << saturation_0_z << "\t"
    << liq_vol_0 << "\t"
    << vap_vol_0 << "\t"
    << brv_0 << "\t"
    << scaled_socr << "\t"
    << socr << "\t"
    << swc << "\t"
    << pthx << "\t"
    << pthz << "\t";

    return ss.str();

    }
};

#endif CELLDATA_HPP

