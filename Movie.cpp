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

// constructor
Movie::Movie(string title, vector<string>& genre, vector<string>& director, int year, int length, float rating, int numRatings) {
    this->title = title;
    this->genre = genre;
    this->director = director;
    this->year = year;
    this->length = length;
    this->rating = rating;
    this->numRatings = numRatings;
}

// get functions
vector<string>& Movie::getGenre() {
    return this->genre;
}
vector<string>& Movie::getDirector() {
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

// printing movie info
void Movie::print() {
    cout << this->title << endl;
    cout << "    Year: " << this->year << endl;

    cout << "    Genre(s): ";
    // iterating through each genre (if necessary)
    for (string s : this->genre) {
        cout << s;
        if (s != genre.at(genre.size() - 1)) {
            cout << ", ";
        }
    }
    cout << endl;

    cout << "    Director(s): ";
    // iterating through each director (if necessary)
    for (string s : this->director) {
        cout << s;
        if (s != director.at(director.size() - 1)) {
            cout << ", ";
        }
    }
    cout << endl;

    cout << "    Rating: " << this->rating << " (Out of " << this->numRatings << ")" << endl;
    cout << "    Runtime: " << this->length << " minutes" << endl;
}


void Movie::swap(Movie* a, Movie* b) {
    Movie t = *a;
    *a = *b;
    *b = t;
}

// This code is from the sorting lecture slides
int Movie::partition(Movie* arr, int low, int high) {
    int pivot = arr[low].getLength();
    int up = low;
    int down = high;
    while (up < down) {
        for (int j = up; j < high; j++) {
            if (arr[up].getLength() > pivot) {
                break;
            }
            up++;
        }
        for (int j = high; j > low; j--) {
            if (arr[down].getLength() < pivot) {
                break;
            }
            down--;
        }
        if (up < down) {
            swap(&arr[up], &arr[down]);
        }
    }
    swap(&arr[low], &arr[down]);
    return down;
}
int Movie::partitionRating(Movie* arr, int low, int high) {

    float pivot = arr[low].getRating();
    int up = low;
    int down = high;
    while (up < down) {
        for (int j = up; j < high; j++) {
            if (arr[up].getRating() > pivot) {
                break;
            }
            up++;
        }
        for (int j = high; j > low; j--) {
            if (arr[down].getRating() < pivot) {
                break;
            }
            down--;
        }
        if (up < down) {
            swap(&arr[up], &arr[down]);
        }
    }
    swap(&arr[low], &arr[down]);
    return down;
}

int Movie::partitionNumOfRatings(Movie* arr, int low, int high) {
    int pivot = arr[low].getNumRatings();
    int up = low;
    int down = high;
    while (up < down) {
        for (int j = up; j < high; j++) {
            if (arr[up].getNumRatings() > pivot) {
                break;
            }
            up++;
        }
        for (int j = high; j > low; j--) {
            if (arr[down].getNumRatings() < pivot) {
                break;
            }
            down--;
        }
        if (up < down) {
            swap(&arr[up], &arr[down]);
        }
    }
    swap(&arr[low], &arr[down]);
    return down;
}

void Movie::quickSort(Movie* arr, int low, int high) { // This code is from the sorting lecture slides

    if (low < high) {
        int pivot = partition(arr, low, high);
        quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
    }
}

void Movie::quickSortRatings(Movie* arr, int low, int high) {
    if (low < high) {
        int pivot = partitionRating(arr, low, high);
        quickSortRatings(arr, low, pivot - 1);
        quickSortRatings(arr, pivot + 1, high);
    }
}

void Movie::quickSortNumOfRatings(Movie* arr, int low, int high) {
    if (low < high) {
        int pivot = partitionNumOfRatings(arr, low, high);
        quickSortNumOfRatings(arr, low, pivot - 1);
        quickSortNumOfRatings(arr, pivot + 1, high);
    }
}


// checks that a name is valid
bool Movie::validDirectorName(string director) {
    for (int i = 0; i < director.length(); i++) {
        if (isalpha(director.at(i)) == 0 && director.at(i) != ' ') {
            return false;
        }

    }
    return true;
}

// checks that genre input is valid
bool Movie::validGenreInput(string line) {
    istringstream stream(line);
    vector<int> input;
    string read;

    // check if the input contains only digits or spaces
    if (!onlyNumbers(line)) {
        return false;
    }

    // read in each number corresponding to a genre
    while (getline(stream, read, ' ')) {
        input.push_back(stoi(read));
    }

    // up to three genres are allowed
    if (input.size() > 3) {
        return false;
    }

    // up to 24 genres
    for (int i = 0; i < input.size(); i++) {
        if (input.at(i) <= 0 || input.at(i) > 24) {
            return false;
        }
    }

    return true;
}

// checks there are only numbers in input
bool Movie::onlyNumbers(string line) {
    // check that genre input only contains numbers or spaces
    for (int i = 0; i < line.length(); i++) {
        if (!isdigit(line.at(i)) && line.at(i) != ' ') {
            return false;
        }
    }
    return true;
}



bool Movie::operator<(const Movie& movie1) const {
    return title < movie1.title;
}

// radix sort for length
void Movie::radixSortLength(Movie* movies, int size) {

    int max = findMaxLength(movies, size);


    for (int digit = 1; max / digit > 0; digit *= 10) {
        radixSortLengthHelper(movies, size, digit);
    }

}

void Movie::radixSortLengthHelper(Movie* movies, int size, int digit) {


    // create temp array same size as original
    Movie* temp = new Movie[size];


    // create a counting array to store count of each digit 0-9
    int count[10] = { 0 };

    // store the number of occurences of each character
    for (int i = 0; i < size; i++) {
        count[(movies[i].getLength() / digit) % 10]++;
    }

    // update the count array to reflect the position in the final array
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // transfer the values into the temporary array
    for (int i = size - 1; i >= 0; i--) {
        temp[count[(movies[i].getLength() / digit) % 10] - 1] = movies[i];
        count[(movies[i].getLength() / digit) % 10]--;
    }

    for (int i = 0; i < size; i++) {
        movies[i] = temp[i];
    }

    delete[] temp;

}

int Movie::findMaxLength(Movie* movies, int size) {
    // finds max length
    int max = movies[0].getLength();
    for (int i = 0; i < size; i++) {
        if (movies[i].getLength() > max) {
            max = movies[i].getLength();
        }
    }
    return max;
}

// radix sort for ratings
void Movie::radixSortRatings(Movie* movies, int size) {

    for (int i = 0; i < size; i++) {
        movies[i].rating = movies[i].rating * 10.0;
    }

    int max = findMaxRating(movies, size);
    for (int digit = 1; max / digit > 0; digit *= 10) {
        radixSortRatingsHelper(movies, size, digit);
    }

    for (int i = 0; i < size; i++) {
        movies[i].rating = (float)movies[i].rating / (float)10.0;
    }
}

void Movie::radixSortRatingsHelper(Movie* movies, int size, int digit) {
    // create temp array same size as original
    Movie* temp = new Movie[size];

    // create a counting array to store count of each digit 0-9
    int count[10] = { 0 };

    // store the number of occurences of each character
    for (int i = 0; i < size; i++) {
        count[((int)movies[i].getRating() / digit) % 10]++;
    }

    // update the count array to reflect the position in the final array
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // transfer the values into the temporary array
    for (int i = size - 1; i >= 0; i--) {
        temp[count[((int)movies[i].getRating() / digit) % 10] - 1] = movies[i];
        count[((int)movies[i].getRating() / digit) % 10]--;
    }

    for (int i = 0; i < size; i++) {
        movies[i] = temp[i];
    }

    delete[] temp;
}

int Movie::findMaxRating(Movie* movies, int size) {
    // finds the max rating
    int max = movies[0].getRating();
    for (int i = 0; i < size; i++) {
        if ((int)movies[i].getRating() > max) {
            max = (int)movies[i].getRating();
        }
    }
    return max;
}

// radix sort for numRatings
void Movie::radixSortNumRatings(Movie* movies, int size) {
    int max = findMaxNumRating(movies, size);

    for (int digit = 1; max / digit > 0; digit *= 10) {
        radixSortNumRatingsHelper(movies, size, digit);
    }
}

void Movie::radixSortNumRatingsHelper(Movie* movies, int size, int digit) {
    // create temp array same size as original
    Movie* temp = new Movie[size];


    // create a counting array to store count of each digit 0-9
    int count[10] = { 0 };

    // store the number of occurences of each character
    for (int i = 0; i < size; i++) {
        count[(movies[i].getNumRatings() / digit) % 10]++;
    }

    // update the count array to reflect the position in the final array
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // transfer the values into the temporary array
    for (int i = size - 1; i >= 0; i--) {
        temp[count[(movies[i].getNumRatings() / digit) % 10] - 1] = movies[i];
        count[(movies[i].getNumRatings() / digit) % 10]--;
    }

    for (int i = 0; i < size; i++) {
        movies[i] = temp[i];
    }

    delete[] temp;
}

int Movie::findMaxNumRating(Movie* movies, int size) {
    // finds the max number of ratings
    int max = movies[0].getNumRatings();
    for (int i = 0; i < size; i++) {
        if (movies[i].getNumRatings() > max) {
            max = movies[i].getNumRatings();
        }
    }
    return max;
}
