#include "Movie.h"

// Constructor
Movie::Movie(std::string title, std::vector<std::string>& genre, std::vector<std::string>& director, int year, int length, float rating, int numRatings) {
    this->title = title;
    this->genre = genre;
    this->director = director;
    this->year = year;
    this->length = length;
    this->rating = rating;
    this->numRatings = numRatings;
}

// Getters
const std::vector<std::string>& Movie::getGenre() const{
    return this->genre;
}

const std::vector<std::string> & Movie::getDirector() const{
    return this->director;
}

int Movie::getLength() const {
    return this->length;
}

float Movie::getRating() const {
    return this->rating;
}

int Movie::getNumRatings() const {
    return this->numRatings;
}

int Movie::getYear() const {
    return this->year;
}

std::string Movie::getTitle() const {
    return this->title;
}

bool Movie::operator<(const Movie& movie1) const {
    return getTitle() < movie1.getTitle();
}

// Print
void Movie::print() {
    std::cout << this->title << std::endl;
    std::cout << "    Year: " << this->year << std::endl;
    std::cout << "    Genre(s): ";

    for (std::string s : this->genre) {
        std::cout << s;
        if (s != genre.at(genre.size() - 1)) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;

    std::cout << "    Director(s): ";
    for (std::string s : this->director) {
        std::cout << s;
        if (s != director.at(director.size() - 1)) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;

    std::cout << "    Rating: " << this->rating << " (Out of " << this->numRatings << ")" << std::endl;
    std::cout << "    Runtime: " << this->length << " minutes" << std::endl;
}

// Validate director input
bool Movie::validateDirector(const std::string& director) {
    for (char c : director) {
        if (!isalpha(c) && c != ' ') {
            return false;
        }
    }
    return true;
}

// Validate genre input
bool Movie::validateGenre(const std::string& line) {
    std::istringstream stream(line);
    std::vector<int> input;
    std::string read;

    // Connect each input number to the corresponding genre
    while (getline(stream, read, ' ')) {
        try {
            int num = stoi(read);
            input.push_back(num);
        }
        catch (const std::invalid_argument& e) {
            return false; // Invalid integer in the input
        }
        catch (const std::out_of_range& e) {
            return false; // Integer out of range
        }
    }

    if (input.size() > 3) {
        return false;
    }

    for (int num : input) {
        if (num <= 0 || num > 24) {
            return false;
        }
    }

    return true;
}

// Merge Sort Functions
// Citation: Pages 88 - 90 of Sorting pdf: https://ufl.instructure.com/courses/488814/files/79874644?wrap=1
void Movie::mergeGenres(std::vector<Movie>& arr, int left, int mid, int right) {
    int leftSize = mid - left + 1;
    int rightSize = right - mid;
    int leftPtr = 0;
    int rightPtr = 0;
    int mergedPtr = left;
    std::vector<Movie> leftVec;
    std::vector<Movie> rightVec;

    for (int i = 0; i < leftSize; i++) {
        leftVec.push_back(arr[left + i]);
    }
    for (int j = 0; j < rightSize; j++) {
        rightVec.push_back(arr[mid + 1 + j]);
    }

    while (leftPtr < leftSize && rightPtr < rightSize) {
        if (leftVec[leftPtr].getGenre() <= rightVec[rightPtr].getGenre()) {
            arr[mergedPtr] = leftVec[leftPtr];
            leftPtr++;
        }
        else {
            arr[mergedPtr] = rightVec[rightPtr];
            rightPtr++;
        }
        mergedPtr++;
    }

    while (leftPtr < leftSize) {
        arr[mergedPtr] = leftVec[leftPtr];
        leftPtr++;
        mergedPtr++;
    }

    while (rightPtr < rightSize) {
        arr[mergedPtr] = rightVec[rightPtr];
        rightPtr++;
        mergedPtr++;
    }
}

void Movie::mergeDirectors(std::vector<Movie>& arr, int left, int mid, int right) {
    int leftSize = mid - left + 1;
    int rightSize = right - mid;
    int leftPtr = 0;
    int rightPtr = 0;
    int mergedPtr = left;
    std::vector<Movie> leftVec;
    std::vector<Movie> rightVec;

    for (int i = 0; i < leftSize; i++) {
        leftVec.push_back(arr[left + i]);
    }
    for (int j = 0; j < rightSize; j++) {
        rightVec.push_back(arr[mid + 1 + j]);
    }

    while (leftPtr < leftSize && rightPtr < rightSize) {
        if (leftVec[leftPtr].getDirector() <= rightVec[rightPtr].getDirector()) {
            arr[mergedPtr] = leftVec[leftPtr];
            leftPtr++;
        }
        else {
            arr[mergedPtr] = rightVec[rightPtr];
            rightPtr++;
        }
        mergedPtr++;
    }

    while (leftPtr < leftSize) {
        arr[mergedPtr] = leftVec[leftPtr];
        leftPtr++;
        mergedPtr++;
    }

    while (rightPtr < rightSize) {
        arr[mergedPtr] = rightVec[rightPtr];
        rightPtr++;
        mergedPtr++;
    }
}

void Movie::mergeTitles(std::vector<Movie>& arr, int left, int mid, int right) {
    int leftSize = mid - left + 1;
    int rightSize = right - mid;
    int leftPtr = 0;
    int rightPtr = 0;
    int mergedPtr = left;
    std::vector<Movie> leftVec;
    std::vector<Movie> rightVec;

    for (int i = 0; i < leftSize; i++) {
        leftVec.push_back(arr[left + i]);
    }
    for (int j = 0; j < rightSize; j++) {
        rightVec.push_back(arr[mid + 1 + j]);
    }

    while (leftPtr < leftSize && rightPtr < rightSize) {
        if (leftVec[leftPtr].getTitle() <= rightVec[rightPtr].getTitle()) {
            arr[mergedPtr] = leftVec[leftPtr];
            leftPtr++;
        }
        else {
            arr[mergedPtr] = rightVec[rightPtr];
            rightPtr++;
        }
        mergedPtr++;
    }

    while (leftPtr < leftSize) {
        arr[mergedPtr] = leftVec[leftPtr];
        leftPtr++;
        mergedPtr++;
    }

    while (rightPtr < rightSize) {
        arr[mergedPtr] = rightVec[rightPtr];
        rightPtr++;
        mergedPtr++;
    }
}

void Movie::mergeLength(std::vector<Movie>& arr, int left, int mid, int right) {
    int leftSize = mid - left + 1;
    int rightSize = right - mid;
    int leftPtr = 0;
    int rightPtr = 0;
    int mergedPtr = left;
    std::vector<Movie> leftVec;
    std::vector<Movie> rightVec;

    for (int i = 0; i < leftSize; i++) {
        leftVec.push_back(arr[left + i]);
    }
    for (int j = 0; j < rightSize; j++) {
        rightVec.push_back(arr[mid + 1 + j]);
    }

    while (leftPtr < leftSize && rightPtr < rightSize) {
        if (leftVec[leftPtr].getLength() <= rightVec[rightPtr].getLength()) {
            arr[mergedPtr] = leftVec[leftPtr];
            leftPtr++;
        }
        else {
            arr[mergedPtr] = rightVec[rightPtr];
            rightPtr++;
        }
        mergedPtr++;
    }

    while (leftPtr < leftSize) {
        arr[mergedPtr] = leftVec[leftPtr];
        leftPtr++;
        mergedPtr++;
    }

    while (rightPtr < rightSize) {
        arr[mergedPtr] = rightVec[rightPtr];
        rightPtr++;
        mergedPtr++;
    }
}

void Movie::mergeRatings(std::vector<Movie>& arr, int left, int mid, int right) {
    int leftSize = mid - left + 1;
    int rightSize = right - mid;
    int leftPtr = 0;
    int rightPtr = 0;
    int mergedPtr = left;
    std::vector<Movie> leftVec;
    std::vector<Movie> rightVec;

    for (int i = 0; i < leftSize; i++) {
        leftVec.push_back(arr[left + i]);
    }
    for (int j = 0; j < rightSize; j++) {
        rightVec.push_back(arr[mid + 1 + j]);
    }

    while (leftPtr < leftSize && rightPtr < rightSize) {
        if (leftVec[leftPtr].getRating() <= rightVec[rightPtr].getRating()) {
            arr[mergedPtr] = leftVec[leftPtr];
            leftPtr++;
        }
        else {
            arr[mergedPtr] = rightVec[rightPtr];
            rightPtr++;
        }
        mergedPtr++;
    }

    while (leftPtr < leftSize) {
        arr[mergedPtr] = leftVec[leftPtr];
        leftPtr++;
        mergedPtr++;
    }

    while (rightPtr < rightSize) {
        arr[mergedPtr] = rightVec[rightPtr];
        rightPtr++;
        mergedPtr++;
    }
}

void Movie::mergeNumRatings(std::vector<Movie>& arr, int left, int mid, int right) {
    int leftSize = mid - left + 1;
    int rightSize = right - mid;
    int leftPtr = 0;
    int rightPtr = 0;
    int mergedPtr = left;
    std::vector<Movie> leftVec;
    std::vector<Movie> rightVec;

    for (int i = 0; i < leftSize; i++) {
        leftVec.push_back(arr[left + i]);
    }
    for (int j = 0; j < rightSize; j++) {
        rightVec.push_back(arr[mid + 1 + j]);
    }

    while (leftPtr < leftSize && rightPtr < rightSize) {
        if (leftVec[leftPtr].getNumRatings() <= rightVec[rightPtr].getNumRatings()) {
            arr[mergedPtr] = leftVec[leftPtr];
            leftPtr++;
        }
        else {
            arr[mergedPtr] = rightVec[rightPtr];
            rightPtr++;
        }
        mergedPtr++;
    }

    while (leftPtr < leftSize) {
        arr[mergedPtr] = leftVec[leftPtr];
        leftPtr++;
        mergedPtr++;
    }

    while (rightPtr < rightSize) {
        arr[mergedPtr] = rightVec[rightPtr];
        rightPtr++;
        mergedPtr++;
    }
}

void Movie::mergeYears(std::vector<Movie>& arr, int left, int mid, int right) {
    int leftSize = mid - left + 1;
    int rightSize = right - mid;
    int leftPtr = 0;
    int rightPtr = 0;
    int mergedPtr = left;
    std::vector<Movie> leftVec;
    std::vector<Movie> rightVec;

    for (int i = 0; i < leftSize; i++) {
        leftVec.push_back(arr[left + i]);
    }
    for (int j = 0; j < rightSize; j++) {
        rightVec.push_back(arr[mid + 1 + j]);
    }

    while (leftPtr < leftSize && rightPtr < rightSize) {
        if (leftVec[leftPtr].getYear() <= rightVec[rightPtr].getYear()) {
            arr[mergedPtr] = leftVec[leftPtr];
            leftPtr++;
        }
        else {
            arr[mergedPtr] = rightVec[rightPtr];
            rightPtr++;
        }
        mergedPtr++;
    }

    while (leftPtr < leftSize) {
        arr[mergedPtr] = leftVec[leftPtr];
        leftPtr++;
        mergedPtr++;
    }

    while (rightPtr < rightSize) {
        arr[mergedPtr] = rightVec[rightPtr];
        rightPtr++;
        mergedPtr++;
    }
}

void Movie::mergeSortGenres(std::vector<Movie>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortGenres(arr, left, mid);
        mergeSortGenres(arr, mid + 1, right);
        mergeGenres(arr, left, mid, right);
    }
}

void Movie::mergeSortDirectors(std::vector<Movie>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortDirectors(arr, left, mid);
        mergeSortDirectors(arr, mid + 1, right);
        mergeDirectors(arr, left, mid, right);
    }
}

void Movie::mergeSortTitles(std::vector<Movie>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortTitles(arr, left, mid);
        mergeSortTitles(arr, mid + 1, right);
        mergeTitles(arr, left, mid, right);
    }
}

void Movie::mergeSortLength(std::vector<Movie>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortLength(arr, left, mid);
        mergeSortLength(arr, mid + 1, right);
        mergeLength(arr, left, mid, right);
    }
}

void Movie::mergeSortRatings(std::vector<Movie>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortRatings(arr, left, mid);
        mergeSortRatings(arr, mid + 1, right);
        mergeRatings(arr, left, mid, right);
    }
}

void Movie::mergeSortNumRatings(std::vector<Movie>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortNumRatings(arr, left, mid);
        mergeSortNumRatings(arr, mid + 1, right);
        mergeNumRatings(arr, left, mid, right);
    }
}

void Movie::mergeSortYears(std::vector<Movie>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortYears(arr, left, mid);
        mergeSortYears(arr, mid + 1, right);
        mergeYears(arr, left, mid, right);
    }
}