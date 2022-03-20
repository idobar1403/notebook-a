#include "Page.hpp"
char Page::empty_char = '_';
void Page::putCharAt(unsigned int row, unsigned int col, char c)
{
    note[col][row] = c;
}
char Page::getChar(unsigned int row, unsigned int col)
{
    if (note[col].count(row) == 1)
    {
        return note[col].at(row);
    }
    return empty_char;
}
void Page::setRowsCols(unsigned int min_row, unsigned int max_row, unsigned int min_col, unsigned int max_col)
{
    if (this->_min_row == -1)
    {
        this->_min_row = min_row;
    }
    if (this->_max_row == -1)
    {
        this->_max_row = max_row;
    }
    if (this->_min_row > min_row)
    {
        this->_min_row = min_row;
    }
    if (this->_max_row < max_row)
    {
        this->_max_row = max_row;
    }
    if (this->_min_col > min_col)
    {
        this->_min_col = min_col;
    }
    if (this->_max_col < max_col)
    {
        this->_max_col = max_col;
    }
}