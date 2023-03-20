//
// Created by Utilizador on 3/9/2023.
//

#ifndef PROJETO_GRAPH_H
#define PROJETO_GRAPH_H

#include <string>
#include <vector>
#include <unordered_map>
#include "Station.h"
#include "Connection.h"

using namespace std;

class Graph {

private:
    unordered_map<string, Station> stations;
    unordered_map<string, vector<Connection>> targets;
    vector<Connection> connections;


public:
    Graph();

    bool loadStations();
    bool loadConnections();

    unordered_map<string, Station> getStations();
    vector<Connection> getConnections();
    unordered_map<string, vector<Connection>> getTargets();
    int maxTrainsBetweenStations(string stationA, string stationB)
};


#endif //PROJETO_GRAPH_H
