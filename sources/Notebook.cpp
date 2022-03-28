#include "Notebook.hpp"
#include "Direction.hpp"
#include <iostream>
using namespace std;

namespace ariel {

    void Notebook::write(int page, int row, int col, Direction direction, string const &word){
        //Edge case
        if(col >= MAX_ROW_LENGTH){
            throw invalid_argument("Invalid column");
        }
        if(page < 0 || col < 0 || row < 0){
            throw invalid_argument("Invalid parameters");
        }
        if(col + (int)word.size() > MAX_ROW_LENGTH && direction == Direction::Horizontal){
            throw invalid_argument("Invalid column");
        }
        //Check word is valid.
        for(uint i=0; i < word.length() ; i++){
            if(word[i]=='\n' || (int)word[i] < ASCII_LOWER_BOUND || (int)word[i] > ASCII_UPPER_BOUND){
                throw invalid_argument("Invalid chars");
            }
        }
        for(uint i=0; i < word.length(); i++){
            // if(col >= MAX_ROW_LENGTH){
            //     throw invalid_argument("Invalid column");
            // }
            if((bool)_notebook.count(page) && (bool)_notebook[page]._page.count(row) && (bool)_notebook[page]._page[row].count(col)){
                throw invalid_argument("cannot write over an existing text.");
            }
            if(word[i]!='_'){
                _notebook[page]._page[row][col] = word[i];
            }
            if(direction == Direction::Horizontal){ col++;}
            if(direction == Direction::Vertical){ row++;}
        }
    }

    std::string Notebook::read(int page, int row, int col, Direction direction, int word_length){
        //Edge case
        if(col >= MAX_ROW_LENGTH){
            throw invalid_argument("Invalid column");
        }
        if(page < 0 || col < 0 || row < 0 || word_length < 0){
            throw invalid_argument("Invalid parameters");
        }
        if(col + word_length > MAX_ROW_LENGTH && direction == Direction::Horizontal){
            throw invalid_argument("Invalid column");
        }
        string ans;
        for(int i=0; i < word_length; i++){
            if(col >= MAX_ROW_LENGTH){
                throw invalid_argument("Invalid column");
            }
            //Check if value exists.
            if((bool)_notebook.count(page) && (bool)_notebook[page]._page.count(row) && (bool)_notebook[page]._page[row].count(col)){
                ans += _notebook[page]._page[row][col];
            }
            else {
                ans += "_";
            }
            if(direction == Direction::Horizontal){ col++;}
            if(direction == Direction::Vertical){ row++;}
        }
        return ans;
    }

    void Notebook::erase(int page, int row, int col, Direction direction, int word_length){
        //Edge case
        if(col >= MAX_ROW_LENGTH){
            throw invalid_argument("Invalid column");
        }
        if(page < 0 || col < 0 || row < 0 || word_length < 0){
            throw invalid_argument("Invalid parameters");
        }
        if(col + word_length >= MAX_ROW_LENGTH && direction == Direction::Horizontal){
            throw invalid_argument("Invalid column");
        }

        for(uint i=0; i < word_length; i++){
            if(col >= MAX_ROW_LENGTH){
                throw invalid_argument("Invalid column");
            }
            _notebook[page]._page[row][col] = '~';
            if(direction == Direction::Horizontal){ col++;}
            if(direction == Direction::Vertical){ row++;}
        }
    }

    void Notebook::show(int page){
        if(page < 0){
            throw invalid_argument("Invalid page");
        }
        int min_row = _notebook[page]._MIN_ROW;
        int min_col = _notebook[page]._MIN_COL;
        int max_row = _notebook[page]._MAX_ROW;
        int max_col = _notebook[page]._MAX_COL;
        
        for(int i = min_row; i < max_row; i++){
            for(int j = min_col; j < max_col; j++){
                cout << _notebook[page]._page[i][j] << " ";
            }
            cout << "\n" ;
        }
    }

}