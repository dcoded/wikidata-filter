#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/gzip.hpp>

using boost::iostreams::input;
using boost::iostreams::filtering_stream;

void gunzip(const char*, filtering_stream<input>&);
bool target(const std::string&, const std::vector<std::string>&);

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        std::cout << "Usage: ./" << argv[0] << "<filename> <category ID>\n";
        exit(0);
    }

    const char* filename = argv[1];
    const char* category = argv[2];

    filtering_stream<input> decompressor;
    gunzip(filename, decompressor);

    std::vector<std::string> categories = { category };

    int i = 0;
    for(std::string line; getline(decompressor, line); i++)
    {
        if(target(line, categories))
        {
            std::cout << line << "\n";
        }


        std::cout << '[' << i << ']' << ' ' << line << std::endl;
    }
}

void gunzip(const char* filename, filtering_stream<input>& decompressor)
{
    std::ifstream file;
    file.exceptions(std::ios::failbit | std::ios::badbit);
    file.open(filename, std::ios_base::in | std::ios_base::binary);

    decompressor.push(boost::iostreams::gzip_decompressor());
    decompressor.push(file);
}

bool target(const std::string& line, const std::vector<std::string>& categories)
{
    for(std::string category : categories)
    {
        if(line.find(category) != std::string::npos)
        {
            return true;
        }
    }
    return false;
}