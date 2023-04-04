//
// Created by Utilizador on 3/9/2023.
//

#ifndef PROJETO_GRAPH_H
#define PROJETO_GRAPH_H

#include <string>
#include <vector>
#include <unordered_map>
#include <limits>
#include <unordered_set>
#include <queue>
#include "Station.h"
#include "Connection.h"

using namespace std;

class Graph {

private:
    unordered_map<string, Station> stations;
    unordered_map<string, vector<Connection>> targets;
    vector<Connection> connections;
    unordered_map<string, string> parent;
    unordered_map<string, vector<pair<string, int>>> residual; // Add an adjacency matrix

public:
    Graph();

    bool loadStations();

    bool loadConnections();

    unordered_map<string, Station> getStations();

    vector<Connection> getConnections();

    unordered_map<string, vector<Connection>> getTargets();

    bool bfs(string source, string destination);

    bool dfsHelper(const string &source, const string &destination, unordered_map<string, bool> &visited);

    bool dfs(string source, string destination);

    bool dijkstra(string source, string destination);

    int findAugmentingPath(const string &source, const string &sink, int flow, unordered_map<string, bool> &visited);

    int calculateMaxFlow(string source, string sink);

    vector<pair<string, string>> highestMaxFlowPairsPath(string source, string sink);

    int maxTrainsAtStation(string stationName);

    vector<string> findSourceStations();

    vector<pair<string, string>> highestMaxFlowPairs();

    void updateResidualConnections();

    pair<int, int> calculateMinCostMaxFlow(string source, string sink);

    //pair<int, int> calculateMinCostMaxFlow(string source, string sink);


};


#endif //PROJETO_GRAPH_H
