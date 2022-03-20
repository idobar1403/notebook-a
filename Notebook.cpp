#include "Notebook.hpp"
#include <iostream>
#include <stdexcept>
using namespace std;
namespace ariel
{
    void Notebook::write(unsigned int page_num, unsigned int row_num, unsigned int col_num, Direction direction, std::string s)
    {
        if (s.length() == 0)
        {
            return;
        }
        if (direction == Direction::Horizontal)
        {
            for (unsigned int i = 0; i < s.length(); i++)
            {
                if (notebook.at(page_num).getChar(row_num, col_num + i) != '_')
                {
                    throw invalid_argument("cannot reach the given place in the notebook");
                }
            }
            notebook.at(page_num).setRowsCols(row_num, row_num, col_num, col_num + s.length() - 1);
            for (unsigned int j = 0; j < s.length(); j++)
            {
                notebook.at(page_num).putCharAt(row_num, col_num + j, s.at(j));
            }
        }
        else
        {
            for (unsigned int i = 0; i < s.length(); i++)
            {
                if (notebook.at(page_num).getChar(row_num + i, col_num) != '_')
                {
                    throw invalid_argument("cannot reach the given place in the notebook");
                }
            }
            notebook.at(page_num).setRowsCols(row_num, row_num + s.length() - 1, col_num, col_num);
            for (unsigned int j = 0; j < s.length(); j++)
            {
                notebook.at(page_num).putCharAt(row_num + j, col_num, s.at(j));
            }
        }
    }
    std::string read(unsigned int page_num, unsigned int row_num, unsigned int col_num, Direction direction, unsigned int length)
    {
        return "hi";
    }
    void erase(unsigned int page_num, unsigned int row_num, unsigned int col_num, Direction direction, unsigned int length)
    {
    }
    void show(unsigned int page_num)
    {
    }
}