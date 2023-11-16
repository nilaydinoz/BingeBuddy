#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <array>

class Movie {
private:
    std::string title = "";
    std::vector<std::string> genre = {};
    std::vector<std::string> director = {};
    int year = 0;
    int length = 0;
    float rating = 0.0;
    int numRatings = 0;
public:
    //member functions and constructors
    Movie() {}
    Movie(std::string title, std::vector<std::string>& genre, std::vector<std::string>& director, int year, int length, float rating, int numRatings);
    // get functions
    std::vector<std::string>& getGenre();
    std::vector<std::string>& getDirector();
    int getLength();
    float getRating();
    int getNumRatings();

    // operator overload to add object to set
    bool operator<(const Movie& movie1) const;

};

// constructor
Movie::Movie(std::string title, std::vector<std::string>& genre, std::vector<std::string>& director, int year, int length, float rating, int numRatings) {
    this->title = title;
    this->genre = genre;
    this->director = director;
    this->year = year;
    this->length = length;
    this->rating = rating;
    this->numRatings = numRatings;
}

// get functions
std::vector<std::string>& Movie::getGenre() {
    return this->genre;
}
std::vector<std::string>& Movie::getDirector() {
    return this->director;
}
int Movie::getLength() {
    return this->length;
}
float Movie::getRating() {
    return this->rating;
}
int Movie::getNumRatings() {
    return this->numRatings;
}

//// printing movie info
//void Movie::print() {
//    cout << this->title << endl;
//    cout << "    Year: " << this->year << endl;
//
//    cout << "    Genre(s): ";
//    // iterating through each genre (if necessary)
//    for (string s : this->genre) {
//        cout << s;
//        if (s != genre.at(genre.size() - 1)) {
//            cout << ", ";
//        }
//    }
//    cout << endl;
//
//    cout << "    Director(s): ";
//    // iterating through each director (if necessary)
//    for (string s : this->director) {
//        cout << s;
//        if (s != director.at(director.size() - 1)) {
//            cout << ", ";
//        }
//    }
//    cout << endl;
//
//    cout << "    Rating: " << this->rating << " (Out of " << this->numRatings << ")" << endl;
//    cout << "    Runtime: " << this->length << " minutes" << endl;
//}

bool Movie::operator<(const Movie& movie1) const {
    return title < movie1.title;
}