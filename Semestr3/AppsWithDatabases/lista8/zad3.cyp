//return the movies where person A acted in
MATCH(a:ACTOR {name: "Tom Hanks"})-[:ACTED_IN]->(m:MOVIE)
RETURN m.title

// return the movies where person A was both the actor and the director

CREATE(m:MOVIE {title: "Django Unchained", year: 2012})
CREATE(a:ACTOR {name: "Jamie Foxx"})
CREATE(a)-[:ACTED_IN]->(m)
CREATE(b:ACTOR {name: "Quentin Tarantino"})
CREATE(b)-[:DIRECTED]->(m)
CREATE(b) -[:ACTED_IN]->(m)


MATCH(a:ACTOR {name: "Quentin Tarantino"})-[:ACTED_IN]->(m:MOVIE)<-[:DIRECTED]-(a)
RETURN m.title


CREATE (:ACTOR {name: "Denzel Washington"})
// return actors that didnt play in any movie
MATCH (a:ACTOR)
WHERE NOT (a)-[:ACTED_IN]->(:MOVIE)
RETURN a

CREATE (:ACTOR {name: "Antonio Banderas"})
CREATE (:MOVIE {title: "Philadelphia"})

MATCH (a:ACTOR {name: "Antonio Banderas"}), (m:MOVIE {title: "Philadelphia"})
CREATE (a)-[:ACTED_IN]->(m)

MATCH (a:ACTOR {name: "Denzel Washington"}), (m:MOVIE {title: "Philadelphia"})
CREATE (a)-[:ACTED_IN]->(m)

MATCH (a:ACTOR {name: "Tom Hanks"}), (m:MOVIE {title: "Philadelphia"})
CREATE (a)-[:ACTED_IN]->(m)

// return actors who played in more than 2 movies
MATCH (a:ACTOR)-[:ACTED_IN]->(m:MOVIE)
WITH a, count(m) AS movies
WHERE movies > 2
RETURN a

// return movies with the larger number of actors.
MATCH (a:ACTOR)-[:ACTED_IN]->(m:MOVIE)
WITH m, count(a) AS actors
WHERE actors > 2
RETURN m