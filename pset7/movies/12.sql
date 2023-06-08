SELECT title
FROM stars
JOIN movies
ON stars.movie_id = movies.id
JOIN people
ON stars.person_id = people.id
WHERE name = "Johnny Depp"
AND title
IN(
    SELECT title
    FROM stars
    JOIN movies
    ON stars.movie_id = movies.id
    JOIN people
    ON stars.person_id = people.id
    WHERE name = "Helena Bonham Carter"
);
