from neo4j import GraphDatabase

URI = 'neo4j+s://2cdc6ae6.databases.neo4j.io'
AUTH = ('neo4j', '4eBbTI1wVRVyhiJ0ilXHcpOoJPNga0PZ300OEGApLQY')

# actor object model class
class Actor:
    def __init__(self, name):
        self.name = name

class DB:
    def __init__(self, uri, auth):
        self.driver = GraphDatabase.driver(uri, auth=auth)
    
    def __enter__(self):
        return self
    
    def __exit__(self, exc_type, exc_value, exc_traceback):
        self.close()

    def close(self):
        self.driver.close()

    def add_actor(self, actor):
        self.driver.execute_query(
            'CREATE (a: ACTOR {name: $name})',
            name=actor.name
        )

    def get_actors(self):
        records, summary, keys = self.driver.execute_query(
            'MATCH (a: ACTOR) RETURN a.name AS name'
        )
        return [Actor(record['name']) for record in records]
    
    def delete_actor(self, actor):
        self.driver.execute_query(
            'MATCH (a: ACTOR {name: $name}) DELETE a',
            name=actor.name
        )
    def update_actor(self, actor, new_name):
        self.driver.execute_query(
            'MATCH (a: ACTOR {name: $name}) SET a.name = $new_name',
            name=actor.name,
            new_name=new_name
        )
    

with DB(URI, AUTH) as driver:
    driver.driver.verify_connectivity()
    # return all people from database
    # add new actor
    driver.add_actor(Actor('John Doe'))
    actors = driver.get_actors()
    for actor in actors:
        print(actor.name)
    # update actor
    driver.update_actor(Actor('John Doe'), 'John Smith')
    # get all actors
    actors = driver.get_actors()
    print('with addition:')
    for actor in actors:
        print(actor.name)
    # delete actor
    driver.delete_actor(Actor('John Smith'))
    actors = driver.get_actors()
    print('with deletion:')
    for actor in actors:
        print(actor.name)
