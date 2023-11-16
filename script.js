function searchMovies() {
    const genre = document.getElementById('genre').value;
    const director = document.getElementById('director').value;
    const yearRange = document.getElementById('yearRange').value;

    // Placeholder for API call
    fetchMovies(genre, director, yearRange);
}

function fetchMovies(genre, director, yearRange) {
    // Replace this with actual API call
    const movies = [
        { title: "Example Movie 1", year: "2000", director: "Director 1" },
        // Add more example movies
    ];

    displayMovies(movies);
}

function displayMovies(movies) {
    const results = document.getElementById('results');
    const movieList = document.getElementById('movieList');
    movieList.innerHTML = '';

    movies.forEach(movie => {
        const li = document.createElement('li');
        li.textContent = `${movie.title} (${movie.year}), Directed by ${movie.director}`;
        movieList.appendChild(li);
    });

    results.style.display = 'block';
}
