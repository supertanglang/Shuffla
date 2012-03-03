#ifndef QUERYDISPATCHER_H
#define QUERYDISPATCHER_H

#include <string>


#include "../engine/search_engine.hpp"
#include "../engine/query/query_create.hpp"


class QueryDispatcher
{
public:
    QueryDispatcher(SearchEngine* search_engine);
    virtual ~QueryDispatcher();
    std::string process_query(const std::string& request);
protected:
private:
    QueryCreate query_parser;
    SearchEngine* search_engine;
};

#endif // QUERYDISPATCHER_H
