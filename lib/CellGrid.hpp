#ifndef CELL_GRID_HPP
#define CELL_GRID_HPP

#include "Coord.hpp"
#include "ACTReader.hpp"

#include "CellData.hpp"

class CellGrid
{
public:
    /**
     * Decomposed constructor.
     *
     * @param _x The x dimensionality component of the grid.
     * @param _y The y dimensionality component of the grid.
     * @param _z The z dimensionality component of the grid.
     */
    CellGrid(int _x, int _y, int _z);

    /**
     * Constructor by Coord instance.
     * 
     * @param extents The Coord instance describing the dimensionality of the grid.
     */
    CellGrid(const Coord<int> &extents);

    /**
     * CellGrid destructor.
     */
    ~CellGrid();

    /**
     * Index accessor.
     *
     * @param index The index at which to find the CellData element.
     */
    CellData & atIndex(int index);

    /**
     * Constant index accessor.
     *
     * @param index The index at which to find the CellData element.
     */

    const CellData &atIndex(int index) const;

    /**
     * Coordinate accessor.
     *
     * @param _x The x coordinate component.
     * @param _y The y coordinate component.
     * @param _z The z coordinate component.
     */
    CellData & atCoordinate(int _x, int _y, int _z);

    /**
     * Constant Coordinate accessor.
     *
     * @param _x The x coordinate component.
     * @param _y The y coordinate component.
     * @param _z The z coordinate component.
     */

    const CellData & atCoordinate(int _x, int _y, int _z) const;

    /**
     * Sets a cell to be valid at index.
     *
     * @param index The cell index to set as valid.
     */
    void setValid(int index);

    /**
     * Checks cell validity.
     *
     * @param index The cell index to check.
     */
    bool isValid(int index) const;

    bool isValid(int _x, int _y, int _z) const;

    /**
     * Gets the number of cells in the grid.
     */
    std::size_t getNumCells() const;

    const Coord<int> getDimensions() const;

    /**
     * Prints a summary of the grid.
     */
    void print() const;

    /**
     * Calculates an estimate for the storage requirements of a grid.
     *
     * @param _x The x dimensionality component of the proposed grid.
     * @param _y The y dimensionality component of the proposed grid.
     * @param _z The z dimensionality component of the proposed grid.
     */
    static std::size_t calculateStorageRequirements(int _x, int _y, int _z);

    /**
     * Calculates an estimate for the storage requirements of a grid.
     *
     * @param _numCells The number of cells the grid will hold.
     */

    static std::size_t calculateStorageRequirements(std::size_t _numCells);


private:

    std::size_t calculateIndex(int _x, int _y, int _z) const;

    ///< The number of cells held by the grid.
    std::size_t numCells;

    ///< The number of cells per z-component slice.
    std::size_t cellsPerSlice;

    ///< The dimensionality of the grid.
    Coord<int> extents;

    ///< The array holding all cell data.
    CellData *grid = nullptr;

    ///< The Coord instance describing the physical size of each cell.
    Coord<float> cellSize = Coord<float>(1.0f, 1.0f, 1.0f);

    ///< Array of bitmasks describing cell validity.
    unsigned char *valid = nullptr;
};

#endif

