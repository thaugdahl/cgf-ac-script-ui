#ifndef PATHWAYCELLDATA_HPP
#define PATHWAYCELLDATA_HPP

#include <cstdint>
#include <string>
#include <iostream>
#include <sstream>

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

    std::string csvHeader()
    {
        std::ostringstream ss{};
    ss << "index" << "\t"
    << "sub_index" << "\t"
    << "porosity" << "\t"
    << "invasion_sequence" << "\t"
    << "invade_temp" << "\t"
    << "invade_press" << "\t"
    << "paleo_filling_fraction" << "\t"
    << "bulk_volume" << "\t"
    << "paleo_z" << "\t"
    << "paleo_crit" << "\t"
    << "pristine_crit" << "\t"
    << "last_expulsion_index" << "\t"
    << "last_expulsion_sub_index" << "\t"
    << "species_00" << "\t"
    << "species_01" << "\t"
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
            << paleo_filling_fraction << "\t"
            << bulk_volume << "\t"
            << paleo_z << "\t"
            << paleo_crit << "\t"
            << pristine_crit << "\t"
            << last_expulsion_index << "\t"
            << last_expulsion_sub_index << "\t"
            << species_00 << "\t"
            << species_01 << "\t"
            << scaled_socr << "\t"
            << socr << "\t"
            << swc << "\t"
            << pthx << "\t"
            << pthz << "\t";

        return ss.str();
    }
};

#endif

