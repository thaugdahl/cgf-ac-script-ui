#ifndef CSV_SERIALIZABLE_HPP
#define CSV_SERIALIZABLE_HPP

#include <string>

class CSV_Serializable
{
    CSV_Serializable() {}
    virtual ~CSV_Serializable() {}

    virtual std::string getCSVHeader() = 0;
    virtual std::string getCSVRow() = 0;


};

#endif

