//
// Created by Utilizador on 3/9/2023.
//

#ifndef PROJETO_GRAPH_H
#define PROJETO_GRAPH_H

#include <string>
#include <vector>
#include <unordered_map>
#include <limits>
#include <queue>
#include "Station.h"
#include "Connection.h"

using namespace std;

class Graph {

private:
    unordered_map<string, Station> stations;
    unordered_map<string, vector<Connection>> targets;
    vector<Connection> connections;
    unordered_map<string, unordered_map<string, int>> adjacencyMatrix; // Add an adjacency matrix




public:
    Graph();

    bool loadStations();
    bool loadConnections();

    unordered_map<string, Station> getStations();
    vector<Connection> getConnections();
    unordered_map<string, vector<Connection>> getTargets();
    void updateAdjacencyMatrix();
    vector<Station> bfs(Station start, Station end);
    void dfsHelper(Station current, unordered_map<string, bool>& visited, vector<Station>& path);
    vector<Station> dfs(Station start, Station end);
    int maxTrainsBetweenStations(const string source, const string destination);


};


#endif //PROJETO_GRAPH_H
