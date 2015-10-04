#include <dcoady/gzip/istream.h>
#include <dcoady/ctype/line.h>
#include <wikidata_filter.h>

#include <algorithm>
#include <iterator>
#include <iostream>
#include <functional>



 

void line_fn(std::string line)
{
    std::cout << line << "\n##########\n###########\n###########\n###########\n";
}

int main(int argc, char* argv[])
{
    const char* filename = argv[1];
    const char* savefile = argv[2];
    const char* idlist   = argv[3];

    wikidata_filter wdf(savefile);

    std::ifstream ids(idlist);
    std::for_each(std::istream_iterator<std::string>(ids),
              std::istream_iterator<std::string>(),
              [&wdf](std::string id) { wdf.add(id); });

    wdf.sort();

    dcoady::gzip::istream gunzip(filename);
    gunzip.imbue(std::locale(std::locale(), new dcoady::ctype::line()));

    std::cout << "** std::for_each begin **\n";
    std::for_each(std::istream_iterator<std::string>(gunzip),
                  std::istream_iterator<std::string>(),
                  [&wdf](std::string line){ wdf.filter(line); });
    std::cout << "** std::for_each end **\n";

    return 0;
}


void filter()
{

}

