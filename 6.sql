SELECT round(AVG(rating), 2) AS average FROM ratings
WHERE (SELECT year FROM movies WHERE year = 2012);