#include "FileProcessor.hpp"

#include <fstream>
#include <wx/wx.h>

FileProcessor::FileProcessor(
    const std::string &input, const std::string &output
) : input{input}, output{output}
{ }

void FileProcessor::process()
{
    std::ifstream file{input};
    std::ofstream ofile;

    if ( ! file.is_open())
    {
        throw std::runtime_error("Failed to open file " + input + " for reading");  
    }

    ofile.open(output);
    if ( !ofile.is_open() )
    {
        throw std::runtime_error("Failed to open file " + output + " for writing");
    }

    std::string prevLine1;

    while ( file.good()  )
    {
        std::getline(file, prevLine1);
        lines_processed++;

        ofile << prevLine1 << "\n";
    }

    file.close();
    ofile.close();
}


