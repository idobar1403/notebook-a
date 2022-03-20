#ifndef NOTEBOOK_CPP
#define NOTEBOOK_CPP

#include <map>
#include <vector>
#include <string>
#include "Direction.hpp"
#include "Page.hpp"
using ariel::Direction;
namespace ariel
{
    class Notebook
    {
    private:
        static char _empty_char;
        std::map<unsigned int,Page> notebook;
    public:
        void write(unsigned int page_num, unsigned int row_num, unsigned int col_num, Direction direction, std::string s);
        std::string read(unsigned int page_num, unsigned int row_num, unsigned int col_num, Direction direction, unsigned int length);
        void erase(unsigned int page_num, unsigned int row_num, unsigned int col_num, Direction direction, unsigned int length);
        void show(unsigned int page_num);
    };
}
#endif