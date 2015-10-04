#include <dcoady/gzip/istream.h>

namespace dcoady {
namespace gzip   {

istream::istream(const char* filename)
{
    file_.exceptions(std::ios::failbit | std::ios::badbit);
    file_.open(filename, std::ios_base::in | std::ios_base::binary);

    push(boost::iostreams::gzip_decompressor());
    push(file_);
}

istream::~istream()
{
}

}}