#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>
#include <algorithm>
#include "Book.hpp"
#include "MoveAll.hpp"

int main(){
  
  std::vector<Book> catalog, cart;

  // open file
  std::string filename = "1000bookInputFile.txt";
  std::ifstream fin(filename);

  // define expected format
  std::regex title("(Title: )(.*)");
  std::regex author("(Author: )(.*)");
  std::regex ISBN("(ISBN: )(.*)");
  std::regex icon("(Icon: )(.*)");
  std::regex price("(Price: \\$)(.*)");
  std::regex keywords("(Keywords: )(.*)");
  std::regex blurb("(Blurb: )(.*)");

  // declare helper variables for reading from file
  std::string line;
  std::smatch match;
  Book temp;

  // reads all 7 fields in each iteration and copies the value of each field into Book "temp"
  // pushes "temp" onto the back of "catalog" at the end of the iteration
  while (getline(fin,line)){

    // Title
    if (std::regex_search(line, match, title)){
      temp.setTitle(match[2]);
    }

    // Author
    getline(fin,line);
    if (std::regex_search(line, match, author)){
      temp.setAuthor(match[2]);
    }

    // ISBN
    getline(fin,line);
    if (std::regex_search(line, match, ISBN)){
      temp.setISBN(std::stoll(match[2]));
    }

    // Icon
    getline(fin,line);
    if (std::regex_search(line, match, icon)){
      std::stringstream numstring(match[2]);
      int* numarray = new int[80];
      for (int i = 0; i < 80; ++i){
        numstring >> numarray[i];
      }
      temp.setIcon(numarray);
      delete[] numarray; // Proper memory handling
    }

    // Price
    getline(fin,line);
    if (std::regex_search(line, match, price)){
      temp.setPrice(std::stof(match[2]));
    }

    // Keywords
    getline(fin,line);
    if (std::regex_search(line, match, keywords)){
      std::vector<std::string> keyVec;
      std::string keyToken;
      std::stringstream ss(match[2]);
      while (getline(ss, keyToken, ',')) {
        keyVec.push_back(keyToken);
      }
      temp.setKeywords(keyVec);
    }

    // Blurb
    getline(fin,line);
    if (std::regex_search(line, match, blurb)){
      temp.setBlurb(match[2]);
    }

    catalog.push_back(temp); // Add the populated 'temp' Book object to 'catalog'
    getline(fin, line); // Skip any blank lines between book entries
  }

  // Test cases
  std::cout << "Catalog contains " << catalog.size() << " books.\n";
  std::cout << "First 5 books in the catalog:\n";
  for (int i = 0; i < 5 && i < catalog.size(); ++i) {
    catalog[i].print();
    std::cout << '\n'; // Separate books by a newline for better readability
  }

  std::string keyword = "Spanish Literature"; // Replace with a keyword present in your books for testing
  moveAll(keyword, catalog, cart);
  std::cout << "After moving, catalog contains " << catalog.size() << " books and cart contains " << cart.size() << " books.\n";

  if (!cart.empty()) {
    std::cout << "Books moved to cart:\n";
    for (Book& book : cart) {
      book.print();
      std::cout << '\n'; // Separate books by a newline
    }
  }

  return 0;
}