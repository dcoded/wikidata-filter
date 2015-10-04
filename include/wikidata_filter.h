#ifndef INCLUDE_WIKIDATAFILTER_H
#define INCLUDE_WIKIDATAFILTER_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/exception/all.hpp>

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
        std::string entity_id;

        std::cout << "** wikidata_filter::filter/read_json() **\n";
        try
        {
            std::istringstream ijsonstream (line);
            read_json (ijsonstream, jsontree);
        }
        catch(boost::exception& ex)
        {
            std::cout << "[error] property_tree::read_json()\n";
            return;
        }

        std::cout << "** wikidata_filter::filter/get(id) **\n";
        try
        {
            // get line id
            entity_id = jsontree.get<std::string>("id");
        }
        catch(boost::exception& ex)
        {
            std::cout << "[error] property_tree::get(id)\n";
            return;
        }

        std::cout << "** wikidata_filter::filter/binary_search() **\n";
        if(std::binary_search(id_list_.begin(), id_list_.end(), entity_id))
        {
            std::cout << "** wikidata_filter::filter/savefile() **\n";
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