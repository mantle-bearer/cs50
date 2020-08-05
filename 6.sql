SELECT CAST(AVG(rating) AS DECIMAL (10, 2)) FROM ratings
WHERE (SELECT year FROM movies WHERE year = 2012);