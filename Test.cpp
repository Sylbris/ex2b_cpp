/**
 *
 * IMPORTANT: Please write more tests - the tests here are only for example and are not complete.
 *
 * AUTHORS: Dan "Sylbris" Davydov
 *
 * Date: 2021-03
 */

#include "doctest.h"
#include "Direction.hpp"
#include "Notebook.hpp"
#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace ariel;

TEST_CASE("Testing empty notebook")
{
    Notebook notebook;

    // Check fresh new notebook
    CHECK(notebook.read(0, 0, 0, Direction::Horizontal, 5) == "_____");
    CHECK(notebook.read(0, 0, 0, Direction::Vertical, 4) == "____");
    CHECK(notebook.read(0, 0, 0, Direction::Vertical, 0) == "");

    // Different pages different page orientation.
    CHECK(notebook.read(7, 0, 0, Direction::Horizontal, 5) == "_____");
    CHECK(notebook.read(4, 0, 0, Direction::Vertical, 4) == "____");

    // Different row/col
    CHECK(notebook.read(3, 5, 0, Direction::Horizontal, 3) == "___");
    CHECK(notebook.read(3, 0, 7, Direction::Horizontal, 3) == "___");
    CHECK(notebook.read(3, 5, 7, Direction::Horizontal, 3) == "___");
    CHECK(notebook.read(3, 5, 7, Direction::Horizontal, 0) == "");

    // Check invalid column
    CHECK_THROWS(notebook.read(3, 5, 100, Direction::Horizontal, 1));
    CHECK_THROWS(notebook.read(0, 0, 351, Direction::Horizontal, 0));
    CHECK_THROWS(notebook.read(3, 5, 97, Direction::Horizontal, 5));

    // write more then 100 letters.
    string big_word;
    for (uint i = 0; i < 101; i++)
    {
        big_word += "a";
    }
    // try to write, and check that nothing was written.
    CHECK_THROWS(notebook.write(3, 5, 0, Direction::Horizontal, big_word));
    CHECK(notebook.read(3, 5, 0, Direction::Horizontal, 1) == "_");

    //try to write a small word close to the border.
    CHECK_THROWS(notebook.write(3, 5, 98, Direction::Horizontal, "aaa"));
    CHECK(notebook.read(3, 5, 98, Direction::Horizontal, 1) == "_");
}

TEST_CASE("Invalid function parameters")
{

}

TEST_CASE("Various input")
{
    Notebook notebook;
    std::string word;
    int word_len = 10;
    for (int i = 0; i < 5; i++)
    {
        word = generateWord(word_len);
        // posting in different pages.
        notebook.write(i, 5, 5, Direction::Horizontal, word);
        notebook.write(i, 10, 10, Direction::Vertical, word);
        CHECK(notebook.read(i, 5, 5, Direction::Horizontal, word_len) == word);
        CHECK(notebook.read(i, 10, 10, Direction::Vertical, word_len) == word);

        // erase some letters of the word.
        notebook.erase(i, 5, 5, Direction::Horizontal, word_len - i);
        std::string erased_word;
        for (int j = 0; j < word_len - i; j++)
        {
            erased_word += "~";
        }

        CHECK(notebook.read(i, 5, 5, Direction::Horizontal, word_len - i) == erased_word);
    }
}

TEST_CASE("Text overriding")
{
    Notebook notebook;
    std::string word;
    notebook.write(0, 5, 5, Direction::Horizontal, "a");

    //write some words in your notebook & try to scribble over them.
     for(int i = 1; i < 10; i++){
         word = generateWord(i);
         CHECK_THROWS(notebook.write(0, 5, 5, Direction::Horizontal, word));
         CHECK_THROWS(notebook.write(0, 5, 5, Direction::Vertical, word));
         //CHECK(notebook.read(0, 5, 5, Direction::Horizontal, i) == word);
     }
}

/*
generate a random word given a certain length.
*/
std::string ariel::generateWord(int len)
{

    char letters[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q',
                        'r', 's', 't', 'u', 'v', 'w', 'x',
                        'y', 'z'};
    string word = "";
    for (int i = 0; i < len; i++)
    {
        word = word + letters[rand() % 26];
    }

    return word;
}