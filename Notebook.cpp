#include "Notebook.hpp"
#include <iostream>
#include <stdexcept>
using namespace std;
namespace ariel
{

    void Notebook::putCharAt(unsigned int page_num, unsigned int row, unsigned int col, char c)
    {
        try
        {
            this->notebook.at(page_num).note[col][row] = c;
        }
        catch(const std::exception& e){
            cout<<"exception at line 15\n";
        }
    }
    char Notebook::getChar(unsigned int page_num, unsigned int row, unsigned int col)
    {
        try
        {
            if (this->notebook.at(page_num).note[col].count(row) == 1)
            {
                return this->notebook.at(page_num).note[col].at(row);
            }
            return Notebook::empty_char;
        }
        catch (const std::exception &e)
        {
            cout << "error at line 25\n";
            return '_';
        }
    }
    void Notebook::setRowsCols(unsigned int page_num, unsigned int min_row, unsigned int max_row, unsigned int min_col, unsigned int max_col)
    {
        // if (this->notebook.at(page_num).min_row == -1)
        // {
        //     this->notebook.at(page_num).min_row = min_row;
        // }
        // if (this->notebook.at(page_num).max_row == -1)
        // {
        //     this->notebook.at(page_num).max_row = max_row;
        // }
        try
        {
            if (this->notebook.at(page_num).min_row > min_row)
            {
                this->notebook.at(page_num).min_row = min_row;
            }
            if (this->notebook.at(page_num).max_row < max_row)
            {
                this->notebook.at(page_num).max_row = max_row;
            }
            if (this->notebook.at(page_num).min_col > min_col)
            {
                this->notebook.at(page_num).min_col = min_col;
            }
            if (this->notebook.at(page_num).max_col < max_col)
            {
                this->notebook.at(page_num).max_col = max_col;
            }
        }
        catch (const std::exception &e)
        {
            cout << "exception at line 59\n";
        }
    }
    void Notebook::write(unsigned int page_num, unsigned int row_num, unsigned int col_num, Direction direction, std::string s)
    {
        if(this->notebook.count(page_num)==0){
            Page page = Page(page_num);
            this->notebook.insert({page_num, page});
        }
        if (s.length() == 0)
        {
            return;
        }
        if (direction == Direction::Horizontal)
        {
            try
            {
                for (unsigned int i = 0; i < s.length(); i++)
                {
                    if (getChar(page_num, row_num, col_num + i) != '_')
                    {
                        throw invalid_argument("cannot reach the given place in the notebook\n");
                    }
                }
            }
            catch (const std::exception &e)
            {
                cout << "exception at line 88\n";
            }
            try
            {
                setRowsCols(page_num, row_num, row_num, col_num, col_num + s.length() - 1);
                for (unsigned int j = 0; j < s.length(); j++)
                {
                    putCharAt(page_num, row_num, col_num + j, s.at(j));
                }
            }
            catch (const std::exception &e)
            {
                cout << "exception at line 101\n";
            }
        }
        else
        {
            try
            {
                for (unsigned int i = 0; i < s.length(); i++)
                {
                    if (getChar(page_num, row_num + i, col_num) != '_')
                    {
                        throw invalid_argument("cannot override already written char\n");
                    }
                }
            }
            catch (const std::exception &e)
            {
                cout << "cannot override already written char\n";
                return;
            }
            try
            {
                setRowsCols(page_num, row_num, row_num + s.length() - 1, col_num, col_num);
                for (unsigned int j = 0; j < s.length(); j++)
                {
                    putCharAt(page_num, row_num + j, col_num, s.at(j));
                }
            }
            catch (const std::exception &e)
            {
                cout << "exception at line 131\n";
            }
        }
    }
    std::string Notebook::read(unsigned int page_num, unsigned int row_num, unsigned int col_num, Direction direction, unsigned int length)
    {
        if(length<lower_bound || (length>upper_bound && direction == Direction::Horizontal)){
            throw invalid_argument("length must be between 0 to 100\n");
        }
        if(col_num<lower_bound || col_num>upper_bound || row_num<lower_bound){
            throw invalid_argument("rows and cols must be valid arguments!\n");
        }
        if(length+col_num>upper_bound && direction == Direction::Horizontal){
            throw invalid_argument("can't reach to column greater than 100\n");
        }
        std::string sentance;
        if(this->notebook.count(page_num)==0){
            Page page = Page(page_num);
            this->notebook.insert({page_num, page});
        }
        if(direction==Direction::Vertical){
            for(unsigned int i=0; i<length; i++){
                sentance += getChar(page_num, row_num+i, col_num);
            }
        }
        else{
            for(unsigned int i=0; i<length; i++){
                sentance += getChar(page_num, row_num, col_num+i);
            }
        }
        return sentance;
    }
    void Notebook::erase(unsigned int page_num, unsigned int row_num, unsigned int col_num, Direction direction, unsigned int length)
    {
        
        if(length<lower_bound || (length>upper_bound && direction == Direction::Horizontal)){
            throw invalid_argument("length must be between 0 to 100\n");
        }
        if(col_num<lower_bound || col_num>upper_bound || row_num<lower_bound){
            throw invalid_argument("rows and cols must be valid arguments!\n");
        }
        if(length+col_num>upper_bound && direction == Direction::Horizontal){
            throw invalid_argument("can't reach to column greater than 100\n");
        }
        if(this->notebook.count(page_num)==0){
            throw invalid_argument("can't erase from no exsiting page\n");
        }
        if(direction==Direction::Vertical){
            for(unsigned int i=0; i<length; i++){
                putCharAt(page_num, row_num+i, col_num,'~');
            }
        }
        else{
            for(unsigned int i=0; i<length; i++){
                putCharAt(page_num, row_num, col_num+i,'~');
            }
        }
    }
    
    void Notebook::show(unsigned int page_num)
    {
    }
}