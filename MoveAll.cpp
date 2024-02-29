/*
Olti Gjoni CSCI 335
Project 1
Due March 1, 2024
*/

#include "MoveAll.hpp"
#include "Book.hpp"

// Moves all Books in "source" with the specified keyword to "dest".
void moveAll(const std::string keyword, std::vector<Book>& source, std::vector<Book>& dest) {
    const auto t1_start = std::chrono::steady_clock::now();
    int books_moved = 0;  // counts books moved

    for (auto it = source.begin(); it != source.end();) {
        if (std::find(it->getKeywords().begin(), it->getKeywords().end(), keyword) != it->getKeywords().end()) {
            dest.push_back(std::move(*it));
            it = source.erase(it);
            books_moved++;
        } else {
            ++it;
        }
    }

    const auto t1_end = std::chrono::steady_clock::now();
    std::cout << "Moved " << books_moved << " books in " << std::chrono::duration<double, std::micro>(t1_end - t1_start).count() << " microseconds.\n";
}