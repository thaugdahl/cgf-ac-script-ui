#include "cell_grid.hpp"
#include <iostream>

CellGrid::CellGrid(int _x, int _y, int _z)
{
    cellsPerSlice = _x * _y;
    numCells = cellsPerSlice * _z;
    extents = Coord<int>(_x, _y, _z);

    grid = new CellData[numCells];
    valid = new bool[numCells];
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


    std::size_t index = _z * cellsPerSlice + _y * extents.get<0>() + _x;

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

void CellGrid::print() const
{
    std::cout << "===Cell Grid===\n";
    std::cout << "Extents: " << extents << "\n";
    std::cout << "Number of cells: " << numCells << "\n";
    std::cout << "Cells per slice: " << cellsPerSlice << "\n";
}
