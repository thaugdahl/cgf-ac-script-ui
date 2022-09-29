#include "MassAuditReader.hpp"

#include <iostream>

MassAuditReader::MassAuditReader(const std::string &_filename)
{

    filename = _filename;

    fh = std::ifstream(filename);

    if ( ! fh.is_open() )
    {
        throw std::runtime_error("Failed to open " + filename);
    }

    std::getline(fh, current_line);
    // std::cout << current_line << std::endl;

    skipRow();

    MassAuditResult res;

    while ( ! fh.eof() )
    {
        res = readRow();

        rows->push_back(res);

        nextRow();
    }

}

std::shared_ptr<std::vector<MassAuditResult>> MassAuditReader::getRows() const
{
    return rows;
}

void MassAuditReader::skipRow()
{
    std::getline(fh, current_line);
}

void MassAuditReader::nextRow()
{
    std::getline(fh, current_line);
    ss = std::stringstream{current_line};
}

template <typename T>
void MassAuditReader::readField(T &field)
{
    ss >> field;
}

MassAuditResult MassAuditReader::readRow()
{
    MassAuditResult currentRow{};

    // readField(currentRow.layer);
    // readField(currentRow.layerName);

    std::vector<std::string> splitString{};

    auto s = current_line.find("\t");

    std::string current_substring = current_line;

    while ( s != std::string::npos )
    {
        std::string first = current_substring.substr(0, s);
        std::string last = current_substring.substr(s+1);

        if (first.length() == 0 ) {
            first = "0";
        }

        splitString.push_back(first);

        current_substring = last;

        s = current_substring.find("\t");

    }

    if ( current_substring.length() == 0 )
    {
        current_substring = "0";
    }

    splitString.push_back(current_substring);

    MassAuditResult result;


    // for ( auto &x : splitString )
    // {
    //     std::cout << x << std::endl;
    // }

    result.layer                       = std::stoi(splitString[0]);
    result.layerName                   = splitString[1];
    result.bulkRockVolume              = std::stod(splitString[2]);
    result.averagePorosity             = std::stof(splitString[3]);
    result.poreVolume                  = std::stof(splitString[4]);
    result.rockVolume                  = std::stof(splitString[5]);
    result.expelledC6plus              = std::stof(splitString[6]);
    result.c6plus                      = std::stof(splitString[7]);
    result.pathwayMass                 = std::stof(splitString[8]);
    result.accumulationMass            = std::stof(splitString[9]);
    result.accumulationBulkRockVolume  = std::stof(splitString[10]);
    result.pathwayBulkRockVolume       = std::stof(splitString[11]);
    result.accumulationAveragePorosity = std::stof(splitString[12]);
    result.pathwayAveragePorosity      = std::stof(splitString[13]);
    result.accumulationPoreVolume      = std::stof(splitString[14]);
    result.pathwayPoreVolume           = std::stof(splitString[15]);
    result.accumulationRockVolume      = std::stof(splitString[16]);
    result.pathwayRockVolume           = std::stof(splitString[17]);

    return result;



}


MassAuditReader::~MassAuditReader()
{
    if ( fh.is_open() )
    {
        fh.close();
    }
}
