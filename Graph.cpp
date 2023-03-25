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

void Graph::updateResidualMatrix() {
    residual.clear();
    for (auto i : stations) {
        residual[i.first] = unordered_map<string, int>();
        for (auto j : stations) {
            residual[i.first][j.first] = 0;
        }
    }
    for (Connection& connection : connections) {
        string source = connection.getSource().getName();
        string destination = connection.getDestination().getName();
        int capacity = connection.getCapacity();
        residual[source][destination] += capacity;
        residual[destination][source] += capacity;
    }
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

int Graph::getIndex(const string name) {
    int i = 0;
    for(auto x : stations) {
        if (x.first == name) {
            return i;
        }
        i++;
    }
    return -1;
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


bool Graph::bfs(Station sourceName, Station destName) {
    queue<string> q;
    unordered_map<string, bool> visited;

    for (auto it = stations.begin(); it != stations.end(); it++) {
        visited[it->first] = false;
        parent[it->first] = "";
    }

    q.push(sourceName.getName());
    visited[sourceName.getName()] = true;
    parent[sourceName.getName()] = "";

    while (!q.empty()) {
        string u = q.front();
        q.pop();

        for (auto it = targets[u].begin(); it != targets[u].end(); it++) {
            string v = it->getDestination().getName();

            // Only consider edges with positive residual capacity
            if (visited[v] == false && residual[u][v] > 0) {
                visited[v] = true;
                parent[v] = u;
                q.push(v);
                cout << "Parent of node " << v << " is " << parent[v] << endl;

                // Return true if we have reached the destination
                if (v == destName.getName()) {
                    return true;
                }
            }
        }
    }

    // If we reach this point, there is no augmenting path from source to dest
    return false;
}

// implement ford fulkerson algorithm
int Graph::maxTrainsBetweenStations(const string source, const string destination) {
    /*int n = stations.size();
    // Construct the residual graph by subtracting the flow from the capacity along forward edges and adding the flow to the capacity along backward edges.
    updateResidualMatrix();
    int max_flow = 0;
    while(true){
        unordered_map<string,string> parent;
        for(auto i : stations){
            parent[i.first] = " ";
        }
        queue<pair<Station, int>> q;
        q.push({stations.find(source)->second, INF});
        while(!q.empty()){
            Station u = q.front().first;
            int flow = q.front().second;
            auto name = u.getName();
            q.pop();
            for(auto v = parent.begin(); v!=parent.end(); v++){
                auto first = v->first;
                auto second = v->second;
                if(v->first == "Vila Nova de Gaia-Devesas"){
                    //cout<<v->second<<endl;
                }
                if(v->second == " " && residual[u.getName()][v->first] > 0){
                    v->second = u.getName();
                    //cout << v->first << endl;
                    int new_flow = min(flow, residual[u.getName()][v->first]);
                    if(v->first==destination){
                        max_flow+=new_flow;
                        while(v->first!=source){
                            auto first = v->first;
                            auto second = v->second;
                            u= stations.find(v->second)->second;
                            residual[u.getName()][v->first] -= new_flow;
                            residual[v->first][u.getName()] += new_flow;
                            v = parent.find(u.getName());
                        }
                        break;
                    }
                    q.push({stations.find(v->first)->second, new_flow});
                }
            }
            if(parent[destination] != " ") break;
        }
        if(parent[destination] == " ") break;
    }
        return max_flow;*/
    int max_flow = 0;
    updateResidualMatrix();
    while (bfs(stations[source], stations[destination])) {
        int path_flow = INT_MAX;
        string v = destination;
        while (v != source) {
            string u = parent[v];
            path_flow = min(path_flow, residual[u][v]);
            v = u;
        }
        v = destination;
        while (v != source) {
            string u = parent[v];
            residual[u][v] -= path_flow;
            residual[v][u] += path_flow;
            v = u;
        }
        max_flow += path_flow;
        updateResidualMatrix();
    }
    return max_flow;
}

// Add this function to the Graph class
/*vector<pair<string, string>> Graph::findStationPairsRequiringMostTrains() {
    int maxFlow = -1;
    vector<pair<string, string>> maxFlowStationPairs;
    unordered_map<string, unordered_map<string, int>> memo;

    for ( auto& source : targets) {
        for ( auto& connection : source.second) {
            const auto& destination = connection.getDestination().getName();

            if (memo[source.first].find(destination) == memo[source.first].end()) {
                memo[source.first][destination] = maxTrainsBetweenStations(source.first, destination);
            }

            int flow = memo[source.first][destination];

            if (flow > maxFlow) {
                maxFlow = flow;
                maxFlowStationPairs.clear();
                maxFlowStationPairs.push_back({source.first, destination});
            } else if (flow == maxFlow) {
                maxFlowStationPairs.push_back({source.first, destination});
            }
        }
    }

    return maxFlowStationPairs;
}*/

vector<pair<string, string>> Graph::findStationPairsRequiringMostTrains() {
    int maxFlow = -1;
    vector<pair<string, string>> maxFlowStationPairs;

    for (auto& source : targets) {
        for (auto& connection : source.second) {
            const auto& destination = connection.getDestination().getName();

            int flow = maxTrainsBetweenStations(source.first, destination);

            if (flow > maxFlow) {
                maxFlow = flow;
                maxFlowStationPairs.clear();
                maxFlowStationPairs.push_back({source.first, destination});
            } else if (flow == maxFlow) {
                maxFlowStationPairs.push_back({source.first, destination});
            }
        }
    }

    return maxFlowStationPairs;
}

Station Graph::findHeaviestEdgesInPath(string origin, string end) {

    unordered_map<string, int> maxCapacity;
    unordered_map<string, string> parent;
    unordered_map<string, int> distance;
    unordered_map<string, bool> visited;
    for (auto i : stations) {
        parent[i.first] = "";
        maxCapacity[i.first] = 0;
        distance[i.first] = INF;
        visited[i.first] = false;
    }
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
    distance[origin] = 0;
    pq.push({0, origin});

    while (!pq.empty()) {
        string u = pq.top().second;
        pq.pop();
        if (u == end) break;
        if (visited[u]) continue;
        visited[u] = true;
        for (auto j : targets[u]) {
            string v = j.getDestination().getName();
            if(v == "Espinho") {
                int weight = j.getCapacity();
            }
                int new_distance = distance[u] + 1;
                if (new_distance < distance[v]) {
                    distance[v] = new_distance;
                    parent[v] = u;
                    pq.push({distance[v], v});
                }

        }
    }

    string u = end;
    int max = targets[u].size();
    string maxi = u;
    string v = parent[u];
    while (u != origin) {
        string v = parent[u];
        if (targets[v].size() > max) {
            maxi = v;
            max = targets[v].size();
        }
        u = v;
    }
    if (targets[origin].size() > max) {
        maxi = origin;
        max = targets[origin].size();
    }
    return stations[maxi];
}







