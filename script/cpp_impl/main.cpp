#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include <thread>
#include <memory>

enum class MODE {
    SINGLE=0,
    DIRECTORY=1
};

namespace fs = std::filesystem;

typedef std::vector<std::string> FilenameContainer;
typedef std::shared_ptr<FilenameContainer> FilenameContainerPtr;

FilenameContainerPtr getFilenames(const std::string &path)
{

    FilenameContainerPtr result = std::make_shared<std::vector<std::string>>();


    for ( const auto & entry : fs::directory_iterator(path) )
    {
        std::string filename = entry.path().filename().generic_string();
        int pos = filename.find_last_of(".");

        std::string extension = filename.substr(pos);

        if ( extension == ".grdecl" || extension == ".GRDECL" )
        {
            result->push_back(filename);
        }

    }

    return result;
}

static MODE mode;

void checks(const std::string &inputPath, const std::string &outputPath)
{

    bool inputPathExists = fs::exists(inputPath);
    std::cout << inputPath << " " << outputPath << "\n";

    if ( ! inputPathExists )
    {
        std::cerr << "Supplied input path does not exist!" << std::endl;
        exit(EXIT_FAILURE);
    }

    bool isDirectory = fs::is_directory(inputPath);

    if ( isDirectory ) {
        mode = MODE::DIRECTORY;
        std::cout << "The supplied input path is a directory. Switching to batch processing mode" << "\n";
    }

    // Create the output directory if it does not exist
    bool outputPathExists = fs::exists(outputPath);
    bool outIsDirectory = fs::is_directory(outputPath);

    if ( ! outputPathExists && mode == MODE::DIRECTORY )
    {
        std::cout << "The output directory does not exist. It is being created now\n";
        fs::create_directory(outputPath);
    }

    if ( outputPathExists && outIsDirectory && ! isDirectory )
    {
        std::cerr << "Output path is a directory, while the input path is a single file." << std::endl;
        exit(EXIT_FAILURE);
    }

    if ( outputPathExists && mode == MODE::SINGLE )
    {
        std::cout << "The output path already exists. Overwrite it? (Y/n)";
        char response;
        std::cin >> response;
        if ( response != 'y' && response != 'Y' )
        {
            std::cout << "Aborting...\n";
            exit(EXIT_FAILURE);
        }
    }

}



int main(int argc, char *argv[])
{
    if ( argc < 3 ) {
        std::cerr << "Not enough arguments" << std::endl;
        exit(EXIT_FAILURE);
    }


    std::string inputPath = argv[1];
    std::string outputPath = argv[2];

    checks(inputPath, outputPath);


    FilenameContainerPtr inputFiles;
    std::string cwd = fs::current_path();
    std::cout << cwd << std::endl;

   if ( mode == MODE::SINGLE ) {
       inputFiles = std::make_shared<FilenameContainer>();
       inputFiles->push_back(inputPath);
   } else {
        inputFiles = getFilenames(inputPath);
   }

   for ( auto &s : *inputFiles )
   {
       std::cout << inputPath << "/" << s << "\n";
   }



    return 0;
}
