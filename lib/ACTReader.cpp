#include "ACTReader.hpp"
#include <iomanip>


ACT_Reader::ACT_Reader(const std::string &_filename)
    : result{std::make_shared<ACT_File>()}
{
    filename = _filename;
    fh = std::ifstream(filename);

    if ( ! fh.is_open() )
    {
        throw std::runtime_error("Failed to open file " + filename);
    }

#ifdef VERBOSE
    std::cout << "Opened file " << filename << "\n";
#endif
}

ACT_Reader::~ACT_Reader()
{
    if ( fh.is_open() )
    {
        fh.close();
    }
}


ACT_File::ACT_File()
{
    pathwayCellData = std::make_shared<std::vector<PathwayCellData>>();
    cellData = std::make_shared<std::vector<CellData>>();
    bodyData = std::make_shared<std::vector<BodyData>>();
}
void ACT_File::print()
{
    std::cout << std::setprecision(5);
    std::cout << std::fixed;
    std::cout << "========== ACT FILE SUMMARY ==========" << "\n";
    std::cout << "Description: " << description << "\n";
    std::cout << "Scenario: " << scenario << "\n";
    std::cout << "Version: " << version << "\n";
    std::cout << "Time: " << time << "\n";
    std::cout << "PVT File: " << pvt_file << "\n";
    std::cout << "Extents: " << 
        extents.get<0>() << ", " <<
        extents.get<1>() << ", " <<
        extents.get<2>() << ", " << "\n";

    std::cout << "Origin: " << 
        origin.get<0>() << ", " <<
        origin.get<1>() << ", " <<
        origin.get<2>() << ", " << "\n";

    std::cout << "Cell Size: " << 
        cellSize.get<0>() << ", " <<
        cellSize.get<1>() << ", " <<
        cellSize.get<2>() << ", " << "\n";



    std::cout << "Pathway Cell Data Length: " << pathwaycelldata_length << "\n";
    std::cout << "Cell Data Length: " << celldata_length << "\n";
    std::cout << "Body Data Length: " << bodydata_length << "\n";
}

void ACT_Reader::getNewLine()
{
    std::getline(fh, current_line);
    ss = std::stringstream(current_line);
}


void ACT_Reader::skipLine()
{
    std::getline(fh, current_line);
}

void ACT_Reader::skipLines(int n)
{
    for ( decltype(n) i = 0; i < n; i++)
        std::getline(fh, current_line);
}


template <typename T>
void ACT_Reader::readCoord(Coord<T> &coord)
{
    std::string label;
    T x, y, z; 

    ss >> label;
    ss >> x >> y >> z;

    coord = Coord<T>(x,y,z);
}

template <typename T>
void ACT_Reader::readField(T &field)
{
    std::string label;
    T value;

    ss >> label;
    ss >> value;

    field = value;
}

std::shared_ptr<ACT_File> ACT_Reader::read()
{

    if ( ! fh.is_open() )
    {
        fh.open(filename);
    }

    if ( ! fh.is_open() ) {
        throw std::runtime_error("Failed to open " + filename);
    }

    getNewLine();
    // Process header
    std::string label;

    // Description
    getNewLine();
    readField(result->description);

    // Version
    getNewLine();
    readField(result->version);

    // Mesh
    getNewLine();

    // Scenario
    getNewLine();
    readField(result->scenario);

    // Extents
    getNewLine();
    readCoord(result->extents);

    // Origin
    getNewLine();
    readCoord(result->origin);

    
    // Cell Size
    getNewLine();
    readCoord(result->cellSize);

    // Skip Rotation
    getNewLine();

    // Time
    getNewLine();
    readField(result->time);

    // PVT file
    getNewLine();
    readField(result->pvt_file);

    // Skip stocktank_bp, stocktank_dp, stocktank_rhol,
    // ---- stocktank_rhov, pathwaycelldata_fields, pathwaycelldata_fieldtypes
    skipLines(6);
    getNewLine();
    readField(result->pathwaycelldata_length);

    // Skip Field Names and Fieldtypes
    skipLines(2);
    getNewLine();
    readField(result->celldata_length);

    // Skip Field Names and Fieldtypes
    skipLines(2);
    getNewLine();
    readField(result->bodydata_length);

    // Read Pathway Cell Data Binary Table
    getNewLine();
    readBinaryTable(*result->pathwayCellData, result->pathwaycelldata_length);

    while ( ! isEndFooter() )
        skipLines(1);

    // Read Cell Data Binary Table
    getNewLine();
    readBinaryTable(*result->cellData, result->celldata_length);

    while ( ! isEndFooter() )
        skipLines(1);

    // Read Body Data Binary Table
    getNewLine();
    readBinaryTable(*result->bodyData, result->bodydata_length);

    // All information of interest is now read

    fh.close();

    // Print the summary
    result->print();



    // Return the shared pointer to the ACT_File instance
    return result;

}

template <typename T>
void ACT_Reader::readBinaryTable(std::vector<T> &vec, std::size_t num_elements)
{
    constexpr std::size_t sz = sizeof(T);

    // Are we at a binary table header?
    if ( ! isBinaryTableHeader() )
    {
        throw std::runtime_error("Could not find binary table header");
    }

    std::size_t bytes_to_read = sz * num_elements;

    // Progress past the Binary Table Header into the binary data
    getNewLine();

    // Read the entire binary table into a char buffer
    char *buffer = new char[bytes_to_read];
    fh.read(buffer, bytes_to_read);
    char *current_elem_ptr = buffer + 0; 

    // Reinterpet raw data as instances of T
    for ( decltype(num_elements) i = 0; i < num_elements; i++ )
    {
        T data = *reinterpret_cast<T *>(current_elem_ptr);

        vec.emplace_back(data);

        // Advance buffer pointer by an entire T
        current_elem_ptr += sizeof(T);
    }
    
}

std::shared_ptr<ACT_File> ACT_Reader::readFile(const std::string &_filename)
{
    ACT_Reader reader{_filename};

    return reader.read();
}

bool ACT_Reader::isBinaryTableHeader()
{
    if ( current_line.find("binarytable") != std::string::npos )
    {
        return true;
    }
    return false;
}

bool ACT_Reader::isEndFooter()
{
    if ( current_line.find("[END]") != std::string::npos )
    {
        return true;
    }
    return false;
}
