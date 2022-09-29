#ifndef MASS_AUDIT_RESULT
#define MASS_AUDIT_RESULT

#include <cstdint>
#include <string>
#include <iomanip>

#include <iostream>

struct MassAuditResult
{

    std::uint32_t layer;
    std::string layerName;
    double bulkRockVolume;
    float averagePorosity;
    float poreVolume;
    float rockVolume;
    float expelledC6plus;
    float c6plus;
    float pathwayMass;
    float accumulationMass;
    float accumulationBulkRockVolume;
    float pathwayBulkRockVolume;
    float accumulationAveragePorosity;
    float pathwayAveragePorosity;
    float accumulationPoreVolume;
    float pathwayPoreVolume;
    float accumulationRockVolume;
    float pathwayRockVolume;

    void print()
    {
    std::cout << "layer: " << layer << std::endl;
    std::cout << "layerName: " << layerName << std::endl;
    std::cout << "bulkRockVolume: " << bulkRockVolume << std::endl;
    std::cout << "averagePorosity: " << averagePorosity << std::endl;
    std::cout << "poreVolume: " << poreVolume << std::endl;
    std::cout << "rockVolume: " << rockVolume << std::endl;
    std::cout << "expelledC6plus: " << expelledC6plus << std::endl;
    std::cout << "c6plus: " << c6plus << std::endl;
    std::cout << "pathwayMass: " << pathwayMass << std::endl;
    std::cout << "accumulationMass: " << accumulationMass << std::endl;
    std::cout << "accumulationBulkRockVolume: " << accumulationBulkRockVolume << std::endl;
    std::cout << "pathwayBulkRockVolume: " << pathwayBulkRockVolume << std::endl;
    std::cout << "accumulationAveragePorosity: " << accumulationAveragePorosity << std::endl;
    std::cout << "pathwayAveragePorosity: " << pathwayAveragePorosity << std::endl;
    std::cout << "accumulationPoreVolume: " << accumulationPoreVolume << std::endl;
    std::cout << "pathwayPoreVolume: " << pathwayPoreVolume << std::endl;
    std::cout << "accumulationRockVolume: " << accumulationRockVolume << std::endl;
    std::cout << "pathwayRockVolume: " << pathwayRockVolume << std::endl;


    }
};

#endif
