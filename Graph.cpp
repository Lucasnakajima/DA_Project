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

        stations.emplace_back(name, district, municipality, township, line);
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

        // Find the source and destination stations in the list of stations
        Station* source = nullptr;
        Station* dest = nullptr;
        for (auto& station : stations) {
            if (station.getName() == sourceName) {
                source = &station;
            }
            if (station.getName() == destName) {
                dest = &station;
            }
            if (source && dest) {
                break;
            }
        }

        // Add the connection if the source and destination stations were found
        if (source && dest) {
            connections.emplace_back(source, dest, capacity, service);
        }
    }

    return true;
}

vector<Station> Graph::getStations() {
    return stations;
}

vector<Connection> Graph::getConnections() {
    return connections;
}