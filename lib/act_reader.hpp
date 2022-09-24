#ifndef ACT_READER
#define ACT_READER

#include <cstdint>
#include <vector>
#include <memory>
#include <string>
#include "coord.hpp"

#include <fstream>
#include <sstream>
#include <iostream>
#include <string_view>

#include "PathwayCellData.hpp"
#include "CellData.hpp"
#include "BodyData.hpp"

struct ACT_File
{

    ACT_File();
    ~ACT_File() {}

    void print();

    std::size_t pathwaycelldata_length;
    std::size_t celldata_length;
    std::size_t bodydata_length;

    ///< The .din file this .act file was generated from
    std::string scenario;
    std::string description;
    int version;
    std::string pvt_file;
    float time;

    Coord<int> extents;
    Coord<float> origin;
    Coord<float> cellSize;


    std::shared_ptr<std::vector<PathwayCellData>> pathwayCellData;
    std::shared_ptr<std::vector<CellData>> cellData;
    std::shared_ptr<std::vector<BodyData>> bodyData;
};

class ACT_Reader
{
public:
    ACT_Reader() = delete;
    ACT_Reader(const std::string &_filename);
    ~ACT_Reader();

    std::shared_ptr<ACT_File> read();

    static std::shared_ptr<ACT_File> readFile(const std::string &_filename);

    template <typename T>
    void readCoord(Coord<T> &coord);


    template <typename T>
    void readField(T &field);

    template <typename T>
    void readBinaryTable(std::vector<T> &vec, std::size_t num_elements);

private:
    std::string filename;

    std::ifstream fh;
    std::stringstream ss;
    std::string current_line;

    std::shared_ptr<ACT_File> result;

    void getNewLine();
    void skipLine();
    void skipLines(int n);

    bool isBinaryTableHeader();
    bool isEndFooter();

    
    


};



#endif

