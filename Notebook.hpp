#ifndef NOTEBOOK_CPP
#define NOTEBOOK_CPP

#include<map>
#include<vector>
#include<string>
#include "Direction.hpp"
struct Page{
    unsigned long min_row;
    unsigned long max_row;
    int min_col;
    int max_col;
    Page (){
        min_row = (unsigned long) -1;
        max_row = (unsigned long) -1;
        min_col = 100;
        max_col = 0;
    }
};
namespace ariel 
#endif