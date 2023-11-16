#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <set>
#include <chrono>
#include "Movie.h"
using namespace std;
using namespace std::chrono;

// storing movie objects from file
void ReadInMovies(vector<Movie>& movies) {
    ifstream file("combined.data.tsv");

    if (file.is_open()) {
        string line;
        while (std::getline(file, line)) {
            istringstream stream(line);
            string title;
            string year;
            string runtime;
            string genres;
            string directors;
            string rating;
            string numRatings;

            getline(stream, title, '\t');
            getline(stream, year, '\t');
            getline(stream, runtime, '\t');
            getline(stream, genres, '\t');
            getline(stream, directors, '\t');
            getline(stream, rating, '\t');
            getline(stream, numRatings, '\t');

            istringstream stream1(genres);
            string genre;
            vector<string> g;
            while (getline(stream1, genre, ',')) {
                g.push_back(genre);
            }

            istringstream stream2(directors);
            string director;
            vector<string> d;
            while (getline(stream2, director, ',')) {
                d.push_back(director);
            }
            // creating movie object and pushing into movies vector
            movies.emplace_back(title, g, d, stoi(year), stoi(runtime), stof(rating), stoi(numRatings));
        }
    }
}

int main() {
    Movie movie;

    // genres for parsing input
    vector<string> allGenres = {"Action", "Adventure", "Animation", "Biography", "Comedy", "Crime", "Documentary",
                                "Drama", "Family", "Fantasy", "Film-Noir", "History", "Horror", "Music", "Musical",
                                "Mystery", "Romance", "Sci-Fi", "Short", "Sport", "Superhero", "Thriller",
                                "War", "Western"};

    // vector to store movies after reading from the file
    vector<Movie> movies;
    ReadInMovies(movies);

    // main menu options
    cout << "* Welcome to Movie Magic! *" << endl;
    cout << "Our goal is to make finding movies suited to your tastes easier." << endl;
    cout << endl;
    cout << "Please enter up to three numbers corresponding to your favorite genres or type in your favorite director." << endl;
    cout << "(Ex. \"1 2 4\" or \"Ryan Coogler\")" << endl;
    cout << endl;
    cout << "1. Action         9.  Family        17. Romance" << endl;
    cout << "2. Adventure      10. Fantasy       18. Sci-Fi" << endl;
    cout << "3. Animation      11. Film Noir     19. Short Film" << endl;
    cout << "4. Biography      12. History       20. Sport" << endl;
    cout << "5. Comedy         13. Horror        21. Superhero" << endl;
    cout << "6. Crime          14. Music         22. Thriller" << endl;
    cout << "7. Documentary    15. Musical       23. War" << endl;
    cout << "8. Drama          16. Mystery       24. Western" << endl;
    cout << "Type 0 to exit." << endl;
    cout << endl;

    // variables
    set<Movie> movieSet;
    Movie* movieArray;
    Movie* movieArray2;
    bool exit = false;

    while (true) {
        string line;
        // taking user input
        getline(cin, line);
        istringstream stream(line);
        // exit if user enters 0
        if (line.at(0) == '0' && line.length() == 1) {
            exit = true;
            break;
        }

        // director entered
        if (movie.validDirectorName(line)) {
            // adding movies with desired director to movieSet
            for (int i = 0; i < movies.size(); i++) {
                vector<string> directors = movies.at(i).getDirector();
                for (int j = 0; j < directors.size(); j++) {
                    if (directors.at(j).compare(line) == 0) {
                        movieSet.insert(movies.at(i));
                    }
                }
            }
            break;
        }
            // movie genre entered
        else if (movie.validGenreInput(line)) {
            string num;
            // looping through each entered number
            while (getline(stream, num, ' ')) {
                // adding movies with desired genres to movieSet
                for (int i = 0; i < movies.size(); i++) {
                    vector<string> genres = movies.at(i).getGenre();
                    for (int j = 0; j < genres.size(); j++) {
                        if (genres.at(j) == allGenres.at(stoi(num) - 1)) {
                            movieSet.insert(movies.at(i));
                        }
                    }
                }

            }
            break;
        }
            // invalid input
        else {
            cout << "Please enter valid input" << endl;
            cout << endl;
        }
    }

    // one array for each sort
    set<Movie> ::iterator iter;
    int count = 0;
    movieArray = new Movie[movieSet.size()];
    for (iter = movieSet.begin(); iter != movieSet.end(); ++iter) {
        movieArray[count] = *iter;
        count++;
    }
    count = 0;
    movieArray2 = new Movie[movieSet.size()];
    for (iter = movieSet.begin(); iter != movieSet.end(); ++iter) {
        movieArray2[count] = *iter;
        count++;
    }

    while (true) {

        if (exit) {
            break;
        }
        // no movies found
        if (movieSet.empty()) {
            cout << "No movies corresponded to your search." << endl;
            break;
        }

        bool another = true;

        while (another) {
            // second menu
            cout << endl;
            cout << "Please enter the criteria you would like to sort the movies on." << endl;
            cout << "Ex. \"1\" or \"2\"" << endl;
            cout << endl;
            cout << "1. Length (from longest)" << endl;
            cout << "2. Length (from shortest)" << endl;
            cout << "3. Rating (from highest)" << endl;
            cout << "4. Rating (from lowest)" << endl;
            cout << "5. Number of Ratings (from highest)" << endl;
            cout << "6. Number of Ratings (from lowest)" << endl;
            cout << "Type 0 to exit." << endl;
            cout << endl;

            another = false;
            string option;
            getline(cin, option);

            // if digit
            if (option.size() == 1 && isdigit(option.at(0))) {
                // length from longest
                if (stoi(option) == 1) {
                    cout << endl;
                    // radix sort
                    auto start = high_resolution_clock::now();
                    movie.radixSortLength(movieArray, movieSet.size());
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<nanoseconds>(stop - start);

                    cout << "Radix Sort (" << duration.count() << " nanoseconds)" << endl;
                    cout << endl;

                    if (movieSet.size() < 100) {
                        int current = 1;
                        for (int i = movieSet.size() - 1; i >= 0; i--) {
                            cout << current << ". ";
                            movieArray[i].print();
                            current++;
                        }
                    }
                    else {
                        int current = 1;
                        for (int i = movieSet.size() - 1; i >= movieSet.size() - 100; i--) {
                            cout << current << ". ";
                            movieArray[i].print();
                            current++;
                        }
                    }
                    cout << endl;

                    // quick sort
                    auto start1 = high_resolution_clock::now();
                    movie.quickSort(movieArray2, 0, movieSet.size() - 1);
                    auto stop1 = high_resolution_clock::now();
                    auto duration1 = duration_cast<nanoseconds>(stop1 - start1);

                    cout << "Quick Sort (" << duration1.count() << " nanoseconds)" << endl;
                    cout << endl;
                    if (movieSet.size() < 100) {
                        int current = 1;
                        for (int i = movieSet.size() - 1; i >= 0; i--) {
                            cout << current << ". ";
                            movieArray2[i].print();
                            current++;
                        }
                    }
                    else {
                        int current = 1;
                        for (int i = movieSet.size() - 1; i >= movieSet.size() - 100; i--) {
                            cout << current << ". ";
                            movieArray2[i].print();
                            current++;
                        }
                    }



                }
                    // length from shortest
                else if (stoi(option) == 2) {
                    cout << endl;
                    // radix sort
                    auto start = high_resolution_clock::now();
                    movie.radixSortLength(movieArray, movieSet.size());
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<nanoseconds>(stop - start);

                    cout << "Radix Sort (" << duration.count() << " nanoseconds)" << endl;
                    cout << endl;
                    if (movieSet.size() < 100) {
                        for (int i = 0; i < movieSet.size(); i++) {
                            cout << i + 1 << ". ";
                            movieArray[i].print();
                        }
                    }
                    else {
                        for (int i = 0; i < 100; i++) {
                            cout << i + 1 << ". ";
                            movieArray[i].print();
                        }
                    }
                    cout << endl;

                    // quick sort

                    auto start1 = high_resolution_clock::now();
                    movie.quickSort(movieArray2, 0, movieSet.size() - 1);
                    auto stop1 = high_resolution_clock::now();
                    auto duration1 = duration_cast<nanoseconds>(stop1 - start1);

                    cout << "Quick Sort (" << duration1.count() << " nanoseconds)" << endl;
                    cout << endl;

                    if (movieSet.size() < 100) {
                        for (int i = 0; i < movieSet.size(); i++) {
                            cout << i + 1 << ". ";
                            movieArray2[i].print();
                        }
                    }
                    else {
                        for (int i = 0; i < 100; i++) {
                            cout << i + 1 << ". ";
                            movieArray2[i].print();
                        }
                    }



                }
                else if (stoi(option) == 3) { // rating from highest
                    cout << endl;
                    // radix sort
                    auto start = high_resolution_clock::now();
                    movie.radixSortRatings(movieArray, movieSet.size());
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<nanoseconds>(stop - start);

                    cout << "Radix Sort (" << duration.count() << " nanoseconds)" << endl;
                    cout << endl;
                    if (movieSet.size() < 100) {
                        int current = 1;
                        for (int i = movieSet.size() - 1; i >= 0; i--) {
                            cout << current << ". ";
                            movieArray[i].print();
                            current++;
                        }
                    }
                    else {
                        int current = 1;
                        for (int i = movieSet.size() - 1; i >= movieSet.size() - 100; i--) {
                            cout << current << ". ";
                            movieArray[i].print();
                            current++;
                        }
                    }
                    cout << endl;

                    // quick sort
                    auto start1 = high_resolution_clock::now();
                    movie.quickSortRatings(movieArray2, 0, movieSet.size() - 1);
                    auto stop1 = high_resolution_clock::now();
                    auto duration1 = duration_cast<nanoseconds>(stop1 - start1);
                    cout << "Quick Sort (" << duration1.count() << " nanoseconds)" << endl;
                    cout << endl;
                    if (movieSet.size() < 100) {
                        int current = 1;
                        for (int i = movieSet.size() - 1; i >= 0; i--) {
                            cout << current << ". ";
                            movieArray2[i].print();
                            current++;
                        }
                    }
                    else {
                        int current = 1;
                        for (int i = movieSet.size() - 1; i >= movieSet.size() - 100; i--) {
                            cout << current << ". ";
                            movieArray2[i].print();
                            current++;
                        }
                    }

                }
                    // rating from lowest
                else if (stoi(option) == 4) {
                    cout << endl;
                    // radix sort
                    auto start = high_resolution_clock::now();
                    movie.radixSortRatings(movieArray, movieSet.size());
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<nanoseconds>(stop - start);

                    cout << "Radix Sort (" << duration.count() << " nanoseconds)" << endl;
                    cout << endl;
                    if (movieSet.size() < 100) {
                        for (int i = 0; i < movieSet.size(); i++) {
                            cout << i + 1 << ". ";
                            movieArray[i].print();
                        }
                    }
                    else {
                        for (int i = 0; i < 100; i++) {
                            cout << i + 1 << ". ";
                            movieArray[i].print();
                        }
                    }
                    cout << endl;

                    // quick sort
                    auto start1 = high_resolution_clock::now();
                    movie.quickSortRatings(movieArray2, 0, movieSet.size() - 1);
                    auto stop1 = high_resolution_clock::now();
                    auto duration1 = duration_cast<nanoseconds>(stop1 - start1);
                    cout << "Quick Sort (" << duration.count() << " nanoseconds)" << endl;
                    cout << endl;
                    if (movieSet.size() < 100) {
                        for (int i = 0; i < movieSet.size(); i++) {
                            cout << i + 1 << ". ";
                            movieArray2[i].print();
                        }
                    }
                    else {
                        for (int i = 0; i < 100; i++) {
                            cout << i + 1 << ". ";
                            movieArray2[i].print();
                        }
                    }


                }
                    // number of ratings from highest
                else if (stoi(option) == 5) {
                    cout << endl;
                    // radix sort
                    auto start = high_resolution_clock::now();
                    movie.radixSortNumRatings(movieArray, movieSet.size());
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<nanoseconds>(stop - start);

                    cout << "Radix Sort (" << duration.count() << " nanoseconds)" << endl;
                    cout << endl;
                    if (movieSet.size() < 100) {
                        int current = 1;
                        for (int i = movieSet.size() - 1; i >= 0; i--) {
                            cout << current << ". ";
                            movieArray[i].print();
                            current++;
                        }
                    }
                    else {
                        int current = 1;
                        for (int i = movieSet.size() - 1; i >= movieSet.size() - 100; i--) {
                            cout << current << ". ";
                            movieArray[i].print();
                            current++;
                        }
                    }
                    cout << endl;

                    // quick sort
                    auto start1 = high_resolution_clock::now();
                    movie.quickSortNumOfRatings(movieArray2, 0, movieSet.size() - 1);
                    auto stop1 = high_resolution_clock::now();
                    auto duration1 = duration_cast<nanoseconds>(stop1 - start1);
                    cout << "Quick Sort (" << duration1.count() << " nanoseconds)" << endl;
                    cout << endl;
                    if (movieSet.size() < 100) {
                        int current = 1;
                        for (int i = movieSet.size() - 1; i >= 0; i--) {
                            cout << current << ". ";
                            movieArray2[i].print();
                            current++;
                        }
                    }
                    else {
                        int current = 1;
                        for (int i = movieSet.size() - 1; i >= movieSet.size() - 100; i--) {
                            cout << current << ". ";
                            movieArray2[i].print();
                            current++;
                        }
                    }

                }
                    // number of ratings from lowest
                else if (stoi(option) == 6) {
                    cout << endl;
                    // radix sort
                    auto start = high_resolution_clock::now();
                    movie.radixSortNumRatings(movieArray, movieSet.size());
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<nanoseconds>(stop - start);

                    cout << "Radix Sort (" << duration.count() << " nanoseconds)" << endl;
                    cout << endl;
                    movie.radixSortNumRatings(movieArray, movieSet.size());
                    if (movieSet.size() < 100) {
                        for (int i = 0; i < movieSet.size(); i++) {
                            cout << i + 1 << ". ";
                            movieArray[i].print();
                        }
                    }
                    else {
                        for (int i = 0; i < 100; i++) {
                            cout << i + 1 << ". ";
                            movieArray[i].print();
                        }
                    }
                    cout << endl;

                    // quick sort
                    auto start1 = high_resolution_clock::now();
                    movie.quickSortNumOfRatings(movieArray2, 0, movieSet.size() - 1);
                    auto stop1 = high_resolution_clock::now();
                    auto duration1 = duration_cast<nanoseconds>(stop1 - start1);
                    cout << "Quick Sort (" << duration.count() << " nanoseconds)" << endl;
                    cout << endl;
                    if (movieSet.size() < 100) {
                        for (int i = 0; i < movieSet.size(); i++) {
                            cout << i + 1 << ". ";
                            movieArray2[i].print();
                        }
                    }
                    else {
                        for (int i = 0; i < 100; i++) {
                            cout << i + 1 << ". ";
                            movieArray2[i].print();
                        }
                    }

                }
                else if (stoi(option) == 0) {
                    exit = true;
                }
                    // digit is not a listed option
                else {
                    cout << "Please enter a valid option." << endl;
                    another = true;
                    continue;
                }
            }
                // input is not a digit
            else {
                cout << "Please enter a valid option." << endl;
                another = true;
                continue;
            }

            if (exit) {
                break;
            }

            cout << endl;
            cout << "Type 1 if you would like to test another option or 0 to exit." << endl;
            cout << endl;
            bool anotherTime = true;

            // loop for choosing different sorting options
            while (anotherTime) {
                getline(cin, option);
                // if input is a digit
                if (!option.empty() && isdigit(option.at(0)) && option.size() == 1) {
                    // 0 -> exit
                    if (stoi(option) == 0) {
                        exit = true;
                        another = false;
                        anotherTime = false;
                        break;
                    }
                        // 1 -> continue looping through second menu
                    else if (stoi(option) == 1) {
                        another = true;
                        anotherTime = false;
                    }
                        // not btwn 0 and 1
                    else {
                        cout << "Please enter a valid option." << endl;
                    }
                }
                    // not a digit
                else if (!option.empty()) {
                    cout << "Please enter a valid option." << endl;
                }
            }
        }
    }
    cout << endl;
    cout << "Thank you for making Movie Magic!" << endl;

    delete[] movieArray;
    delete[] movieArray2;
    return 0;
}