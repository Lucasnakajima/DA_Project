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


bool Graph::bfs(string source, string destination) {
    unordered_map<string, bool> visited;
    for (const auto &entry : stations) {
        visited[entry.first] = false;
    }

    queue<string> q;
    q.push(source);
    visited[source] = true;
    parent[source] = "";

    while (!q.empty()) {
        string current = q.front();
        q.pop();

        for (auto &connection : targets[current]) {
            const string &next = connection.getDestination().getName();
            if (!visited[next] && connection.getResidual() >0) {
                visited[next] = true;
                parent[next] = current;
                q.push(next);
            }

            if (next == destination) {
                int pathFlow = numeric_limits<int>::max();
                for (string v = destination; v != source; v = parent[v]) {
                    string u = parent[v];
                    for (auto &conn : targets[u]) {
                        if (conn.getDestination().getName() == v) {
                            pathFlow = min(pathFlow, conn.getResidual());
                        }
                    }
                }
                if (pathFlow > 0) {
                    return true;
                }
            }
        }
    }

    return false;
}

bool Graph::dijkstra(string source, string destination) {
    unordered_map<string, int> dist;
    unordered_map<string, bool> visited;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;

    for (const auto &node : targets) {
        dist[node.first] = numeric_limits<int>::max();
    }
    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        string u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (const auto &connection : targets[u]) {
            string v = connection.getDestination().getName();
            int residual = connection.getCapacity();
            int cost = connection.getService() == "STANDARD" ? 2 : 4;

            if (!visited[v] && residual > 0 && dist[u] != numeric_limits<int>::max() && dist[u] + cost < dist[v]) {
                dist[v] = dist[u] + cost;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    return dist[destination] != numeric_limits<int>::max();
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
//Edmonds-Karp algorithm
int Graph::calculateMaxFlow(string source, string sink) {
    updateResidualConnections();
    int maxFlow = 0;
    parent.clear();
    unordered_map<string, bool> visited;
    while(bfs(source,sink)) {
        int pathFlow = INF;

        for (string v = sink; v != source; v = parent[v]) {
            string u = parent[v];
            for (const auto &connection: targets[u]) {
                if (connection.getDestination().getName() == v) {
                    pathFlow = min(pathFlow, connection.getCapacity());
                }
            }
        }
        for (string v = sink; v != source; v = parent[v]) {
            string u = parent[v];
            for (auto &connection : targets[u]) {
                if (connection.getDestination().getName() == v) {
                    connection.setResidual(connection.getResidual() - pathFlow);
                }
            }
            for (auto &reverseConnection : targets[v]) {
                if (reverseConnection.getDestination().getName() == u) {
                    reverseConnection.setResidual(reverseConnection.getResidual() + pathFlow);
                }
            }
        }

        maxFlow += pathFlow;
    }
    updateResidualConnections();
    return maxFlow;

}

vector<pair<string, string>> Graph::highestMaxFlowPairs() {
    int maxFlow = -1;
    vector<pair<string, string>> maxFlowStationPairs;
    unordered_set<string> addedPairs;

    for (auto& source : targets) {
        for (auto& connection : source.second) {
            const auto& destination = connection.getDestination().getName();

            int flow = calculateMaxFlow(source.first, destination);

            if (flow > maxFlow) {
                maxFlow = flow;
                maxFlowStationPairs.clear();
                maxFlowStationPairs.push_back({source.first, destination});
                addedPairs.clear();
                addedPairs.insert(source.first + "->" + destination);
                addedPairs.insert(destination + "->" + source.first);
            } else if (flow == maxFlow) {
                string forwardPairStr = source.first + "->" + destination;
                string reversePairStr = destination + "->" + source.first;
                if (addedPairs.find(forwardPairStr) == addedPairs.end() &&
                    addedPairs.find(reversePairStr) == addedPairs.end()) {
                    maxFlowStationPairs.push_back({source.first, destination});
                    addedPairs.insert(forwardPairStr);
                    addedPairs.insert(reversePairStr);
                }
            }
        }
    }

    return maxFlowStationPairs;
}


vector<string> Graph::findSourceStations() {
    unordered_map<string, int> inDegree;
    for (const auto& station : stations) {
        inDegree[station.first] = 0;
    }

    for (const auto& target : targets) {
        for (const auto& connection : target.second) {
            inDegree[connection.getDestination().getName()]++;
        }
    }

    vector<string> sourceStations;
    for (const auto& stationDegree : inDegree) {
        if (stationDegree.second == 1) {
            sourceStations.push_back(stationDegree.first);
        }
    }

    return sourceStations;
}

vector<pair<string, string>> Graph::highestMaxFlowPairsPath(string source, string sink) {
    int maxFlow = -1;
    vector<pair<string, string>> maxFlowStationPairs;

    for (const auto& connection : targets[source]) {
        const auto& destination = connection.getDestination().getName();

        int flow = calculateMaxFlow(source, destination);

        if (flow > maxFlow) {
            maxFlow = flow;
            maxFlowStationPairs.clear();
            maxFlowStationPairs.push_back({source, destination});
        } else if (flow == maxFlow) {
            maxFlowStationPairs.push_back({source, destination});
        }
    }

    return maxFlowStationPairs;
}

// 2.4
int Graph::maxTrainsAtStation(string stationName) {
    //TODO testes com Viana do Castelo e Porto Campanhã
    string superSource = "SUPER_SOURCE";

    vector<string> sourceStations = findSourceStations();

    // Create a super source and connect it to all source stations with infinite capacity
    for (const auto& source : sourceStations) {
        Connection superSourceConnection(Station(superSource, "", "", "", ""), stations[source], INF, "STANDARD");
        targets[superSource].push_back(superSourceConnection);
    }

    // Calculate max flow between the super source and the given station
    int maxTrains = calculateMaxFlow(superSource, stationName);

    // Remove the super source and its connections
    targets.erase(superSource);

    return maxTrains;
}


void Graph::updateResidualConnections() {
    for(auto &i : connections){
        i.setResidual(i.getCapacity());
    }
    for(auto &j : targets){
        for(auto &x : j.second){
            x.setResidual(x.getCapacity());
        }
    }
}

pair<int, int> Graph::calculateMinCostMaxFlow(string source, string sink) {
    int maxFlow = 0;
    int minCost = 0;
    parent.clear();
    updateResidualConnections();

    while (dijkstra(source, sink)) {
        int pathFlow = numeric_limits<int>::max();
        int pathCost = 0;

        cout << pathCost << endl;

        for (string v = sink; v != source; v = parent[v]) {
            string u = parent[v];
            for (auto &connection : targets[u]) {
                if (connection.getDestination().getName() == v) {
                    cout << pathCost << endl;
                    pathFlow = min(pathFlow, connection.getCapacity());
                }
            }
        }

        // Calculate the path cost
        for (string v = sink; v != source; v = parent[v]) {
            string u = parent[v];
            for (auto &connection: targets[u]) {
                if (connection.getDestination().getName() == v) {
                    cout << pathCost << endl;
                    connection.setCapacity(connection.getCapacity() - pathFlow);
                    pathCost += (connection.getService() == "STANDARD" ? 2 : 4);
                    cout << pathCost << endl;
                }
            }
            for (auto &reverseConnection: targets[v]) {
                if (reverseConnection.getDestination().getName() == u) {
                    reverseConnection.setCapacity(reverseConnection.getCapacity() + pathFlow);
                }
            }
        }

        maxFlow += pathFlow;
        minCost += pathFlow * pathCost;
    }

    return make_pair(maxFlow, minCost);
}

bool Graph::bfsMunicipality(string source, string destination) {
    unordered_map<string, bool> visited;
    for (const auto &entry : stations) {
        visited[entry.first] = false;
    }
    auto municipality = stations.find(source)->second.getMunicipality();
    queue<string> q;
    q.push(source);
    visited[source] = true;
    parent[source] = "";

    while (!q.empty()) {
        string current = q.front();
        q.pop();

        for (auto &connection : targets[current]) {
            const string &next = connection.getDestination().getName();
            if (!visited[next] && connection.getResidual() >0 && municipality==connection.getDestination().getMunicipality()) {
                visited[next] = true;
                parent[next] = current;
                q.push(next);
            }

            if (next == destination) {
                int pathFlow = numeric_limits<int>::max();
                for (string v = destination; v != source; v = parent[v]) {
                    string u = parent[v];
                    for (auto &conn : targets[u]) {
                        if (conn.getDestination().getName() == v) {
                            pathFlow = min(pathFlow, conn.getResidual());
                        }
                    }
                }
                if (pathFlow > 0) {
                    return true;
                }
            }
        }
    }

    return false;
}

int Graph::calculateMaxFlowMunicipality(string source, string sink) {
    updateResidualConnections();
    int maxFlow = 0;
    parent.clear();
    unordered_map<string, bool> visited;
    while(bfsMunicipality(source,sink)) {
        int pathFlow = INF;

        for (string v = sink; v != source; v = parent[v]) {
            string u = parent[v];
            for (const auto &connection: targets[u]) {
                if (connection.getDestination().getName() == v) {
                    pathFlow = min(pathFlow, connection.getCapacity());
                }
            }
        }
        for (string v = sink; v != source; v = parent[v]) {
            string u = parent[v];
            for (auto &connection : targets[u]) {
                if (connection.getDestination().getName() == v) {
                    connection.setResidual(connection.getResidual() - pathFlow);
                }
            }
            for (auto &reverseConnection : targets[v]) {
                if (reverseConnection.getDestination().getName() == u) {
                    reverseConnection.setResidual(reverseConnection.getResidual() + pathFlow);
                }
            }
        }

        maxFlow += pathFlow;
    }
    updateResidualConnections();
    return maxFlow;

}

vector<string> Graph::topkbudgetMunicipality() {
    unordered_map<string, int> municipalities;
    unordered_map<string, int> maxmunicipalities;
    int maxFlow = -1;
    vector<pair<string, string>> maxFlowStationPairs;
    unordered_set<string> addedPairs;

    for (auto& source : targets) {
        auto municipality = stations.find(source.first)->second.getMunicipality();
        if(municipalities.empty()){
            municipalities.emplace(municipality, -1);
        }
        else if(municipalities.find(municipality) == municipalities.end()){
            municipalities.emplace(municipality, -1);
        }
        for (auto& connection : source.second) {
            if(connection.getDestination().getMunicipality() != municipality) continue;

            else {
                const auto &destination = connection.getDestination().getName();

                int flow = calculateMaxFlowMunicipality(source.first, destination);

                if (flow > municipalities.find(municipality)->second) {
                    municipalities.find(municipality)->second = flow;
                }
            }
        }
        if(maxmunicipalities.empty() || maxmunicipalities.begin()->second==municipalities.find(municipality)->second){
            maxmunicipalities.emplace(municipality, municipalities.find(municipality)->second);
        }
        else if(maxmunicipalities.begin()->second < municipalities.find(municipality)->second){
            maxmunicipalities.clear();
            maxmunicipalities.emplace(municipality, municipalities.find(municipality)->second);
        }
    }
    vector<string> result;
    for(auto i: maxmunicipalities){
        result.push_back(i.first);
    }
    return result;
}

bool Graph::bfsDistrict(string source, string destination) {
    unordered_map<string, bool> visited;
    for (const auto &entry : stations) {
        visited[entry.first] = false;
    }
    auto district = stations.find(source)->second.getDistrict();
    queue<string> q;
    q.push(source);
    visited[source] = true;
    parent[source] = "";

    while (!q.empty()) {
        string current = q.front();
        q.pop();

        for (auto &connection : targets[current]) {
            const string &next = connection.getDestination().getName();
            if (!visited[next] && connection.getResidual() >0 && district==connection.getDestination().getDistrict()) {
                visited[next] = true;
                parent[next] = current;
                q.push(next);
            }

            if (next == destination) {
                int pathFlow = numeric_limits<int>::max();
                for (string v = destination; v != source; v = parent[v]) {
                    string u = parent[v];
                    for (auto &conn : targets[u]) {
                        if (conn.getDestination().getName() == v) {
                            pathFlow = min(pathFlow, conn.getResidual());
                        }
                    }
                }
                if (pathFlow > 0) {
                    return true;
                }
            }
        }
    }

    return false;
}

int Graph::calculateMaxFlowDistrict(string source, string sink) {
    updateResidualConnections();
    int maxFlow = 0;
    parent.clear();
    unordered_map<string, bool> visited;
    while(bfsDistrict(source,sink)) {
        int pathFlow = INF;

        for (string v = sink; v != source; v = parent[v]) {
            string u = parent[v];
            for (const auto &connection: targets[u]) {
                if (connection.getDestination().getName() == v) {
                    pathFlow = min(pathFlow, connection.getCapacity());
                }
            }
        }
        for (string v = sink; v != source; v = parent[v]) {
            string u = parent[v];
            for (auto &connection : targets[u]) {
                if (connection.getDestination().getName() == v) {
                    connection.setResidual(connection.getResidual() - pathFlow);
                }
            }
            for (auto &reverseConnection : targets[v]) {
                if (reverseConnection.getDestination().getName() == u) {
                    reverseConnection.setResidual(reverseConnection.getResidual() + pathFlow);
                }
            }
        }

        maxFlow += pathFlow;
    }
    updateResidualConnections();
    return maxFlow;

}

vector<string> Graph::topkbudgetDistrict() {
    unordered_map<string, int> districts;
    unordered_map<string, int> maxdistricts;
    int maxFlow = -1;
    vector<pair<string, string>> maxFlowStationPairs;
    unordered_set<string> addedPairs;

    for (auto& source : targets) {
        auto district = stations.find(source.first)->second.getDistrict();
        if(districts.empty()){
            districts.emplace(district, -1);
        }
        else if(districts.find(district) == districts.end()){
            districts.emplace(district, -1);
        }
        for (auto& connection : source.second) {
            if(connection.getDestination().getDistrict() != district) continue;

            else {
                const auto &destination = connection.getDestination().getName();

                int flow = calculateMaxFlowDistrict(source.first, destination);

                if (flow > districts.find(district)->second) {
                    districts.find(district)->second = flow;
                }
            }
        }
        if(maxdistricts.empty() || maxdistricts.begin()->second==districts.find(district)->second){
            maxdistricts.emplace(district, districts.find(district)->second);
        }
        else if(maxdistricts.begin()->second < districts.find(district)->second){
            maxdistricts.clear();
            maxdistricts.emplace(district, districts.find(district)->second);
        }
    }
    vector<string> result;
    for(auto i: maxdistricts){
        result.push_back(i.first);
    }
    return result;
}

void Graph:: removeConnection(string s1, string s2){
    for(auto i = targets.find(s1)->second.begin(); i!=targets.find(s1)->second.end(); i++){
        if(i->getDestination().getName() == s2){
            targets.find(s1)->second.erase(i);
        }
    }
    for(auto i = targets.find(s2)->second.begin(); i!=targets.find(s2)->second.end(); i++){
        if(i->getDestination().getName() == s1){
            targets.find(s2)->second.erase(i);
        }
    }
    for(auto i = connections.begin(); i!=connections.end(); i++){
        if(i->getSource().getName() == s1 || i->getSource().getName() == s2){
            connections.erase(i);
        }
    }
}







