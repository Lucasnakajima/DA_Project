//
// Created by Utilizador on 3/9/2023.
//


#include <fstream>
#include <sstream>
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

int Graph::maxTrainsBetweenStations(const string& source, const string& destination) {
    // Create a priority queue to store the unprocessed nodes
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;

    // Create a map to store the shortest distance and minimum capacity for each node
    unordered_map<string, pair<int, int>> distance;

    // Initialize the distance and minimum capacity for each node
    for (const auto& station : stations) {
        distance[station.first] = make_pair(numeric_limits<int>::max(), numeric_limits<int>::min());
    }

    // Set the distance and minimum capacity for the source station
    distance[source] = make_pair(0, numeric_limits<int>::max());

    // Add the source station to the priority queue
    pq.push(make_pair(0, source));

    while (!pq.empty()) {
        int current_distance = pq.top().first;
        string current_station = pq.top().second;
        pq.pop();

        // If the current station is the destination, break the loop
        if (current_station == destination) {
            break;
        }

        // If the current station has already been processed, skip it
        if (current_distance > distance[current_station].first) {
            continue;
        }

        for (Connection& connection : targets[current_station]) {
            string next_station = connection.getDestination()->getName();
            int new_distance = current_distance + 1;
            int new_capacity = min(distance[current_station].second, connection.getCapacity());

            // If the new path has a shorter distance or a higher capacity, update the values
            if (new_distance < distance[next_station].first || new_capacity > distance[next_station].second) {
                distance[next_station] = make_pair(new_distance, new_capacity);
                pq.push(make_pair(new_distance, next_station));
            }
        }
    }

    // Return the minimum capacity of the shortest path between the source and destination stations
    return distance[destination].second;
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