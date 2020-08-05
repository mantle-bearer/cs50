SELECT round(AVG(rating), 2) AS average FROM ratings
JOIN movies
ON ratings.movie_id = movies.id
WHERE movies.year = 2012;