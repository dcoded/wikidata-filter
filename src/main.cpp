#include <fstream>
#include <iostream>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/gzip.hpp>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "missing filename argument\n";
        exit(0);
    }

    const char* filename = argv[1];

	std::ifstream file;
    file.exceptions(std::ios::failbit | std::ios::badbit);
    file.open(filename, std::ios_base::in | std::ios_base::binary);

    boost::iostreams::filtering_stream<boost::iostreams::input> decompressor;
    decompressor.push(boost::iostreams::gzip_decompressor());
    decompressor.push(file);

    int i = 0;
    for(std::string line; getline(decompressor, line); i++) {
        std::cout << '[' << i << ']' << ' ' << line << std::endl;
    }
}

