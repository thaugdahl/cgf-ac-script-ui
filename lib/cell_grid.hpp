#ifndef CELL_GRID_HPP
#define CELL_GRID_HPP

#include "coord.hpp"
#include "act_reader.hpp"

#include "CellData.hpp"

class CellGrid
{
public:
    CellGrid(int _x, int _y, int _z);

    CellGrid(const Coord<int> &extents);

    ~CellGrid();

    CellData & atIndex(int index);
    const CellData &atIndex(int index) const;

    CellData & atCoordinate(int _x, int _y, int _z);
    const CellData & atCoordinate(int _x, int _y, int _z) const;

    void print() const;


private:

    std::size_t numCells;
    std::size_t cellsPerSlice;
    Coord<int> extents;
    CellData *grid = nullptr;
    bool *valid = nullptr;


};

#endif

