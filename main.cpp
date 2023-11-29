#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <set>
#include <chrono>
#include "Movie.h"
using namespace std::chrono;

// Reads data file and stores information
void readFile(std::vector<Movie>& movies) {
    std::ifstream file("data.tsv");

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            // Initialize and get all information for every movie in the .tsv file
            std::istringstream stream(line);
            std::string title;
            std::string year;
            std::string runtime;
            std::string genres;
            std::string directors;
            std::string rating;
            std::string numRatings;

            getline(stream, title, '\t');
            getline(stream, year, '\t');
            getline(stream, runtime, '\t');
            getline(stream, genres, '\t');
            getline(stream, directors, '\t');
            getline(stream, rating, '\t');
            getline(stream, numRatings, '\t');

            std::istringstream stream1(genres);
            std::string genre;
            std::vector<std::string> g;
            // Add genre to genre vector
            while (getline(stream1, genre, ',')) {
                g.push_back(genre);
            }

            std::istringstream stream2(directors);
            std::string director;
            std::vector<std::string> d;
            // Add director to director vector
            while (getline(stream2, director, ',')) {
                d.push_back(director);
            }
            // Add movie to movie vector
            movies.emplace_back(title, g, d, stoi(year), stoi(runtime), stof(rating), stoi(numRatings));
        }
    }
    else {
        std::cout << "Error" << std::endl;
    }
}

