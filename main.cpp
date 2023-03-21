#include <iostream>

#include "Graph.h"

int main() {
    Graph g;

    bool bstations = g.loadStations();
    bool bconnections = g.loadConnections();

    unordered_map<string, Station> stations = g.getStations();
    string source = "Lisboa Oriente";
    string destination = "Vila Nova de Gaia-Devesas";

    vector<Connection> targets = g.getTargets()[destination];

    int shortest = g.maxTrainsBetweenStations2("Bencanta","Aguim");

    cout << bstations << " " << bconnections << endl;

    cout << shortest;


}
