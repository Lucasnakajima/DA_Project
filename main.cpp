#include <iostream>

#include "Graph.h"

int main() {
    Graph g;

    bool bstations = g.loadStations();
    bool bconnections = g.loadConnections();

    unordered_map<string, Station> stations = g.getStations();
    string source = "Vila Nova de Gaia - Devesas";
    string destination = "Lisboa Oriente";

    vector<Connection> targets = g.getTargets()[destination];

    int shortest = g.maxTrainsBetweenStations(source,destination);

    cout << bstations << " " << bconnections << endl;

    cout << shortest<< endl;

   vector<pair<string, string>> pairs = g.findStationPairsRequiringMostTrains();
    cout << pairs.size()<< endl;

    for (auto i : pairs) {
        cout << i.first << " " << i.second;
    }

    Station a = g.findHeaviestEdgesInPath("Lisboa Oriente", "Espinho");

}
