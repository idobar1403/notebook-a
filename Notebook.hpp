#ifndef NOTEBOOK_CPP
#define NOTEBOOK_CPP

#include <unordered_map>
#include <vector>
#include <string>
#include "Direction.hpp"
struct Page
{
    std::vector<std::unordered_map<unsigned int, char>> note;
    unsigned int page_number;
    unsigned int min_row;
    unsigned int max_row;
    unsigned int min_col;
    unsigned int max_col;
    Page(unsigned int page_num): note(std::vector<std::unordered_map<unsigned int, char>>(100))
    {
        page_number = page_num;
        min_row = 0;
        max_row = 0;
        min_col = 100;
        max_col = 0;
    }
};

using ariel::Direction;
namespace ariel
{
    class Notebook
    {
    private:
        char empty_char = '_';
        unsigned int upper_bound = 100;
        unsigned int lower_bound = 0;
        std::unordered_map<unsigned int,Page> notebook;
        void putCharAt(unsigned int page_num, unsigned int row, unsigned int col, char c);
        char getChar(unsigned int page_num, unsigned int row, unsigned int col);
        void setRowsCols(unsigned int page_num, unsigned int min_row, unsigned int max_row, unsigned int min_col, unsigned int max_col);
    public:
        void write(unsigned int page_num, unsigned int row_num, unsigned int col_num, Direction direction, std::string s);
        std::string read(unsigned int page_num, unsigned int row_num, unsigned int col_num, Direction direction, unsigned int length);
        void erase(unsigned int page_num, unsigned int row_num, unsigned int col_num, Direction direction, unsigned int length);
        void show(unsigned int page_num);
    };
}
#endif