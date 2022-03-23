#include "doctest.h"
#include "Notebook.hpp"
#include "Direction.hpp"
using namespace ariel;
#include <iostream>
#include <string>
using namespace std;
TEST_CASE("Good Writing and reading tests")
{
    ariel::Notebook notebook;
    CHECK_NOTHROW(notebook.write(0, 0, 2, Direction::Horizontal, "good test"));         // simple write
    CHECK(notebook.read(0, 0, 2, Direction::Horizontal, 9) == "good test");             // simple read
    CHECK(notebook.read(0, 0, 2, Direction::Vertical, 9) == "g________");               // simple vertical read
    CHECK_NOTHROW(notebook.write(100, 20, 99, Direction::Vertical, "vertical string")); // vertical write at edge of row
    CHECK(notebook.read(100, 20, 99, Direction::Vertical, 15) == "vertical string");    // vertical read at edge of row
    CHECK(notebook.read(100, 19, 99, Direction::Vertical, 17) == "_vertical string_");  // read also non-writen entries
    CHECK(notebook.read(100, 20, 98, Direction::Horizontal, 2) == "_v");                // read horizontally vertically written string
    CHECK_NOTHROW(notebook.write(20000, 2900, 0, Direction::Horizontal, ""));           // write empty string
    CHECK_NOTHROW(notebook.write(20000, 2900, 99, Direction::Horizontal, "1"));         // check that get no errors on writing on edge
    CHECK(notebook.read(20000, 2900, 0, Direction::Horizontal, 3) == "___");            // read non written entries
    CHECK_NOTHROW(notebook.read(0, 0, 0, Direction::Horizontal, 0));                    // nothing to read
    std::string s;
    std::string s2;
    for (int i = 0; i < 60; i++) // horizontal writing loop
    {
        CHECK_NOTHROW(notebook.write(1, 2900, i, Direction::Horizontal, "y"));
        s2 = "";
        for (int j = 0; j < i; j++) // horizontal reading loop
        {
            s2 += 'y';
            CHECK(notebook.read(1, 2900, 0, Direction::Horizontal, j + 1) == s2);
        }
        CHECK(notebook.read(1, 2900, 0, Direction::Horizontal, i) == s);
        s += 'y';
    }
    std::string s3;
    for (int i = 0; i < 120; i++) // vertical writing and reading loop, more than 100 chars
    {
        s3 += 'y';
        CHECK_NOTHROW(notebook.write(2, i, 0, Direction::Vertical, "y"));
        CHECK(notebook.read(2, 0, 0, Direction::Vertical, i + 1) == s3);
    }
}
TEST_CASE("Good erase tests")
{
    ariel::Notebook notebook;
    CHECK_NOTHROW(notebook.write(0, 0, 2, Direction::Horizontal, "good test"));         // simple write
    CHECK_NOTHROW(notebook.write(100, 20, 99, Direction::Vertical, "vertical string")); // simple write
    CHECK_NOTHROW(notebook.write(20000, 2900, 0, Direction::Horizontal, ""));           // simple write
    CHECK_NOTHROW(notebook.erase(0, 0, 2, Direction::Horizontal, 3));                   // erase some chars
    CHECK(notebook.read(0, 0, 2, Direction::Horizontal, 9) == "~~~d test");             // check that it's actually got deleted
    CHECK_NOTHROW(notebook.erase(0, 0, 2, Direction::Horizontal, 3));                   // erase some chars
    CHECK(notebook.read(0, 0, 2, Direction::Horizontal, 9) == "~~~d test");             // check that it's actually got deleted
    CHECK(notebook.read(0, 0, 2, Direction::Vertical, 3) == "~__");                     // check that it's actually got deleted
    CHECK_NOTHROW(notebook.erase(100, 20, 99, Direction::Vertical, 14));                // erase some chars
    CHECK(notebook.read(100, 20, 99, Direction::Vertical, 15) == "~~~~~~~~~~~~~~g");    // check that it's actually got deleted
    CHECK_NOTHROW(notebook.erase(3, 3, 3, Direction::Horizontal, 3));
    CHECK_NOTHROW(notebook.erase(3, 3, 3, Direction::Horizontal, 3)); // erase the same entries twice
    std::string s;
    for (int i = 0; i < 40; i++)
    {
        s += '~';
    }
    CHECK_NOTHROW(notebook.erase(1000, 30, 50, Direction::Vertical, 40));        // erase big amount of chars
    CHECK(notebook.read(1000, 30, 50, Direction::Vertical, 40) == s);            // check that it's actually got deleted
    CHECK_NOTHROW(notebook.erase(30, 10, 90, Direction::Horizontal, 10));        // erase some chars
    CHECK(notebook.read(30, 10, 90, Direction::Horizontal, 10) == "~~~~~~~~~~"); // check that it's actually got deleted
    CHECK_NOTHROW(notebook.erase(0, 0, 0, Direction::Horizontal, 0));            // empty length to erase
    std::string s1;
    for (int i = 0; i < 100; i++) // horizontal erase loop
    {
        CHECK_NOTHROW(notebook.erase(1, 2900, i, Direction::Horizontal, 1));
        CHECK(notebook.read(1, 2900, 0, Direction::Horizontal, i) == s1);
        s1 += '~';
    }
    std::string s2;
    for (int i = 0; i < 50; i++) // vertical erase loop, more than 100 chars
    {
        CHECK_NOTHROW(notebook.erase(2, i, 0, Direction::Vertical, i + 1));
        s2 = "";
        for (int j = 0; j < 2 * i - 1; j++) // vertical read loop, more than 100 chars
        {
            s2 += '~';
            CHECK(notebook.read(2, 0, 0, Direction::Vertical, j + 1) == s2);
        }
    }
}
TEST_CASE("Bad inputs")
{
    ariel::Notebook notebook;
    std::string s;
    for (int i = 0; i < 11; i++)
    {
        s += 'i';
    }
    CHECK_THROWS(notebook.write(100000, 3, 90, Direction::Horizontal, s)); // write over the limit of coloumns
    CHECK_THROWS(notebook.write(1000, 3, 101, Direction::Horizontal, "")); // start at unavailable column
    CHECK_THROWS(notebook.write(1000, 3, 101, Direction::Vertical, ""));   // start at unavailable column
    for (int i = 0; i < 90; i++)
    {
        s += 'i';
    }
    CHECK_THROWS(notebook.write(0, 9, 0, Direction::Horizontal, s));       // write over the limit of chars per row
    CHECK_THROWS(notebook.erase(1, 3, 101, Direction::Vertical, 0));       // unavailable column
    CHECK_THROWS(notebook.erase(1, 3, 101, Direction::Horizontal, 0));     // unavailable column
    CHECK_THROWS(notebook.erase(5, 2, 9, Direction::Horizontal, 92));      // erase over the limit of chars per row
    CHECK_THROWS(notebook.read(2, 2, 210, Direction::Horizontal, 0));      // unavailable column
    CHECK_THROWS(notebook.read(2, 2, 210, Direction::Vertical, 0));        // unavailable column
    CHECK_THROWS(notebook.read(3, 95, 90, Direction::Horizontal, 11));     // read reach to an unavailable column
    CHECK_THROWS(notebook.write(1000, 3, 100, Direction::Vertical, ""));   // unavailable column
    CHECK_THROWS(notebook.write(1000, 3, 100, Direction::Horizontal, "")); // unavailable column
    CHECK_THROWS(notebook.read(1000, 3, 100, Direction::Horizontal, 0));   // unavailable column
    CHECK_THROWS(notebook.read(1000, 3, 100, Direction::Vertical, 0));     // unavailable column
    CHECK_THROWS(notebook.erase(1000, 3, 100, Direction::Vertical, 0));    // unavailable column
    CHECK_THROWS(notebook.erase(1000, 3, 100, Direction::Horizontal, 0));  // unavailable column
    CHECK_THROWS(notebook.write(3, 3, 3, Direction::Horizontal, "abc~def")); // cant write '~', onlt at erase
    CHECK_THROWS(notebook.write(3, 3, 3, Direction::Vertical, "abc~def")); // cant write '~', onlt at erase
}
TEST_CASE("Negative inputs")
{
    ariel::Notebook notebook;
    CHECK_THROWS(notebook.write(-1, 9, 0, Direction::Horizontal, "fail"));   // negative argument
    CHECK_THROWS(notebook.write(1, -9, 0, Direction::Horizontal, "fail"));   // negative argument
    CHECK_THROWS(notebook.write(1, 9, -12, Direction::Horizontal, "fail"));  // negative argument
    CHECK_THROWS(notebook.write(-1, -20, 0, Direction::Horizontal, "fail")); // negative argument
    CHECK_THROWS(notebook.write(-1, 9, -3, Direction::Horizontal, "fail"));  // negative argument
    CHECK_THROWS(notebook.read(-1, 9, 0, Direction::Horizontal, 3));         // negative argument
    CHECK_THROWS(notebook.read(1, 9, -30, Direction::Vertical, 0));          // negative argument
    CHECK_THROWS(notebook.read(1, 9, 30, Direction::Horizontal, -9));        // negative length to read
    CHECK_THROWS(notebook.erase(-1, 9, 0, Direction::Vertical, 40));         // negative argument
    CHECK_THROWS(notebook.erase(1, 9, 0, Direction::Horizontal, -6));        // negative length to erase
}
TEST_CASE("Write over written or deleted entries")
{
    ariel::Notebook notebook;
    for (int page = 0; page < 10; page++)
    {
        for (int row = 0; row < 10; row++)
        {
            for (int col = 0; col < 40; col++)
            {
                CHECK_NOTHROW(notebook.write(page, row, col, Direction::Horizontal, "f")); // write one char
                CHECK_THROWS(notebook.write(page, row, col, Direction::Horizontal, "a"));  // can't write if already written at the entry
            }
        }
    }
    for (int page = 0; page < 10; page++)
    {
        for (int row = 0; row < 10; row++)
        {
            for (int col = 0; col < 40; col++)
            {
                CHECK_NOTHROW(notebook.erase(page, row, col, Direction::Horizontal, 1));  // erase one char
                CHECK_THROWS(notebook.write(page, row, col, Direction::Horizontal, "a")); // can't write on deleted entry
            }
        }
    }
}