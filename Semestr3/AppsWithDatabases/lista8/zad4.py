from neo4j import GraphDatabase

URI = 'neo4j+s://2cdc6ae6.databases.neo4j.io'
AUTH = ('neo4j', '4eBbTI1wVRVyhiJ0ilXHcpOoJPNga0PZ300OEGApLQY')

with GraphDatabase.driver(URI, auth=AUTH) as driver:
    driver.verify_connectivity()
    # return all people from database
    records, summary, keys = driver.execute_query(
        'MATCH (a: ACTOR) RETURN a.name AS name'
    )
    for person in records:
        print(person['name'])
