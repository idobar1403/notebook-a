#include <map>
#include <vector>
#include <string>
#include "Direction.hpp"

class Page
{
private:
    std::vector<std::map<unsigned int, char>> note;
    static char empty_char;
    unsigned int _page_number;
    unsigned int _min_row;
    unsigned int _max_row;
    unsigned int _min_col;
    unsigned int _max_col;

public:
    explicit Page(unsigned int page_num) : note(std::vector<std::map<unsigned int, char>>(100))
    {
        this->_page_number = page_num;
        this->_min_row = (unsigned int)-1;
        this->_max_row = (unsigned int)-1;
        this->_min_col = 100;
        this->_max_col = 0;
    }
    void putCharAt(unsigned int row, unsigned int col, char c);
    char getChar(unsigned int row, unsigned int col);
    void setRowsCols(unsigned int min_row, unsigned int max_row, unsigned int min_col, unsigned int max_col);
};