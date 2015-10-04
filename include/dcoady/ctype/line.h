#ifndef INCLUDE_DCOADY_CTYPE_LINE_H
#define INCLUDE_LINEREADER_H

#include <istream>
#include <vector>

namespace dcoady {
namespace ctype  {

struct line : std::ctype<char> {
    explicit line();
    static std::ctype_base::mask const* get_table();
}; 

}}

#endif