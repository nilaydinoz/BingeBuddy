#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <array>
using namespace std;

class Movie {
private:
    string title = "";
    vector<string> genre = {};
    vector<string> director = {};
    int year = 0;
    int length = 0;
    float rating = 0.0;
    int numRatings = 0;
public:
    //member functions and constructors
    Movie() {}
    Movie(string title, vector<string>& genre, vector<string>& director, int year, int length, float rating, int numRatings);
    // get functions
    vector<string>& getGenre();
    vector<string>& getDirector();
    int getLength();
    float getRating();
    int getNumRatings();

    // operator overload to add object to set
    bool operator<(const Movie& movie1) const;

};