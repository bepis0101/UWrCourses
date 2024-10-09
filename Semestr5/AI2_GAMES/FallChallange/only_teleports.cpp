#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <map>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

const int TELEPORT_COST = 5000;
const int POD_UPDATE = 1000;
const int POD_DESTROY = -750;


struct Coords {
    int x;
    int y;
};

vector<int> string_to_numbers(string s) {
    vector<int> res;
    string temp = "";
    for(int j = 0; j < s.size(); j++) {
        if(s[j] == ' ') {
            res.push_back(stoi(temp));
            temp = "";
        } else {
            temp += s[j];
        }
    }
    if(!temp.empty()) res.push_back(stoi(temp));
    return res;
}


class Route {
    int buildingId1;
    int buildingId2;
    int capacity;

public:
    Route(int id1, int id2, int capacity) {
        this->buildingId1 = id1;
        this->buildingId2 = id2;
        this->capacity    = capacity;
    }
};

class Building {
    int moduleType;
    int buildingId;
    int x;
    int y;
public:
    Building(int moduleType, int buildingId, int x, int y) {
        this->moduleType = moduleType;
        this->buildingId = buildingId;
        this->x = x;
        this->y = y;
    }
    int getId() {
        return buildingId;
    }
    int getModuleType() {
        return moduleType;
    }
    friend ostream& operator<<(ostream& os, const Building& b);  
};

ostream& operator<<(ostream& os, const Building& b) {
    os << "Type: " << b.moduleType << ' ' << "ID: " << b.buildingId << '\n';
    return os;
}
class LandingPad : public Building {
    int numOfAstronauts;
    map<int, int> astronautKinds;
public:
    LandingPad(int moduleType, int buildingId, int x, int y, int numOfAstronauts, vector<int> astronauts) : Building(moduleType, buildingId, x, y) {
        this->numOfAstronauts = numOfAstronauts;
        for(int astronaut : astronauts) {
            astronautKinds[astronaut]++;
        }
    }
    map<int, int> getAstronautKinds() {
        return astronautKinds;
    }
};

class LunarModule : public Building {
public:
    LunarModule(int moduleType, int buildingId, int x, int y) : Building(moduleType, buildingId, x, y) {}
};

bool checkIfModuleTypeExists(unordered_map<int, LunarModule*> &idToLunarModules, int type, unordered_set<int> &teleportsOut) {
    for(auto&[id, module] : idToLunarModules) {
        // cerr << *module;
        if(module->getModuleType() == type and teleportsOut.find(module->getId()) == teleportsOut.end()) {
            return true;
        }
    }
    return false;
}
int main()
{
    // game loop
    unordered_map<int, LunarModule*> idToLunarModules;
    unordered_map<int, LandingPad*> idToLandingPad;
    while (1) {
        unordered_map<int, int> teleports;
        unordered_set<int> teleportOut;
        int resources;
        cin >> resources; cin.ignore();
        int num_travel_routes;
        cin >> num_travel_routes; cin.ignore();
        for (int i = 0; i < num_travel_routes; i++) {
            int building_id_1;
            int building_id_2;
            int capacity;
            cin >> building_id_1 >> building_id_2 >> capacity; cin.ignore();
            if(!capacity) {
                teleports[building_id_1] = building_id_2;
                teleportOut.insert(building_id_2);
            }
        }
        int num_pods;
        cin >> num_pods; cin.ignore();
        for (int i = 0; i < num_pods; i++) {
            string pod_properties;
            getline(cin, pod_properties);
        }
        int num_new_buildings;
        cin >> num_new_buildings; cin.ignore();
        for (int i = 0; i < num_new_buildings; i++) {
            string building_properties;
            getline(cin, building_properties);
            vector<int> building_props = string_to_numbers(building_properties);
            vector<int> astronautTypes;
            if(building_props[0] == 0) {
                copy(building_props.begin() + 5, building_props.end(), back_inserter(astronautTypes));
                idToLandingPad[building_props[1]] = new LandingPad(building_props[0], building_props[1], building_props[2], building_props[3], building_props[4], astronautTypes);
            } else {
                idToLunarModules[building_props[1]] = new LunarModule(building_props[0], building_props[1], building_props[2], building_props[3]);
                // cerr << *idToLunarModules[building_properties[1]];
            }
        }
        // for(auto&[id, model] : idToLunarModules) {
        //     cerr << *model;
        // }
        while(resources >= TELEPORT_COST) {
            pair<pair<int, int> , int> maksAstronauts = {{-1, -1}, 0};
            for(auto&[id, pad] : idToLandingPad) {
                auto astronauts = pad->getAstronautKinds();
                for(auto&[astronaut_type, count] : astronauts) {
                    // cerr << "FOR PAD " << pad->getId() << " AND ASTRONAUT TYPE " << astronaut_type << " QUERIES ARE " << (maksAstronauts.second < count) << ' ' << (teleports.find(pad->getId()) == teleports.end()) << ' ' << checkIfModuleTypeExists(idToLunarModules, astronaut_type, teleportOut) << '\n';
                    if(maksAstronauts.second < count and 
                    teleports.find(pad->getId()) == teleports.end() and 
                    checkIfModuleTypeExists(idToLunarModules, astronaut_type, teleportOut)) {  
                        // cerr << "MAKS ASTRONAUT FOUND " << pad->getId() << ' ' << astronaut_type << '\n';
                        maksAstronauts = {{pad->getId(), astronaut_type}, count};
                    }
                }
            }
            int build1id = maksAstronauts.first.first;
            int build2id = 0;
            for(auto&[id, module] : idToLunarModules) {
                if(module->getModuleType() == maksAstronauts.first.second) {
                    build2id = module->getId();
                    break;
                }
            }
            teleports[build1id] = build2id;
            teleportOut.insert(build2id);
            if(build1id > -1) {
                cout << "TELEPORT " << build1id << ' ' << build2id << ';';
            } else {
                break;
            }
        }
        cout << "WAIT\n";

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
    }
}