SELECT name AS [Stars Name]FROM people
WHERE people.id 
IN (SELECT person_id FROM stars 
	JOIN movies 
	ON stars.movie_id = (SELECT movies.id FROM movies WHERE movies.title = "Toy Story")
    WHERE  movies.id = stars.movie_id);