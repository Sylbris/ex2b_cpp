#include <iostream>
#include <stdexcept>
#include <map>
#include <string>
#include <vector>
#include "Direction.hpp"
using namespace std;

const uint MAX_ROW_LENGTH = 100;
const int ASCII_LOWER_BOUND = 32;
const int ASCII_UPPER_BOUND = 125;

struct page {
    map<int, map<int, char>> _page;
    //Each page holds the lowest index, where it was written.
    int _MIN_ROW, _MIN_COL; 
    int _MAX_ROW, _MAX_COL;
};

namespace ariel
{
    class Notebook {
        uint _row, _col, _pageNum;
        map<int, page> _notebook;

        public:
            Notebook() {}
            ~Notebook() {}
            void write(int page, int row, int col, Direction direction, string const &word);
            std::string read(int page, int row, int col, Direction direction, int word_length);
            void erase(int page, int row, int col, Direction direction, int word_length);
            void show(int page);

    };

    std::string generateWord(int len);
};