#include "doctest.h"
#include "Notebook.hpp"
using namespace ariel;

#include <string>
#include <algorithm>
using namespace std;
TEST_CASE("Good input"){
	CHECK(nospaces(mat(9, 7, '@', '-')) == nospaces("@@@@@@@@@\n"
													"@-------@\n"
													"@-@@@@@-@\n"
													"@-@---@-@\n"
													"@-@@@@@-@\n"
													"@-------@\n"
													"@@@@@@@@@"));
    CHECK(nospaces(mat(1,1,'#','-'))==nospaces("#"));
    CHECK(nospaces(mat(5,13,'@','-'))==nospaces("@@@@@\n"
                                                "@---@\n"
                                                "@-@-@\n"
                                                "@-@-@\n"
                                                "@-@-@\n"
                                                "@-@-@\n"
                                                "@-@-@\n"
                                                "@-@-@\n"
                                                "@-@-@\n"
                                                "@-@-@\n"
                                                "@-@-@\n"
                                                "@---@\n"
                                                "@@@@@"));
    CHECK(nospaces(mat(1,3,'?','-'))==nospaces("?\n"
                                               "?\n"
                                               "?"));
    CHECK(nospaces(mat(3,1,'?','-'))==nospaces("???"));
    CHECK(nospaces(mat(3,3,'c','='))==nospaces("ccc\n"
                                               "c=c\n"
                                               "ccc"));
    CHECK(nospaces(mat(3,5,'?','!'))==nospaces("???\n"
                                               "?!?\n"
                                               "?!?\n"
                                               "?!?\n"
                                               "???"));
    CHECK(nospaces(mat(5,5,'?','?'))==nospaces("?????\n"
                                               "?????\n"
                                               "?????\n"
                                               "?????\n"
                                               "?????"));
}
TEST_CASE("Bad inputs") {
    CHECK_THROWS(mat(10, 5, '$', '%'));
    CHECK_THROWS(mat(0, 0, 'x', 'y'));
    CHECK_THROWS(mat(3, -3, '$', '-'));
    CHECK_THROWS(mat(5, 5, '$', ' '));
    CHECK_THROWS(mat(5, 5, '\n', '^'));
    CHECK_THROWS(mat(3, 1, '@', '\r'));
    CHECK_THROWS(mat(1, 5, 'Q', '\t'));
    CHECK_THROWS(mat(-1, 9, '$', ')'));
    CHECK_THROWS(mat(9, -7, '-', '*'));
    CHECK_THROWS(mat(2, 2, '!', '$'));
    CHECK_THROWS(mat(3, 7, ' ', '@'));
    CHECK_THROWS(mat(-1, -3, '%', '$'));
}