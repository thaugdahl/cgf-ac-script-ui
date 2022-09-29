#ifndef MASSCASE_HPP
#define MASSCASE_HPP

#include "mass_audit_result.hpp"

#include <vector>
#include <memory>
#include <array>

struct MassCaseZone
{
    double mass;
    double percentage;
    double mean;
    double sd;
};

class MassCase
{
public:
    MassCase() = delete;
    MassCase(int _caseID, std::shared_ptr<std::vector<MassAuditResult>> _caseData);

    ~MassCase();

    MassCase(MassCase &&other);


    void printLayers() const;

    void printTotalMass() const;

    std::size_t getNumLayers() const;

    void printZones() const;

    int getCaseID() const;

    std::string getCSVHeader();

    std::string getCSVRow();

private:

    MassAuditResult *sortedLayers;

    double *percentageMass;

    std::size_t numLayers = 0;

    double totalMassC6;

    double sumAllC6();

    int caseID;

    void printLayer(std::size_t index) const;

    void printZoneHeader(std::size_t index) const;

    void calculateZones();

    static constexpr std::array<std::tuple<int, int, int>, 9> zones = {
        std::tuple<int,int,int>{1, 1, 58},
        std::tuple<int,int,int>{2, 62, 96},
        std::tuple<int,int,int>{3, 100, 114},
        std::tuple<int,int,int>{4, 118, 140},
        std::tuple<int,int,int>{5, 144, 158},
        std::tuple<int,int,int>{6, 162, 178},
        std::tuple<int,int,int>{7, 182, 197},
        std::tuple<int,int,int>{8, 201, 216},
        std::tuple<int,int,int>{9, 233, 253},
    };

    std::array<MassCaseZone, zones.size()> *zoneData;




};


#endif
