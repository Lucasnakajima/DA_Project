//
// Created by Utilizador on 3/9/2023.
//


#include <fstream>
#include <sstream>
#include <algorithm>
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
            Connection connection((source->second), (dest->second), capacity, service);
            targets[sourceName].push_back(connection);
            connections.push_back(connection);
        }
    }

    return true;
}

void Graph::updateAdjacencyMatrix() {
    for (Connection& connection : connections) {
        string source = connection.getSource().getName();
        string destination = connection.getDestination().getName();
        int capacity = connection.getCapacity();
        adjacencyMatrix[source][destination] = capacity;
    }
}

int Graph::maxTrainsBetweenStations(const string source, const string destination) {
    int maxFlow = 0;
    unordered_map<string, string> parent;

    while (true) {
        queue<string> q;
        q.push(source);

        parent.clear();

        while (!q.empty() && parent.find(destination) == parent.end()) {
            string current = q.front();
            q.pop();

            for (const auto& neighbor : adjacencyMatrix[current]) {
                string neighborStation = neighbor.first;
                int capacity = neighbor.second;

                if (parent.find(neighborStation) == parent.end() && neighborStation != source && capacity > 0) {
                    parent[neighborStation] = current;
                    q.push(neighborStation);
                }
            }
        }

        if (parent.find(destination) == parent.end()) {
            break;
        }

        int pathFlow = INT_MAX;
        string currentStation = destination;

        while (currentStation != source) {
            string prevStation = parent[currentStation];
            pathFlow = min(pathFlow, adjacencyMatrix[prevStation][currentStation]);
            currentStation = prevStation;
        }

        maxFlow += pathFlow;
        currentStation = destination;

        while (currentStation != source) {
            string prevStation = parent[currentStation];
            adjacencyMatrix[prevStation][currentStation] -= pathFlow;
            adjacencyMatrix[currentStation][prevStation] += pathFlow;
            currentStation = prevStation;
        }
    }

    return maxFlow;
}


unordered_map<string, Station> Graph::getStations(){
    return stations;
}

vector<Connection> Graph::getConnections(){
    return connections;
}

unordered_map<string, vector<Connection>> Graph::getTargets() {
    return targets;
}

// dfs implementation without pointer or reference
vector<Station> Graph::dfs(Station start, Station end) {
    unordered_map<string, bool> visited;
    vector<Station> path;

    dfsHelper(start, visited, path);

    return path;
}

void Graph::dfsHelper(Station current, unordered_map<string, bool>& visited, vector<Station>& path) {
    visited[current.getName()] = true;
    path.push_back(current);

    for (Connection& connection : targets[current.getName()]) {
        Station neighbor = connection.getDestination();

        if (!visited[neighbor.getName()]) {
            dfsHelper(neighbor, visited, path);
        }
    }
}


vector<Station> Graph::bfs(Station start, Station end) {
    unordered_map<string, bool> visited;
    vector<Station> path;
    queue<Station> q;

    q.push(start);
    visited[start.getName()] = true;

    while (!q.empty()) {
        Station current = q.front();
        q.pop();

        path.push_back(current);

        for (Connection& connection : targets[current.getName()]) {
            Station neighbor = connection.getDestination();

            if (!visited[neighbor.getName()]) {
                q.push(neighbor);
                visited[neighbor.getName()] = true;
            }
        }
    }

    return path;
}






