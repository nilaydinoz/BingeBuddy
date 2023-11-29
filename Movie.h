#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <array>
#include <functional>

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
    // Constructors
    Movie() {}
    Movie(std::string title, std::vector<std::string>& genre, std::vector<std::string>& director, int year, int length, float rating, int numRatings);

    // Getters
    const std::vector<std::string>& getGenre() const;
    const std::vector<std::string>& getDirector() const;
    int getLength() const;
    float getRating() const;
    int getNumRatings() const;
    int getYear() const;
    std::string getTitle() const;

    // Print
    void print();

    // Validate User Input
    bool validateDirector(const std::string& director);
    bool validateGenre(const std::string& line);

    // Operator Overloading
    bool operator<(const Movie& movie1) const;

    // Merge Sort Functions
    void mergeLength(std::vector<Movie>&, int left, int mid, int right);
    void mergeRatings(std::vector<Movie>&, int left, int mid, int right);
    void mergeNumRatings(std::vector<Movie>&, int left, int mid, int right);
    void mergeYears(std::vector<Movie>&, int left, int mid, int right);
    void mergeGenres(std::vector<Movie>&, int left, int mid, int right);
    void mergeDirectors(std::vector<Movie>&, int left, int mid, int right);
    void mergeTitles(std::vector<Movie>&, int left, int mid, int right);

    void mergeSortGenres(std::vector<Movie>& arr, int left, int right);
    void mergeSortDirectors(std::vector<Movie>& arr, int left, int right);
    void mergeSortTitles(std::vector<Movie>& arr, int left, int right);
    void mergeSortLength(std::vector<Movie>& arr, int left, int right);
    void mergeSortRatings(std::vector<Movie>& arr, int left, int right);
    void mergeSortNumRatings(std::vector<Movie>& arr, int left, int right);
    void mergeSortYears(std::vector<Movie>&, int left, int right);

    // Shell Sort Functions
    // Citation: https://www.geeksforgeeks.org/templates-cpp/#
    template <typename T>
    // Citation: DSA Fall 2023 Slides and Lectures with Professor Amanpreet Kapoor
    static void shellSort(T* arr, int size, const std::function<bool(const T&, const T&)>& compare) {
        for (int gap = size / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < size; ++i) {
                T temp = arr[i];
                int j;

                for (j = i; j >= gap && compare(arr[j - gap], temp); j -= gap) {
                    arr[j] = arr[j - gap];
                }

                arr[j] = temp;
            }
        }
    }

    // Comparison functions for different criteria
    static bool compareByTitle(const Movie& a, const Movie& b) {
        return a.getTitle() < b.getTitle();
    }

    static bool compareByRating(const Movie& a, const Movie& b) {
        return a.getRating() < b.getRating();
    }

    static bool compareByYear(const Movie& a, const Movie& b) {
        return a.getYear() < b.getYear();
    }

    static bool compareByNumRatings(const Movie& a, const Movie& b) {
        return a.getNumRatings() < b.getNumRatings();
    }

    static bool compareByLength(const Movie& a, const Movie& b) {
        return a.getLength() < b.getLength();
    }

    static bool compareByDirector(const Movie& a, const Movie& b) {
        const std::vector<std::string>& directorsA = a.getDirector();
        const std::vector<std::string>& directorsB = b.getDirector();

        // Compare directors lexicographically
        for (size_t i = 0; i < directorsA.size() && i < directorsB.size(); ++i) {
            if (directorsA[i] != directorsB[i]) {
                return directorsA[i] < directorsB[i];
            }
        }

        return a.getDirector() < b.getDirector();
    }

    static bool compareByGenre(Movie a, Movie b) {
        const std::vector<std::string>& genresA = a.getGenre();
        const std::vector<std::string>& genresB = b.getGenre();

        // Compare genres lexicographically
        for (size_t i = 0; i < genresA.size() && i < genresB.size(); ++i) {
            if (genresA[i] != genresB[i]) {
                return genresA[i] < genresB[i];
            }
        }

        return a.getGenre() < b.getGenre();
    }
};
