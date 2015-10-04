#ifndef INCLUDE_DCOADY_GZIP_ISTREAM_H
#define INCLUDE_DCOADY_GZIP_ISTREAM_H

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include <algorithm>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/gzip.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace dcoady {
namespace gzip   {


namespace
{
    using boost::iostreams::input;
    using boost::iostreams::filtering_stream;
}

class istream : public filtering_stream<input> {
public:
    explicit istream(const char* filename);
    ~istream();

private:
    std::ifstream file_;
};

}}

#endif