#include "MassCase.hpp"
#include <math.h>

#include <sstream>

MassCase::MassCase(int _caseID, std::shared_ptr<std::vector<MassAuditResult>> _caseData)
{
    caseID = _caseID;

    this->numLayers = _caseData->size();

    sortedLayers = new MassAuditResult[numLayers];
    percentageMass = new double[numLayers];
    zoneData = new std::array<MassCaseZone, zones.size()>{};



    // Insert directly
    for ( auto & x : *_caseData )
    {
        sortedLayers[x.layer - 1] = x;
    }


    totalMassC6 = sumAllC6();

    for ( int i = 0; i < numLayers; i++ )
    {
        percentageMass[i] = sortedLayers[i].c6plus / totalMassC6;
    }

    calculateZones();


}

void MassCase::calculateZones()
{

    for ( std::size_t i = 0; i < zones.size(); i++)
    {
        auto &descriptor = zones[i];

        int zoneNumber = std::get<0>(descriptor);
        int zoneStart = std::get<1>(descriptor);
        int zoneEnd = std::get<2>(descriptor);

        double massSum = 0.0;
        double percentageSum = 0.0;

        std::size_t localNumLayers = zoneEnd - zoneStart;

        // TODO: Verify layer indexing
        for ( std::size_t layer = zoneStart - 1; layer < zoneEnd; layer++ )
        {
            massSum += sortedLayers[layer].c6plus;
            percentageSum += percentageMass[layer];
        }


        double mean = massSum / localNumLayers;

        double variance = 0.0;

        for ( std::size_t layer = zoneStart - 1; layer < zoneEnd; layer++ )
        {
            double factor = sortedLayers[layer].c6plus - mean;
            variance += factor*factor;
        }

        variance /= localNumLayers - 1;

        (*zoneData)[i].mass = massSum;
        (*zoneData)[i].mean = mean;
        (*zoneData)[i].percentage = percentageSum;
        (*zoneData)[i].sd = std::sqrt(variance);
    }

}

MassCase::MassCase(MassCase &&other)
{
    sortedLayers = other.sortedLayers;
    other.sortedLayers = nullptr;

    percentageMass = other.percentageMass;
    other.percentageMass = nullptr;

    zoneData = other.zoneData;
    other.zoneData = nullptr;

    numLayers = other.numLayers;
    other.numLayers = 0;

    totalMassC6 = other.totalMassC6;
    other.totalMassC6 = 0.0;

    caseID = other.caseID;
    other.caseID = 0;
}

MassCase::~MassCase()
{
    if ( sortedLayers != nullptr)
        delete[] sortedLayers;

    if ( percentageMass != nullptr )
        delete[] percentageMass;

    if (zoneData != nullptr )
        delete zoneData;
}

double MassCase::sumAllC6()
{

    double total = 0.0;

    for ( std::size_t i = 0; i < numLayers; i++)
    {
        total += sortedLayers[i].c6plus;
    }

    return total;
}


void MassCase::printLayer(std::size_t index) const
{
    double massMT = sortedLayers[index].c6plus / 1e9;
    double percent = percentageMass[index] * 100.0;

    std::cout << "Layer " << index << ": " << massMT << " Mt (" << percent << "%)" << std::endl;
}


void MassCase::printLayers() const
{
    std::cout << "NUM LAYERS: " << numLayers << std::endl;
    for ( std::size_t i = 0; i < numLayers; i++)
    {
        printLayer(i);
    }
}


void MassCase::printTotalMass() const
{
    std::cout << "Total Mass C6+: " << totalMassC6 << std::endl;
}

std::size_t MassCase::getNumLayers() const
{
    return numLayers;
}


void MassCase::printZones() const
{
    for ( std::size_t i = 0; i < zones.size(); i++ )
    {
        printZoneHeader(i);
        // std::cout << "=== Zone L" << std::get<0>(zones[i]) << " ===\n";
        std::cout << "Aggregate Heavy Mass: " << (*zoneData)[i].mass / 1e9 << " Mt\n";
        std::cout << "Percentage of Total Mass: " << (*zoneData)[i].percentage * 100.0 << "%\n";
        std::cout << "Mean Heavy Mass in Constituent Layers : " << (*zoneData)[i].mean / 1e9 << " Mt\n";
        std::cout << "Standard Deviation of Mass: " << (*zoneData)[i].sd << " kg\n";
    }

}

int MassCase::getCaseID() const
{
    return caseID;
}


void MassCase::printZoneHeader(std::size_t index) const
{
    std::cout << "=== Zone L" << std::get<0>(zones[index]) <<
        "( " << std::get<1>(zones[index]) <<
        " - " <<
        std::get<2>(zones[index]) << " ) ===\n";
}

std::string MassCase::getCSVHeader()
{
    std::vector<std::string> items;

    // items.push_back("Case");

    for ( auto &descriptor : zones )
    {
        int layerNum = std::get<0>(descriptor);
        std::string layerString = "L" + std::to_string(layerNum);
        items.push_back(layerString + " Mass C6+ (Mt)");
        items.push_back(layerString + " Percentage of Mass (%)");
        items.push_back(layerString + " Mean Layer Mass (Mt)");
        items.push_back(layerString + " Layer Mass SD (kg)");
    }


    std::ostringstream oss{};

    for ( auto &itemHeader : items )
    {
        oss << "\t" << itemHeader;
    }

    return oss.str();



}

std::string MassCase::getCSVRow()
{

    std::ostringstream oss{};

    oss.precision(12);

    oss << caseID;

    for ( std::size_t i = 0; i < zones.size(); i++)
    {
        oss << "\t" << (*zoneData)[i].mass / 1e9
            << "\t" << (*zoneData)[i].percentage * 100.0
            << "\t" << (*zoneData)[i].mean / 1e9
            << "\t" << (*zoneData)[i].sd;
    }

    return oss.str();


}
