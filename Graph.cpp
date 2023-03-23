//
// Created by Utilizador on 3/9/2023.
//


#include <fstream>
#include <sstream>
#include <algorithm>
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
        }
    }

    return true;
}

void Graph::updateResidualMatrix() {
    for (Connection& connection : connections) {
        string source = connection.getSource().getName();
        string destination = connection.getDestination().getName();
        int capacity = connection.getCapacity();
        residual[source][destination] = capacity;
        residual[destination][source] = capacity;
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

// implement ford fulkerson algorithm
int Graph::maxTrainsBetweenStations(const string source, const string destination) {
    int n = stations.size();
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

Connection Graph::findHeaviestEdgesInPath(string origin, string end) {
/*    unordered_map<string, int> maxCapacity;
    unordered_map<string, string> previous;
    unordered_set<string> unvisited;

    // Initialize the maxCapacity and previous maps
    for (const auto& station : stations) {
        maxCapacity[station.first] = (station.first == origin) ? INT_MAX : 0;
        previous[station.first] = "";
        unvisited.insert(station.first);
    }

    while (!unvisited.empty()) {
        // Find the station with the maximum capacity that has not been visited
        string currentStation;
        int currentMaxCapacity = -1;
        for (const auto& station : unvisited) {
            if (maxCapacity[station] > currentMaxCapacity) {
                currentMaxCapacity = maxCapacity[station];
                currentStation = station;
            }
        }

        // If the current station is the end station, break the loop
        if (currentStation == end) break;

        // Mark the current station as visited
        unvisited.erase(currentStation);

        // Update the capacities for the neighbors of the current station
        for ( auto& connection : targets[currentStation]) {
            const auto& neighbor = connection.getDestination().getName();
            int capacity = connection.getCapacity();

            if (unvisited.find(neighbor) != unvisited.end() && min(maxCapacity[currentStation], capacity) > maxCapacity[neighbor]) {
                maxCapacity[neighbor] = min(maxCapacity[currentStation], capacity);
                previous[neighbor] = currentStation;
            }
        }
    }

    // Find the heaviest edges in the path
    vector<pair<string, string>> heaviestEdges;
    int heaviestEdgeCapacity = -1;
    string current = end;

    while (previous[current] != "") {
        string prev = previous[current];
        int capacity = maxCapacity[current];

        if (capacity > heaviestEdgeCapacity) {
            heaviestEdgeCapacity = capacity;
            heaviestEdges.clear();
            heaviestEdges.push_back({prev, current});
        } else if (capacity == heaviestEdgeCapacity) {
            heaviestEdges.push_back({prev, current});
        }

        current = prev;
    }

    return heaviestEdges;*/

    unordered_map<string, int> maxCapacity;
    unordered_map<string,string> parent;
    unordered_map<string, int> distance;
    unordered_map<string, int> distance1;
    unordered_map<string, bool> visited;
    for(auto i : stations){
        parent[i.first] = " ";
        maxCapacity[i.first] = 0;
        distance[i.first] = INF;
        distance1[i.first] = INF;
        visited[i.first] = false;
    }
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq1;
    distance[origin] = 0;
    distance1[end] = 0;
    pq.push({0, origin});
    pq1.push({0, end});
    while(!pq.empty() && !pq1.empty()){
        if(pq.top().first <= pq1.top().first) {
            string u = pq.top().second;
            pq.pop();
            if(visited[u]) continue;
            visited[u] = true;
            for(auto j : targets[u]){
                string v = j.getDestination().getName();
                int weight = j.getCapacity();
                if(!visited[v]){
                    int new_distance = distance[u] + 1;
                    if(new_distance < distance[v]) {
                        distance[v] = new_distance;
                        maxCapacity[v] = max(maxCapacity[u], weight);
                        pq.push({distance[v], v});
                    }
                }
            }
            if(visited[end]) break;
        } else{
            string u = pq1.top().second;
            pq1.pop();
            if(visited[u]) continue;
            visited[u] = true;
            for(auto j : targets[u]){
                string v = j.getDestination().getName();
                int weight = j.getCapacity();
                if(!visited[v]){
                    int new_distance = distance1[u] + 1;
                    if(new_distance < distance1[v]) {
                        distance1[v] = new_distance;
                        maxCapacity[v] = max(maxCapacity[u], weight);
                        pq1.push({distance1[v], v});
                    }
                }
            }
            if(visited[origin]) break;
        }
    }

    Connection heaviest_edge;
    int min_distance = INF;
    for(auto u: stations){
        if(distance[u.first] < INF || distance1[u.first]< INF){
            int ok = distance[u.first];
            int ok1 = distance1[u.first];
            min_distance = INF;
        }
        if((distance[u.first] < INF || distance1[u.first] < INF)/* && distance1[u.first] + distance[u.first] < min_distance*/){
            if(distance[u.first] < INF) min_distance = distance[u.first];
            else min_distance = distance1[u.first];
            heaviest_edge = new Connection(u.second, u.second, maxCapacity[u.first], "a");
            string v = u.first;
            while(v!=origin){
                string parent1 = " ";
                for(auto connection : targets[v]){
                    if(distance[connection.getDestination().getName()] < distance[v]){
                        parent1 = connection.getDestination().getName();
                        break;
                    }
                }
               if(parent1 != " "){
                   if(maxCapacity[parent1] > heaviest_edge.getCapacity()){
                        heaviest_edge.setSource(stations[parent1]);
                        heaviest_edge.setDestination(stations[v]);
                        heaviest_edge.setCapacity(maxCapacity[parent1]);
                   }
                   v = parent1;
               } else{
                   break;
               }

            }
            v = u.first;
            while(v!=origin) {
                string parent1 = " ";
                for (auto connection: targets[v]) {
                    if (distance1[connection.getDestination().getName()] < distance1[v]) {
                        parent1 = connection.getDestination().getName();
                        break;
                    }
                }
                if (parent1 != " ") {
                    if (maxCapacity[parent1] > heaviest_edge.getCapacity()) {
                        heaviest_edge.setSource(stations[v]);
                        heaviest_edge.setDestination(stations[parent1]);
                        heaviest_edge.setCapacity(maxCapacity[parent1]);
                    }
                    v = parent1;
                } else {
                    break;
                }
            }
            break;
        }
    }
    return heaviest_edge;
}






