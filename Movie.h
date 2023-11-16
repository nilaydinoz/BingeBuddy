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

    // print info
    void print();

    // input validation
    bool validDirectorName(string director);
    bool validGenreInput(string line);
    bool onlyNumbers(string line);

    // quick sort
    int partition(Movie* arr, int low, int high);
    // helper functions for Quick Sort
    void swap(Movie* a, Movie* b);
    void quickSort(Movie* arr, int low, int high);
    void quickSortRatings(Movie* arr, int low, int high);
    void quickSortNumOfRatings(Movie* arr, int low, int high);
    int partitionRating(Movie* arr, int low, int high);
    int partitionNumOfRatings(Movie* arr, int low, int high);


    // radix sort length
    void radixSortLength(Movie* movies, int size);
    void radixSortLengthHelper(Movie* movies, int size, int digit);
    int findMaxLength(Movie* movies, int size);

    // radix sort ratings
    void radixSortRatings(Movie* movies, int size);
    void radixSortRatingsHelper(Movie* movies, int size, int digit);
    int findMaxRating(Movie* movies, int size);

    // radix sort numratings
    void radixSortNumRatings(Movie* movies, int size);
    void radixSortNumRatingsHelper(Movie* movies, int size, int digit);
    int findMaxNumRating(Movie* movies, int size);

    // operator overload to add object to set
    bool operator<(const Movie& movie1) const;
};
