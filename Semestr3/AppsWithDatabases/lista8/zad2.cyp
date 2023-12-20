CREATE(th:ACTOR {name: "Tom Hanks"})
CREATE(tc:ACTOR {name: "Tom Cruise"})

CREATE(fg:MOVIE {title: "Forrest Gump"})
CREATE(spr:MOVIE {title: "Saving Private Ryan"})

MATCH (fg:MOVIE {title: "Forrest Gump"})
SET fg.year = 1993,
    fg.oscar = True

// add relationships between actors and movies (acted-in)
MATCH (a:ACTOR {name: "Tom Hanks"}), (m:MOVIE {title: "Forrest Gump"})
CREATE (a)-[:ACTED_IN]->(m)

MATCH (a:ACTOR {name: "Tom Hanks"}), (m:MOVIE {title: "Saving Private Ryan"})
CREATE (a)-[:ACTED_IN]->(m)

// update one movie property

MATCH (m:MOVIE {title: "Forrest Gump"})
SET m.year = 1994

// remove one acted_in realtionship

MATCH (a:ACTOR {name: "Tom Hanks"})-[r:ACTED_IN]->(m:MOVIE {title: "Saving Private Ryan"})
DELETE r
