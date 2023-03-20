//
// Created by Utilizador on 3/9/2023.
//


#include <fstream>
#include <sstream>
#include <queue>
#include "Graph.h"

using namespace std;

Graph::Graph() {}

bool Graph::loadStations() {
    ifstream inputFile("stations.csv");

    if (!inputFile.is_open()) {
        return false;
    }

    // Skip header line
    string line;
    getline(inputFile, line);

    while (getline(inputFile, line)) {
        istringstream iss(line);

        string name, district, municipality, township, line;
        getline(iss, name, ',');
        getline(iss, district, ',');
        getline(iss, municipality, ',');
        getline(iss, township, ',');
        getline(iss, line, ',');

        Station station(name, district, municipality, township, line);
        stations.emplace(station.getName(), station);
    }

    return true;
}

bool Graph::loadConnections() {
    ifstream inputFile("network.csv");

    if (!inputFile.is_open()) {
        return false;
    }

    // Skip header line
    string line;
    getline(inputFile, line);

    while (getline(inputFile, line)) {
        istringstream iss(line);

        string sourceName, destName, service;
        int capacity;
        getline(iss, sourceName, ',');
        getline(iss, destName, ',');
        iss >> capacity;
        getline(iss.ignore(), service, ',');

        // Find the source and destination stations in the unordered_map
        auto source = stations.find(sourceName);
        auto dest = stations.find(destName);

        // Add the connection if the source and destination stations were found
        if (source != stations.end() && dest != stations.end()) {
            Connection connection(&(source->second), &(dest->second), capacity, service);
            targets[sourceName].push_back(connection);
            connections.push_back(connection);
        }
    }

    return true;
}

int Graph::maxTrainsBetweenStations(string stationA, string stationB) {
    // create adjacency list to store graph
    unordered_map<string, vector<pair<string, int>>> adj;
    for (auto conn: targets) {
        string source = conn.first;
        for (auto c: conn.second) {
            string dest = c.getDestination()->getName();
            adj[source].push_back(make_pair(dest, c.getCapacity()));
            adj[dest].push_back(make_pair(source, 0));  // residual edge
        }
    }

    // find shortest augmenting path using BFS
    int maxFlow = 0;
    while (true) {
        unordered_map<string, string> parent;
        unordered_map<string, int> capacity;
        parent[stationA] = "";
        capacity[stationA] = INT_MAX;
        queue<string> q;
        q.push(stationA);
        while (!q.empty()) {
            string u = q.front();
            q.pop();
            for (auto v: adj[u]) {
                if (parent.find(v.first) == parent.end() && v.second > 0) {
                    parent[v.first] = u;
                    capacity[v.first] = min(capacity[u], v.second);
                    if (v.first == stationB) {
                        break;
                    }
                    q.push(v.first);
                }
            }
            if (parent.find(stationB) != parent.end()) {
                break;
            }
        }
        if (parent.find(stationB) == parent.end()) {
            break;
        }
        maxFlow += capacity[stationB];
        string u = stationB;
        while (u != stationA) {
            string v = parent[u];
            for (auto &edge: adj[u]) {
                if (edge.first == v) {
                    edge.second -= capacity[stationB];
                    break;
                }
            }
            for (auto &edge: adj[v]) {
                if (edge.first == u) {
                    edge.second += capacity[stationB];
                    break;
                }
            }
            u = v;
        }
    }
}

unordered_map<string, Station> Graph::getStations() {
    return stations;
}

vector<Connection> Graph::getConnections() {
    return connections;
}

unordered_map<string, vector<Connection>> Graph::getTargets() {
    return targets;
}