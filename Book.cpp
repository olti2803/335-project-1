/*
Olti Gjoni CSCI 335
Project 1
Due March 1, 2024
*/
#include "Book.hpp"

// Default constructor
Book::Book() : title_(""), author_(""), ISBN_(0), icon_(nullptr), price_(0.0), keywords_({}), blurb_("") {}

// Copy constructor
Book::Book(const Book& rhs) : title_(rhs.title_), author_(rhs.author_), ISBN_(rhs.ISBN_), icon_(new int[80]), price_(rhs.price_), keywords_(rhs.keywords_), blurb_(rhs.blurb_) {
    std::copy(rhs.icon_, rhs.icon_ + 80, icon_);
}

// Move constructor
Book::Book(Book&& rhs) : title_(std::move(rhs.title_)), author_(std::move(rhs.author_)), ISBN_(rhs.ISBN_), icon_(rhs.icon_), price_(rhs.price_), keywords_(std::move(rhs.keywords_)), blurb_(std::move(rhs.blurb_)) {
    rhs.icon_ = nullptr;
}

// Destructor
Book::~Book() {
    delete[] icon_;
}

// Copy assignment operator
Book& Book::operator=(const Book& rhs) {
    if (this != &rhs) {
        title_ = rhs.title_;
        author_ = rhs.author_;
        ISBN_ = rhs.ISBN_;
        price_ = rhs.price_;
        keywords_ = rhs.keywords_;
        blurb_ = rhs.blurb_;
        int* new_icon = new int[80];
        std::copy(rhs.icon_, rhs.icon_ + 80, new_icon);
        delete[] icon_;
        icon_ = new_icon;
    }
    return *this;
}

// Move assignment operator
Book& Book::operator=(Book&& rhs) {
    if (this != &rhs) {
        title_ = std::move(rhs.title_);
        author_ = std::move(rhs.author_);
        ISBN_ = rhs.ISBN_;
        price_ = rhs.price_;
        keywords_ = std::move(rhs.keywords_);
        blurb_ = std::move(rhs.blurb_);
        delete[] icon_;  // Delete current icon before moving
        icon_ = rhs.icon_;  // Transfer ownership
        rhs.icon_ = nullptr;  // Ensure the moved-from object is in a safe state
    }
    return *this;
}

// Getters and setters
const std::string& Book::getTitle() const { return title_; }
void Book::setTitle(const std::string& title) { title_ = title; }

const std::string& Book::getAuthor() const { return author_; }
void Book::setAuthor(const std::string& author) { author_ = author; }

long long int Book::getISBN() const { return ISBN_; }
void Book::setISBN(long long int ISBN) { ISBN_ = ISBN; }

const int* Book::getIcon() const { return icon_; }
void Book::setIcon(int* icon) {
    delete[] icon_;  // Free existing icon before setting new one
    icon_ = new int[80];
    std::copy(icon, icon + 80, icon_);
}

float Book::getPrice() const { return price_; }
void Book::setPrice(float price) { price_ = price; }

const std::vector<std::string>& Book::getKeywords() const { return keywords_; }
void Book::setKeywords(const std::vector<std::string>& keywords) { keywords_ = keywords; }

const std::string& Book::getBlurb() const { return blurb_; }
void Book::setBlurb(const std::string& blurb) { blurb_ = blurb; }

// Print function
void Book::print() const {
    std::cout << "Title: " << title_ << std::endl;
    std::cout << "Author: " << author_ << std::endl;
    std::cout << "ISBN: " << ISBN_ << std::endl;
    std::cout << "Price: " << std::fixed << std::setprecision(2) << price_ << std::endl;
    std::cout << "Keywords: ";
    for (const auto& keyword : keywords_) {
        std::cout << keyword << " ";
    }
    std::cout << std::endl;
    std::cout << "Blurb: " << blurb_ << std::endl;
    std::cout << "Icon: ";
    if (icon_ != nullptr) {
        for (int i = 0; i < 80; ++i) {
            std::cout << icon_[i] << " ";
        }
    }
    std::cout << std::endl;
}
