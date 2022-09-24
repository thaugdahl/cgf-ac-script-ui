#ifndef BODYDATA_HPP
#define BODYDATA_HPP


#include <cstdint>
#include <string>
#include <iostream>
#include <sstream>

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
        std::cout << "=====Body Data====" << "\n";
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

    std::string csvHeader()
    {
        std::ostringstream ss{};

    ss << "index" << "\t"
    << "acc_state" << "\t"
    << "pet_phase" << "\t"
    << "last_flash_temp" << "\t"
    << "last_flash_press" << "\t"
    << "liq_volume" << "\t"
    << "vap_volume" << "\t"
    << "min_z" << "\t"
    << "crest_x" << "\t"
    << "crest_y" << "\t"
    << "owc_depth_proxy" << "\t"
    << "liq_ift" << "\t"
    << "liq_density" << "\t"
    << "vap_ift" << "\t"
    << "vap_density" << "\t"
    << "free_water_level" << "\t"
    << "liquid_species_00" << "\t"
    << "liquid_species_01" << "\t"
    << "vapor_species_00" << "\t"
    << "vapor_species_01" << "\t";
    return ss.str();
    }

    std::string printCSV()
    {
        std::ostringstream ss{};
        ss << index << "\t"
    << acc_state << "\t"
    << pet_phase << "\t"
    << last_flash_temp << "\t"
    << last_flash_press << "\t"
    << liq_volume << "\t"
    << vap_volume << "\t"
    << min_z << "\t"
    << crest_x << "\t"
    << crest_y << "\t"
    << owc_depth_proxy << "\t"
    << liq_ift << "\t"
    << liq_density << "\t"
    << vap_ift << "\t"
    << vap_density << "\t"
    << free_water_level << "\t"
    << liquid_species_00 << "\t"
    << liquid_species_01 << "\t"
    << vapor_species_00 << "\t"
    << vapor_species_01 << "\t";

        return ss.str();

    }

};


#endif
