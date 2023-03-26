//
// Created by Utilizador on 3/9/2023.
//


#include <fstream>
#include <sstream>
#include <algorithm>
#include <queue>
#include "Graph.h"

using namespace std;
const int INF = 1e9;

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
            Connection connection_reverse((dest->second), (source->second), capacity, service);
            connections.push_back(connection_reverse);
            targets[destName].push_back(connection_reverse);
        }
    }

    return true;
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

bool Graph::dfs(string source, string destination) {
    unordered_map<string, bool> visited;
    for (const auto &entry : stations) {
        visited[entry.first] = false;
    }

    return dfsHelper(source, destination, visited);
}

bool Graph::dfsHelper(const string &source, const string &destination, unordered_map<string, bool> &visited) {
    if (source == destination) {
        return true;
    }

    visited[source] = true;
    for (const auto &connection : targets[source]) {
        const string &next = connection.getDestination().getName();
        if (!visited[next]) {
            if (dfsHelper(next, destination, visited)) {
                return true;
            }
        }
    }

    return false;
}

bool Graph::bfsHelper(const string &source, const string &destination, unordered_map<string, bool> &visited) {
    queue<string> q;
    q.push(source);
    visited[source] = true;

    while (!q.empty()) {
        string current = q.front();
        q.pop();

        if (current == destination) {
            return true;
        }

        for (const auto &connection : targets[current]) {
            const string &next = connection.getDestination().getName();
            if (!visited[next]) {
                visited[next] = true;
                q.push(next);
            }
        }
    }

    return false;
}

bool Graph::bfs(string source, string destination) {
    unordered_map<string, bool> visited;
    for (const auto &entry : stations) {
        visited[entry.first] = false;
    }

    return bfsHelper(source, destination, visited);
}

vector<Station> Graph::shortestPath(string source, string destination) {
    unordered_map<string, int> distances;
    unordered_map<string, Station> previous;

    for (const auto& entry : stations) {
        distances[entry.first] = numeric_limits<int>::max();
    }

    distances[source] = 0;

    using StationDistance = pair<int, string>;
    priority_queue<StationDistance, vector<StationDistance>, greater<StationDistance>> pq;
    pq.push(make_pair(0, source));

    while (!pq.empty()) {
        string current = pq.top().second;
        pq.pop();

        if (current == destination) {
            break;
        }

        for (const auto& connection : targets[current]) {
            string next = connection.getDestination().getName();
            int newDistance = distances[current] + 1;

            if (newDistance < distances[next]) {
                distances[next] = newDistance;
                previous[next] = stations[current];
                pq.push(make_pair(newDistance, next));
            }
        }
    }

    vector<Station> path;
    if (previous.find(destination) != previous.end()) {
        Station currentStation = stations[destination];
        while (currentStation.getName() != source) {
            path.push_back(currentStation);
            currentStation = previous[currentStation.getName()];
        }
        path.push_back(stations[source]);
        reverse(path.begin(), path.end());
    }

    return path;
}

int Graph::findAugmentingPath(const string& source, const string& sink, int flow, unordered_map<string, bool>& visited) {
    if (source == sink) {
        return flow;
    }

    visited[source] = true;
    for (auto& connection : targets[source]) {
        const string& next = connection.getDestination().getName();
        int capacity = connection.getCapacity();

        if (!visited[next] && capacity > 0) {
            int minFlow = min(flow, capacity);
            int result = findAugmentingPath(next, sink, minFlow, visited);

            if (result > 0) {
                // Update the capacities in the original graph and residual graph
                connection.setCapacity(capacity - result);
                for (auto& reverseConnection : targets[next]) {
                    if (reverseConnection.getDestination().getName() == source) {
                        reverseConnection.setCapacity(reverseConnection.getCapacity() + result);
                        break;
                    }
                }

                return result;
            }
        }
    }

    return 0;
}

int Graph::calculateMaxFlow(string source, string sink) {
    int maxFlow = 0;
    unordered_map<string, bool> visited;

    // Initialize visited map
    for (const auto& entry : stations) {
        visited[entry.first] = false;
    }

    int flow = findAugmentingPath(source, sink, numeric_limits<int>::max(), visited);
    while (flow != 0) {
        maxFlow += flow;

        // Reset visited map for the next iteration
        for (const auto& entry : stations) {
            visited[entry.first] = false;
        }

        flow = findAugmentingPath(source, sink, numeric_limits<int>::max(), visited);
    }

    return maxFlow;
}









