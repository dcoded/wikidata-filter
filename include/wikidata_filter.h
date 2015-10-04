#ifndef INCLUDE_WIKIDATAFILTER_H
#define INCLUDE_WIKIDATAFILTER_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace
{
    using boost::property_tree::ptree;
    using boost::property_tree::read_json;
}

class wikidata_filter {
public:
    explicit wikidata_filter(const char* filename)
    : savefile_(filename)
    , saved_(0)
    {

    }

    ~wikidata_filter()
    {
        savefile_.close();
    }

    void add(std::string id)
    {
        id_list_.push_back(id);
        std::cout << "adding [" << id_list_.size() << "] " << id << '\n';
    }

    void sort()
    {
        std::sort(id_list_.begin(), id_list_.end());
    }

    void filter(std::string line)
    {
        ptree jsontree;
        std::istringstream ijsonstream (line);
        read_json (ijsonstream, jsontree);

        // get line id
        std::string entity_id = jsontree.get<std::string>("id");


        if(std::binary_search(id_list_.begin(), id_list_.end(), entity_id))
        {
            savefile_ << line << std::endl;
            std::cout << "+" << entity_id << "; " << saved_++ << " of " << id_list_.size() << "\n";
        }
    }
private:
    std::ofstream savefile_;
    std::deque<std::string> id_list_;
    std::uint32_t saved_;
};

#endif