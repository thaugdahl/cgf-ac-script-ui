#ifndef MASS_AUDIT_READER
#define MASS_AUDIT_READER

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include "MassAuditResult.hpp"


class MassAuditReader
{
public:
    MassAuditReader() = delete;

    /**
     * MassAuditReader constructor.
     * Expects a .tsv file
     *
     * @param filename A string, should be a tsv filename.
     */
    MassAuditReader(const std::string &_filename);

    ~MassAuditReader();

    std::shared_ptr<std::vector<MassAuditResult>> getRows() const;




protected:

private:

    ///< The file handle used for reading the Mass Audit table. Must be freed
    std::ifstream fh;
    std::string filename;
    std::string current_line;
    std::stringstream ss;

    std::shared_ptr<std::vector<MassAuditResult>> rows = std::make_shared<std::vector<MassAuditResult>>();

    MassAuditResult readRow();
    void skipRow();
    void nextRow();

    template <typename T>
    void readField(T &field);

};

#endif
