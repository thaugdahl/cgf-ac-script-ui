#include "CellGrid.hpp"
#include <iostream>

CellGrid::CellGrid(int _x, int _y, int _z)
{
    cellsPerSlice = _x * _y;
    numCells = cellsPerSlice * _z;
    extents = Coord<int>(_x, _y, _z);

    grid = new CellData[numCells];
    valid = new unsigned char[numCells / 8 + 1];
}

CellGrid::CellGrid(const Coord<int> &extents)
    : CellGrid( extents.get<0>(), 
            extents.get<1>(), 
            extents.get<2>())
{ }


CellGrid::~CellGrid()
{
    if ( nullptr != grid )
        delete[] grid;

    if ( nullptr != valid )
        delete[] valid;
}

CellData &CellGrid::atIndex(int index)
{
    if ( index >= numCells )
        throw std::runtime_error("CellGrid: Index out of bounds");

    return grid[index];
}

const CellData &CellGrid::atIndex(int index) const
{
    return const_cast<const CellData &>(
                const_cast<CellGrid *>(this)
                    ->atIndex(index));
}

CellData &CellGrid::atCoordinate(int _x, int _y, int _z)
{
    if(_x >= extents.get<0>() ||
            _y >= extents.get<1>() ||
            _z >= extents.get<2>() )
    {
        throw std::runtime_error("CellGrid: Passed coordinates do not "
                "match the grid dimensions");
    }


    std::size_t index = calculateIndex(_x, _y, _z);

    return atIndex(index);
}

// Deduplicated with `const_cast`?
// Ensure no UB. See: https://en.cppreference.com/w/cpp/language/const_cast
const CellData &CellGrid::atCoordinate(int _x, int _y, int _z) const
{
    return const_cast<const CellData &>(
            const_cast<CellGrid *>(this)
                ->atCoordinate(_x,_y,_z));
}

void CellGrid::setValid(int index)
{
    int bitmaskIndex = index / 8;
    int bitOffset = index % 8;

    unsigned char ORMask = 0b1 << bitOffset;

    valid[bitmaskIndex] |= ORMask; 
}

bool CellGrid::isValid(int index) const
{
    int bitmaskIndex = index / 8;
    int bitOffset = index % 8;

    unsigned char ANDMask = 0b1 << bitOffset;

    return (valid[bitmaskIndex] & ANDMask) > 0;
}

bool CellGrid::isValid(int _x, int _y, int _z) const
{
    std::size_t index = calculateIndex(_x, _y, _z);
    return isValid(index);
}


const Coord<int> CellGrid::getDimensions() const
{
    return extents;
}



std::size_t CellGrid::getNumCells() const
{
    return numCells;
}

std::size_t CellGrid::calculateStorageRequirements(std::size_t _numCells)
{
    return (_numCells * sizeof(CellData) + (_numCells / 8 + 1) * sizeof(unsigned char));
}

std::size_t CellGrid::calculateStorageRequirements(int _x, int _y, int _z)
{
    std::size_t numCells = _x * _y * _z;
    return calculateStorageRequirements(numCells);
}

std::size_t CellGrid::calculateIndex(int _x, int _y, int _z) const
{
   return _z * cellsPerSlice + _y * extents.get<0>() + _x;
}

void CellGrid::print() const
{
    std::cout << "===Cell Grid===\n";
    std::cout << "Extents: " << extents << "\n";
    std::cout << "Number of cells: " << numCells << "\n";
    std::cout << "Cells per slice: " << cellsPerSlice << "\n";
    std::cout << "Storage required: " << (calculateStorageRequirements(numCells)) / (1024 * 1024) << "MB\n";
}