int main() {
    Movie movie;

    // Store all genres
    std::vector<std::string> genres = {"Action", "Adventure", "Animation", "Biography", "Comedy", "Crime", "Documentary",
                                "Drama", "Family", "Fantasy", "Film-Noir", "History", "Horror", "Music", "Musical",
                                "Mystery", "Romance", "Sci-Fi", "Short", "Sport", "Superhero", "Thriller",
                                "War", "Western"};
    std::vector<Movie> movies;
    readFile(movies);

    // Created with: https://www.asciiart.eu/text-to-ascii-art
    std::cout << R"(
    /\_/\  /\_/\  /\_/\  /\_/\  /\_/\  /\_/\  /\_/\  /\_/\  /\_/\  /\_/\  /\_/\  /\_/\
   ( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )
    > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <
    /\_/\                                                                        /\_/\
   ( o.o )                                                                      ( o.o )
    > ^ <        __        __   _                            _                   > ^ <
    /\_/\        \ \      / /__| | ___ ___  _ __ ___   ___  | |_ ___             /\_/\
   ( o.o )        \ \ /\ / / _ \ |/ __/ _ \| '_ ` _ \ / _ \ | __/ _ \           ( o.o )
    > ^ <          \ V  V /  __/ | (_| (_) | | | | | |  __/ | || (_) |           > ^ <
    /\_/\       ____\_/\_/ \___|_|\___\___/|_|_|_| |_|\___|_ \__\___/    _       /\_/\
   ( o.o )     | __ )(_)_ __   __ _  ___  | __ ) _   _  __| | __| |_   _| |     ( o.o )
    > ^ <      |  _ \| | '_ \ / _` |/ _ \ |  _ \| | | |/ _` |/ _` | | | | |      > ^ <
    /\_/\      | |_) | | | | | (_| |  __/ | |_) | |_| | (_| | (_| | |_| |_|      /\_/\
   ( o.o )     |____/|_|_| |_|\__, |\___| |____/ \__,_|\__,_|\__,_|\__, (_)     ( o.o )
    > ^ <                     |___/                                |___/         > ^ <
    /\_/\                                                                        /\_/\
   ( o.o )                                                                      ( o.o )
    > ^ <                                                                        > ^ <
    /\_/\  /\_/\  /\_/\  /\_/\  /\_/\  /\_/\  /\_/\  /\_/\  /\_/\  /\_/\  /\_/\  /\_/\
   ( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )
    > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <)" << std::endl;

    // Genre Menu
    std::cout << std::endl;
    std::cout << "Please enter up to three numbers corresponding to these genres, or a director's name." << std::endl;
    std::cout << std::endl;
    std::cout << "1. Action         9.  Family        17. Romance" << std::endl;
    std::cout << "2. Adventure      10. Fantasy       18. Sci-Fi" << std::endl;
    std::cout << "3. Animation      11. Film Noir     19. Short Film" << std::endl;
    std::cout << "4. Biography      12. History       20. Sport" << std::endl;
    std::cout << "5. Comedy         13. Horror        21. Superhero" << std::endl;
    std::cout << "6. Crime          14. Music         22. Thriller" << std::endl;
    std::cout << "7. Documentary    15. Musical       23. War" << std::endl;
    std::cout << "8. Drama          16. Mystery       24. Western" << std::endl;
    std::cout << "Press 0 to exit." << std::endl;
    std::cout << std::endl;

    // Additional data structures
    // Set to store all movie information
    std::set<Movie> movieSet;
    // Dynamically allocated array to use during shell sorts
    Movie* movieArray;
    bool exit = false;

    while (true) {
        std::string line;
        getline(std::cin, line);
        std::istringstream stream(line);
        // Exit
        if (line.at(0) == '0' && line.length() == 1) {
            exit = true;
            break;
        }

        // Validating directors and genres before adding to the movie set
        if (movie.validateDirector(line)) {
            for (const auto & movie : movies) {
                std::vector<std::string> directors = movie.getDirector();
                for (int j = 0; j < directors.size(); j++) {
                    if (directors.at(j) == line) {
                        // Add to set
                        movieSet.insert(movie);
                    }
                }
            }
            break;
        }
        else if (movie.validateGenre(line)) {
            std::string num;
            while (getline(stream, num, ' ')) {
                for (int i = 0; i < movies.size(); i++) {
                    std::vector<std::string> genresA = movies.at(i).getGenre();
                    for (int j = 0; j < genresA.size(); j++) {
                        if (genresA.at(j) == genres.at(stoi(num) - 1)) {
                            // Add to set
                            movieSet.insert(movies.at(i));
                        }
                    }
                }

            }
            break;
        }
        else {
            std::cout << "Invalid Input." << std::endl;
            std::cout << std::endl;
        }
    }

    // Set iteration
    std::set<Movie> ::iterator iter;
    int count = 0;
    movieArray = new Movie[movieSet.size()];
    for (iter = movieSet.begin(); iter != movieSet.end(); ++iter) {
        movieArray[count] = *iter;
        count++;
    }
    // Movie vector for merge sorts
    std::vector<Movie> movieVector;
    count = 0;
    for (iter = movieSet.begin(); iter != movieSet.end(); ++iter) {
        movieVector.push_back(*iter);
        count++;
    }

    while (true) {

        if (exit) {
            break;
        }

        // If there are no movies fitting the criteria
        if (movieSet.empty()) {
            std::cout << "No movies available." << std::endl;
            break;
        }

        bool again = true;

        while (again) {
            // Action Menu
            std::cout << std::endl;
            std::cout << "How would you like to sort your movies?." << std::endl;
            std::cout << std::endl;
            std::cout << "1. Length (from longest)" << std::endl;
            std::cout << "2. Length (from shortest)" << std::endl;
            std::cout << "3. Rating (from highest)" << std::endl;
            std::cout << "4. Rating (from lowest)" << std::endl;
            std::cout << "5. Number of Ratings (from highest)" << std::endl;
            std::cout << "6. Number of Ratings (from lowest)" << std::endl;
            std::cout << "7. Year (from latest)" << std::endl;
            std::cout << "8. Year (from oldest)" << std::endl;
            std::cout << "9. Title (ascending)" << std::endl;
            std::cout << "10. Title (descending)" << std::endl;
            std::cout << "11. Director (ascending)" << std::endl;
            std::cout << "12. Director (descending)" << std::endl;
            std::cout << "13. Genre (ascending)" << std::endl;
            std::cout << "14. Genre (descending)" << std::endl;
            std::cout << "Type 0 to exit." << std::endl;
            std::cout << std::endl;

            again = false;
            std::string option;
            getline(std::cin, option);

            // Valid option choice
            if ((option.size() == 1  || option.size() == 2) && isdigit(option.at(0))) {
                // Length from longest to shortest
                if (stoi(option) == 1) {
                    std::cout << std::endl;

                    // Start timer for merge sort
                    auto start = high_resolution_clock::now();
                    movie.mergeSortLength(movieVector, 0, movieSet.size() - 1);
                    // End timer for merge sort
                    auto stop = high_resolution_clock::now();
                    // Calculate time for merge sort in nanoseconds
                    auto duration = duration_cast<nanoseconds>(stop - start);
                    // Output the results
                    std::cout << "Merge Sort (" << duration.count() << " nanoseconds)" << std::endl;
                    std::cout << std::endl;

                    // If there are less than 100 movies available
                    if (movieSet.size() < 100) {
                        int current = 1;
                        for (int i = movieSet.size() - 1; i >= 0; i--) {
                            std::cout << current << ". ";
                            movieVector[i].print();
                            current++;
                        }
                    }
                    else {
                        int current = 1;
                        for (int i = movieSet.size() - 1; i >= movieSet.size() - 100; i--) {
                            std::cout << current << ". ";
                            movieVector[i].print();
                            current++;
                        }
                    }
                    std::cout << std::endl;

                    // Start timer for shell sort
                    auto start1 = high_resolution_clock::now();
                    Movie::shellSort<Movie>(movieArray, movieSet.size(), Movie::compareByLength);
                    // End timer for shell sort
                    auto stop1 = high_resolution_clock::now();
                    // Calculate time for shell sort in nanoseconds
                    auto duration1 = duration_cast<nanoseconds>(stop1 - start1);
                    // Output the results
                    std::cout << "Shell Sort (" << duration1.count() << " nanoseconds)" << std::endl;
                    std::cout << std::endl;

                    // If there are less than 100 movies available
                    if (movieSet.size() < 100) {
                        for (int i = 0; i < movieSet.size(); i++) {
                            std::cout << i + 1 << ". ";
                            movieArray[i].print();
                        }
                    }
                    else {
                        for (int i = 0; i < 100; i++) {
                            std::cout << i + 1 << ". ";
                            movieArray[i].print();
                        }
                    }
                }

                // Length from shortest to longest
                else if (stoi(option) == 2) {
                    std::cout << std::endl;

                    auto start = high_resolution_clock::now();
                    movie.mergeSortLength(movieVector, 0, movieSet.size() - 1);
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<nanoseconds>(stop - start);
                    std::cout << "Merge Sort (" << duration.count() << " nanoseconds)" << std::endl;
                    std::cout << std::endl;

                    if (movieSet.size() < 100) {
                        for (int i = 0; i < movieSet.size(); i++) {
                            std::cout << i + 1 << ". ";
                            movieVector[i].print();
                        }
                    }
                    else {
                        for (int i = 0; i < 100; i++) {
                            std::cout << i + 1 << ". ";
                            movieVector[i].print();
                        }
                    }
                    std::cout << std::endl;

                    auto start1 = high_resolution_clock::now();
                    Movie::shellSort<Movie>(movieArray, movieSet.size(), Movie::compareByLength);
                    auto stop1 = high_resolution_clock::now();
                    auto duration1 = duration_cast<nanoseconds>(stop1 - start1);

                    std::cout << "Shell Sort (" << duration1.count() << " nanoseconds)" << std::endl;
                    std::cout << std::endl;

                    if (movieSet.size() < 100) {
                        int current = 1;
                        for (int i = movieSet.size() - 1; i >= 0; i--) {
                            std::cout << current << ". ";
                            movieArray[i].print();
                            current++;
                        }
                    }
                    else {
                        int current = 1;
                        for (int i = movieSet.size() - 1; i >= movieSet.size() - 100; i--) {
                            std::cout << current << ". ";
                            movieArray[i].print();
                            current++;
                        }
                    }
                    std::cout << std::endl;
                }

                // Rating from highest to lowest
                else if (stoi(option) == 3) {
                    std::cout << std::endl;

                    auto start = high_resolution_clock::now();
                    movie.mergeSortRatings(movieVector, 0, movieSet.size() - 1);
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<nanoseconds>(stop - start);
                    std::cout << "Merge Sort (" << duration.count() << " nanoseconds)" << std::endl;
                    std::cout << std::endl;

                    if (movieSet.size() < 100) {
                        int current = 1;
                        for (int i = movieSet.size() - 1; i >= 0; i--) {
                            std::cout << current << ". ";
                            movieVector[i].print();
                            current++;
                        }
                    }
                    else {
                        int current = 1;
                        for (int i = movieSet.size() - 1; i >= movieSet.size() - 100; i--) {
                            std::cout << current << ". ";
                            movieVector[i].print();
                            current++;
                        }
                    }
                    std::cout << std::endl;

                    auto start1 = high_resolution_clock::now();
                    Movie::shellSort<Movie>(movieArray, movieSet.size(), Movie::compareByRating);
                    auto stop1 = high_resolution_clock::now();
                    auto duration1 = duration_cast<nanoseconds>(stop1 - start1);

                    std::cout << "Shell Sort (" << duration1.count() << " nanoseconds)" << std::endl;
                    std::cout << std::endl;

                    if (movieSet.size() < 100) {
                        for (int i = 0; i < movieSet.size(); i++) {
                            std::cout << i + 1 << ". ";
                            movieArray[i].print();
                        }
                    }
                    else {
                        for (int i = 0; i < 100; i++) {
                            std::cout << i + 1 << ". ";
                            movieArray[i].print();
                        }
                    }
                }

                // Rating from lowest to highest
                else if (stoi(option) == 4) {
                    std::cout << std::endl;

                    auto start = high_resolution_clock::now();
                    movie.mergeSortRatings(movieVector, 0, movieSet.size() - 1);
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<nanoseconds>(stop - start);
                    std::cout << "Merge Sort (" << duration.count() << " nanoseconds)" << std::endl;
                    std::cout << std::endl;

                    if (movieSet.size() < 100) {
                        for (int i = 0; i < movieSet.size(); i++) {
                            std::cout << i + 1 << ". ";
                            movieVector[i].print();
                        }
                    }
                    else {
                        for (int i = 0; i < 100; i++) {
                            std::cout << i + 1 << ". ";
                            movieVector[i].print();
                        }
                    }
                    std::cout << std::endl;

                    auto start1 = high_resolution_clock::now();
                    Movie::shellSort<Movie>(movieArray, movieSet.size(), Movie::compareByRating);
                    auto stop1 = high_resolution_clock::now();
                    auto duration1 = duration_cast<nanoseconds>(stop1 - start1);

                    std::cout << "Shell Sort (" << duration1.count() << " nanoseconds)" << std::endl;
                    std::cout << std::endl;

                    if (movieSet.size() < 100) {
                        int current = 1;
                        for (int i = movieSet.size() - 1; i >= 0; i--) {
                            std::cout << current << ". ";
                            movieArray[i].print();
                            current++;
                        }
                    }
                    else {
                        int current = 1;
                        for (int i = movieSet.size() - 1; i >= movieSet.size() - 100; i--) {
                            std::cout << current << ". ";
                            movieArray[i].print();
                            current++;
                        }
                    }
                    std::cout << std::endl;
                }

                // Number of ratings from highest to lowest
                else if (stoi(option) == 5) {
                    std::cout << std::endl;

                    auto start = high_resolution_clock::now();
                    movie.mergeSortNumRatings(movieVector, 0, movieSet.size() - 1);
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<nanoseconds>(stop - start);
                    std::cout << "Merge Sort (" << duration.count() << " nanoseconds)" << std::endl;
                    std::cout << std::endl;

                    if (movieSet.size() < 100) {
                        int current = 1;
                        for (int i = movieSet.size() - 1; i >= 0; i--) {
                            std::cout << current << ". ";
                            movieVector[i].print();
                            current++;
                        }
                    }
                    else {
                        int current = 1;
                        for (int i = movieSet.size() - 1; i >= movieSet.size() - 100; i--) {
                            std::cout << current << ". ";
                            movieVector[i].print();
                            current++;
                        }
                    }
                    std::cout << std::endl;

                    auto start1 = high_resolution_clock::now();
                    Movie::shellSort<Movie>(movieArray, movieSet.size(), Movie::compareByNumRatings);
                    auto stop1 = high_resolution_clock::now();
                    auto duration1 = duration_cast<nanoseconds>(stop1 - start1);

                    std::cout << "Shell Sort (" << duration1.count() << " nanoseconds)" << std::endl;
                    std::cout << std::endl;

                    if (movieSet.size() < 100) {
                        for (int i = 0; i < movieSet.size(); i++) {
                            std::cout << i + 1 << ". ";
                            movieArray[i].print();
                        }
                    }
                    else {
                        for (int i = 0; i < 100; i++) {
                            std::cout << i + 1 << ". ";
                            movieArray[i].print();
                        }
                    }
                }

                // Number of ratings from lowest to highest
                else if (stoi(option) == 6) {
                    std::cout << std::endl;

                    auto start = high_resolution_clock::now();
                    movie.mergeSortNumRatings(movieVector, 0, movieSet.size() - 1);
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<nanoseconds>(stop - start);
                    std::cout << "Merge Sort (" << duration.count() << " nanoseconds)" << std::endl;
                    std::cout << std::endl;

                    if (movieSet.size() < 100) {
                        for (int i = 0; i < movieSet.size(); i++) {
                            std::cout << i + 1 << ". ";
                            movieVector[i].print();
                        }
                    }
                    else {
                        for (int i = 0; i < 100; i++) {
                            std::cout << i + 1 << ". ";
                            movieVector[i].print();
                        }
                    }
                    std::cout << std::endl;

                    auto start1 = high_resolution_clock::now();
                    Movie::shellSort<Movie>(movieArray, movieSet.size(), Movie::compareByNumRatings);
                    auto stop1 = high_resolution_clock::now();
                    auto duration1 = duration_cast<nanoseconds>(stop1 - start1);

                    std::cout << "Shell Sort (" << duration1.count() << " nanoseconds)" << std::endl;
                    std::cout << std::endl;

                    if (movieSet.size() < 100) {
                        int current = 1;
                        for (int i = movieSet.size() - 1; i >= 0; i--) {
                            std::cout << current << ". ";
                            movieArray[i].print();
                            current++;
                        }
                    }
                    else {
                        int current = 1;
                        for (int i = movieSet.size() - 1; i >= movieSet.size() - 100; i--) {
                            std::cout << current << ". ";
                            movieArray[i].print();
                            current++;
                        }
                    }
                    std::cout << std::endl;
                }

                // Year from latest to oldest
                else if (stoi(option) == 7) {
                    std::cout << std::endl;

                    auto start = high_resolution_clock::now();
                    movie.mergeSortYears(movieVector, 0, movieSet.size() - 1);
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<nanoseconds>(stop - start);
                    std::cout << "Merge Sort (" << duration.count() << " nanoseconds)" << std::endl;
                    std::cout << std::endl;

                    if (movieSet.size() < 100) {
                        int current = 1;
                        for (int i = movieSet.size() - 1; i >= 0; i--) {
                            std::cout << current << ". ";
                            movieVector[i].print();
                            current++;
                        }
                    }
                    else {
                        int current = 1;
                        for (int i = movieSet.size() - 1; i >= movieSet.size() - 100; i--) {
                            std::cout << current << ". ";
                            movieVector[i].print();
                            current++;
                        }
                    }
                    std::cout << std::endl;

                    auto start1 = high_resolution_clock::now();
                    Movie::shellSort<Movie>(movieArray, movieSet.size(), Movie::compareByYear);
                    auto stop1 = high_resolution_clock::now();
                    auto duration1 = duration_cast<nanoseconds>(stop1 - start1);

                    std::cout << "Shell Sort (" << duration1.count() << " nanoseconds)" << std::endl;
                    std::cout << std::endl;

                    if (movieSet.size() < 100) {
                        for (int i = 0; i < movieSet.size(); i++) {
                            std::cout << i + 1 << ". ";
                            movieArray[i].print();
                        }
                    }
                    else {
                        for (int i = 0; i < 100; i++) {
                            std::cout << i + 1 << ". ";
                            movieArray[i].print();
                        }
                    }
                    std::cout << std::endl;
                }

                // Year from oldest to latest
                else if (stoi(option) == 8) {
                    std::cout << std::endl;

                    auto start = high_resolution_clock::now();
                    movie.mergeSortYears(movieVector, 0, movieSet.size() - 1);
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<nanoseconds>(stop - start);
                    std::cout << "Merge Sort (" << duration.count() << " nanoseconds)" << std::endl;
                    std::cout << std::endl;
                    if (movieSet.size() < 100) {
                        for (int i = 0; i < movieSet.size(); i++) {
                            std::cout << i + 1 << ". ";
                            movieVector[i].print();
                        }
                    }
                    else {
                        for (int i = 0; i < 100; i++) {
                            std::cout << i + 1 << ". ";
                            movieVector[i].print();
                        }
                    }
                    std::cout << std::endl;

                    auto start1 = high_resolution_clock::now();
                    Movie::shellSort<Movie>(movieArray, movieSet.size(), Movie::compareByYear);
                    auto stop1 = high_resolution_clock::now();
                    auto duration1 = duration_cast<nanoseconds>(stop1 - start1);

                    std::cout << "Shell Sort (" << duration1.count() << " nanoseconds)" << std::endl;
                    std::cout << std::endl;

                    if (movieSet.size() < 100) {
                        int current = 1;
                        for (int i = movieSet.size() - 1; i >= 0; i--) {
                            std::cout << current << ". ";
                            movieArray[i].print();
                            current++;
                        }
                    }
                    else {
                        int current = 1;
                        for (int i = movieSet.size() - 1; i >= movieSet.size() - 100; i--) {
                            std::cout << current << ". ";
                            movieArray[i].print();
                            current++;
                        }
                    }
                    std::cout << std::endl;
                }

                // Titles in ascending order
                else if (stoi(option) == 9) {
                    std::cout << std::endl;

                    auto start = high_resolution_clock::now();
                    movie.mergeSortTitles(movieVector, 0, movieSet.size() - 1);
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<nanoseconds>(stop - start);
                    std::cout << "Merge Sort (" << duration.count() << " nanoseconds)" << std::endl;
                    std::cout << std::endl;

                    if (movieSet.size() < 100) {
                        for (int i = 0; i < movieSet.size(); i++) {
                            std::cout << i + 1 << ". ";
                            movieVector[i].print();
                        }
                    }
                    else {
                        for (int i = 0; i < 100; i++) {
                            std::cout << i + 1 << ". ";
                            movieVector[i].print();
                        }
                    }
                    std::cout << std::endl;

                    auto start1 = high_resolution_clock::now();
                    Movie::shellSort<Movie>(movieArray, movieSet.size(), Movie::compareByTitle);
                    auto stop1 = high_resolution_clock::now();
                    auto duration1 = duration_cast<nanoseconds>(stop1 - start1);

                    std::cout << "Shell Sort (" << duration1.count() << " nanoseconds)" << std::endl;
                    std::cout << std::endl;

                    if (movieSet.size() < 100) {
                        int current = 1;
                        for (int i = movieSet.size() - 1; i >= 0; i--) {
                            std::cout << current << ". ";
                            movieArray[i].print();
                            current++;
                        }
                    }
                    else {
                        int current = 1;
                        for (int i = movieSet.size() - 1; i >= movieSet.size() - 100; i--) {
                            std::cout << current << ". ";
                            movieArray[i].print();
                            current++;
                        }
                    }
                    std::cout << std::endl;
                }

                // Titles in descending order
                else if (stoi(option) == 10) {
                    std::cout << std::endl;

                    auto start = high_resolution_clock::now();
                    movie.mergeSortTitles(movieVector, 0, movieSet.size() - 1);
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<nanoseconds>(stop - start);
                    std::cout << "Merge Sort (" << duration.count() << " nanoseconds)" << std::endl;
                    std::cout << std::endl;

                    if (movieSet.size() < 100) {
                        int current = 1;
                        for (int i = movieSet.size() - 1; i >= 0; i--) {
                            std::cout << current << ". ";
                            movieVector[i].print();
                            current++;
                        }
                    }
                    else {
                        int current = 1;
                        for (int i = movieSet.size() - 1; i >= movieSet.size() - 100; i--) {
                            std::cout << current << ". ";
                            movieVector[i].print();
                            current++;
                        }
                    }
                    std::cout << std::endl;

                    auto start1 = high_resolution_clock::now();
                    Movie::shellSort<Movie>(movieArray, movieSet.size(), Movie::compareByTitle);
                    auto stop1 = high_resolution_clock::now();
                    auto duration1 = duration_cast<nanoseconds>(stop1 - start1);

                    std::cout << "Shell Sort (" << duration1.count() << " nanoseconds)" << std::endl;
                    std::cout << std::endl;

                    if (movieSet.size() < 100) {
                        for (int i = 0; i < movieSet.size(); i++) {
                            std::cout << i + 1 << ". ";
                            movieArray[i].print();
                        }
                    }
                    else {
                        for (int i = 0; i < 100; i++) {
                            std::cout << i + 1 << ". ";
                            movieArray[i].print();
                        }
                    }
                    std::cout << std::endl;
                }

                // Directors in ascending order
                else if (stoi(option) == 11) {
                    std::cout << std::endl;

                    auto start = high_resolution_clock::now();
                    movie.mergeSortDirectors(movieVector, 0, movieSet.size() - 1);
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<nanoseconds>(stop - start);
                    std::cout << "Merge Sort (" << duration.count() << " nanoseconds)" << std::endl;
                    std::cout << std::endl;

                    if (movieSet.size() < 100) {
                        for (int i = 0; i < movieSet.size(); i++) {
                            std::cout << i + 1 << ". ";
                            movieVector[i].print();
                        }
                    }
                    else {
                        for (int i = 0; i < 100; i++) {
                            std::cout << i + 1 << ". ";
                            movieVector[i].print();
                        }
                    }
                    std::cout << std::endl;

                    auto start1 = high_resolution_clock::now();
                    Movie::shellSort<Movie>(movieArray, movieSet.size(), Movie::compareByDirector);
                    auto stop1 = high_resolution_clock::now();
                    auto duration1 = duration_cast<nanoseconds>(stop1 - start1);

                    std::cout << "Shell Sort (" << duration1.count() << " nanoseconds)" << std::endl;
                    std::cout << std::endl;

                    if (movieSet.size() < 100) {
                        int current = 1;
                        for (int i = movieSet.size() - 1; i >= 0; i--) {
                            std::cout << current << ". ";
                            movieArray[i].print();
                            current++;
                        }
                    }
                    else {
                        int current = 1;
                        for (int i = movieSet.size() - 1; i >= movieSet.size() - 100; i--) {
                            std::cout << current << ". ";
                            movieArray[i].print();
                            current++;
                        }
                    }
                    std::cout << std::endl;
                }

                // Directors in descending order
                else if (stoi(option) == 12) {
                    std::cout << std::endl;

                    auto start = high_resolution_clock::now();
                    movie.mergeSortDirectors(movieVector, 0, movieSet.size() - 1);
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<nanoseconds>(stop - start);
                    std::cout << "Merge Sort (" << duration.count() << " nanoseconds)" << std::endl;
                    std::cout << std::endl;

                    if (movieSet.size() < 100) {
                        int current = 1;
                        for (int i = movieSet.size() - 1; i >= 0; i--) {
                            std::cout << current << ". ";
                            movieVector[i].print();
                            current++;
                        }
                    }
                    else {
                        int current = 1;
                        for (int i = movieSet.size() - 1; i >= movieSet.size() - 100; i--) {
                            std::cout << current << ". ";
                            movieVector[i].print();
                            current++;
                        }
                    }
                    std::cout << std::endl;

                    auto start1 = high_resolution_clock::now();
                    Movie::shellSort<Movie>(movieArray, movieSet.size(), Movie::compareByDirector);
                    auto stop1 = high_resolution_clock::now();
                    auto duration1 = duration_cast<nanoseconds>(stop1 - start1);

                    std::cout << "Shell Sort (" << duration1.count() << " nanoseconds)" << std::endl;
                    std::cout << std::endl;

                    if (movieSet.size() < 100) {
                        for (int i = 0; i < movieSet.size(); i++) {
                            std::cout << i + 1 << ". ";
                            movieArray[i].print();
                        }
                    }
                    else {
                        for (int i = 0; i < 100; i++) {
                            std::cout << i + 1 << ". ";
                            movieArray[i].print();
                        }
                    }
                    std::cout << std::endl;
                }

                // Genres in ascending order
                else if (stoi(option) == 13) {
                    std::cout << std::endl;

                    auto start = high_resolution_clock::now();
                    movie.mergeSortGenres(movieVector, 0, movieSet.size() - 1);
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<nanoseconds>(stop - start);
                    std::cout << "Merge Sort (" << duration.count() << " nanoseconds)" << std::endl;
                    std::cout << std::endl;

                    if (movieSet.size() < 100) {
                        for (int i = 0; i < movieSet.size(); i++) {
                            std::cout << i + 1 << ". ";
                            movieVector[i].print();
                        }
                    }
                    else {
                        for (int i = 0; i < 100; i++) {
                            std::cout << i + 1 << ". ";
                            movieVector[i].print();
                        }
                    }
                    std::cout << std::endl;

                    auto start1 = high_resolution_clock::now();
                    Movie::shellSort<Movie>(movieArray, movieSet.size(), Movie::compareByGenre);
                    auto stop1 = high_resolution_clock::now();
                    auto duration1 = duration_cast<nanoseconds>(stop1 - start1);

                    std::cout << "Shell Sort (" << duration1.count() << " nanoseconds)" << std::endl;
                    std::cout << std::endl;

                    if (movieSet.size() < 100) {
                        int current = 1;
                        for (int i = movieSet.size() - 1; i >= 0; i--) {
                            std::cout << current << ". ";
                            movieArray[i].print();
                            current++;
                        }
                    }
                    else {
                        int current = 1;
                        for (int i = movieSet.size() - 1; i >= movieSet.size() - 100; i--) {
                            std::cout << current << ". ";
                            movieArray[i].print();
                            current++;
                        }
                    }
                    std::cout << std::endl;
                }

                // Genres in descending order
                else if (stoi(option) == 14) {
                    std::cout << std::endl;

                    auto start = high_resolution_clock::now();
                    movie.mergeSortGenres(movieVector, 0, movieSet.size() - 1);
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<nanoseconds>(stop - start);
                    std::cout << "Merge Sort (" << duration.count() << " nanoseconds)" << std::endl;
                    std::cout << std::endl;

                    if (movieSet.size() < 100) {
                        int current = 1;
                        for (int i = movieSet.size() - 1; i >= 0; i--) {
                            std::cout << current << ". ";
                            movieVector[i].print();
                            current++;
                        }
                    }
                    else {
                        int current = 1;
                        for (int i = movieSet.size() - 1; i >= movieSet.size() - 100; i--) {
                            std::cout << current << ". ";
                            movieVector[i].print();
                            current++;
                        }
                    }
                    std::cout << std::endl;

                    auto start1 = high_resolution_clock::now();
                    Movie::shellSort<Movie>(movieArray, movieSet.size(), Movie::compareByGenre);
                    auto stop1 = high_resolution_clock::now();
                    auto duration1 = duration_cast<nanoseconds>(stop1 - start1);

                    std::cout << "Shell Sort (" << duration1.count() << " nanoseconds)" << std::endl;
                    std::cout << std::endl;

                    if (movieSet.size() < 100) {
                        for (int i = 0; i < movieSet.size(); i++) {
                            std::cout << i + 1 << ". ";
                            movieArray[i].print();
                        }
                    }
                    else {
                        for (int i = 0; i < 100; i++) {
                            std::cout << i + 1 << ". ";
                            movieArray[i].print();
                        }
                    }
                    std::cout << std::endl;
                }
                // If the user decides to exit
                else if (stoi(option) == 0) {
                    exit = true;
                }
                // Digit is not there
                else {
                    std::cout << "Invalid Input." << std::endl;
                    again = true;
                    continue;
                }
            }
            // Invalid (not int)
            else {
                std::cout << "Invalid Input." << std::endl;
                again = true;
                continue;
            }

            if (exit) {
                break;
            }

            // Ask the user what they want to do next
            std::cout << std::endl;
            std::cout << "Press 1 to go again." << std::endl;
            std::cout << "Press 0 to exit." << std::endl;
            std::cout << std::endl;
            bool againAgain = true;

            // User input
            while (againAgain) {
                getline(std::cin, option);
                if (!option.empty() && isdigit(option.at(0)) && option.size() == 1) {
                    // User wants to exit
                    if (stoi(option) == 0) {
                        exit = true;
                        again = false;
                        againAgain = false;
                        break;
                    }
                    // User wants to continue
                    else if (stoi(option) == 1) {
                        again = true;
                        againAgain = false;
                    }
                    else {
                        std::cout << "Invalid Input." << std::endl;
                    }
                }
                else if (!option.empty()) {
                    std::cout << "Invalid Input." << std::endl;
                }
            }
        }
    }

    // Created with: https://www.asciiart.eu/text-to-ascii-art
    std::cout << R"(
    /\_/\  /\_/\  /\_/\  /\_/\  /\_/\  /\_/\  /\_/\  /\_/\  /\_/\  /\_/\
   ( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )
    > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <
    /\_/\                                                          /\_/\
   ( o.o )                                                        ( o.o )
    > ^ <           ____                                           > ^ <
    /\_/\          / ___|  ___  ___   _   _  ___  _   _            /\_/\
   ( o.o )         \___ \ / _ \/ _ \ | | | |/ _ \| | | |          ( o.o )
    > ^ <           ___) |  __/  __/ | |_| | (_) | |_| |           > ^ <
    /\_/\          |____/ \___|\___|  \__, |\___/ \__,_|           /\_/\
   ( o.o )                            |___/                       ( o.o )
    > ^ <                       _     _   _                _       > ^ <
    /\_/\       _ __   _____  _| |_  | |_(_)_ __ ___   ___| |      /\_/\
   ( o.o )     | '_ \ / _ \ \/ / __| | __| | '_ ` _ \ / _ \ |     ( o.o )
    > ^ <      | | | |  __/>  <| |_  | |_| | | | | | |  __/_|      > ^ <
    /\_/\      |_| |_|\___/_/\_\\__|  \__|_|_| |_| |_|\___(_)      /\_/\
   ( o.o )                                                        ( o.o )
    > ^ <                                                          > ^ <
    /\_/\  /\_/\  /\_/\  /\_/\  /\_/\  /\_/\  /\_/\  /\_/\  /\_/\  /\_/\
   ( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )
    > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <)" << std::endl;

    // Delete dynamically allocated movie array
    delete[] movieArray;
    return 0;
}