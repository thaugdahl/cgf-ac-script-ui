#ifndef ACT_CSVEXPORT_HPP
#define ACT_CSVEXPORT_HPP

#include <array>
#include <string_view>

constexpr std::array<std::string_view, 20> PathwayCellData_Fields =
{
    "index",
    "sub_index",
    "porosity",
    "invasion_sequence",
    "invade_temp",
    "invade_press",
    "paleo_filling_fraction",
    "bulk_volume",
    "paleo_z",
    "paleo_crit",
    "pristine_crit",
    "last_expulsion_index",
    "last_expulsion_sub_index",
    "species_00",
    "species_01",
    "scaled_socr",
    "socr",
    "swc",
    "pthx",
    "pthz"
};

class ACT_CSVExport
{
    
};

#endif

