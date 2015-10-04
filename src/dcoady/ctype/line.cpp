#include <dcoady/ctype/line.h>

namespace dcoady {
namespace ctype  {

line::line()
: std::ctype<char>(get_table())
{
}

std::ctype_base::mask const* line::get_table()
{
    static std::vector<std::ctype_base::mask> 
        rc(table_size, std::ctype_base::mask());

    rc['\n'] = std::ctype_base::space;
    return &rc[0];
}

}}