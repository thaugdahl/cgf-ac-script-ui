#ifndef FILE_PROCESSOR_HPP
#define FILE_PROCESSOR_HPP

#include <string>

class FileProcessor
{
public:

    FileProcessor(const std::string &input, const std::string &output);

    void process();

    int lines_processed = 0; 

private:
    std::string input;
    std::string output;
};

#endif
