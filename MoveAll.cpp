/*
Olti Gjoni CSCI 335
Project 1
Due March 1, 2024
*/

#include "MoveAll.hpp"
#include "Book.hpp"

// Moves all Books in "source" with the specified keyword to "dest".
void moveAll (const std::string keyword, std::vector<Book> &source, std::vector<Book> &dest){
    const auto t1_start = std::chrono::steady_clock::now();
    int books_moved = 0; // counts books moved

    // Iterate through the source vector and move books that match the keyword
    for (auto it = source.begin(); it != source.end(); ) {
        // Check if the current book has the keyword
        if (std::find(it->getKeywords().begin(), it->getKeywords().end(), keyword) != it->getKeywords().end()) {
            // Move the book to the destination vector
            dest.push_back(std::move(*it));
            // Remove the book from the source vector
            it = source.erase(it);
            // Increment the count of moved books
            books_moved++;
        } else {
            ++it; // Only increment if not erasing, to avoid skipping elements
        }
    }

    const auto t1_end = std::chrono::steady_clock::now();
    int t1 = std::chrono::duration<double, std::micro>(t1_end - t1_start).count();
    std::cout << "Moved " << books_moved << " books in " << t1 << " microseconds." << std::endl;
}
