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

    vector<Station> shortest = g.shortestPath(g.getStations()[source], g.getStations()[destination]);

    cout << bstations << " " << bconnections << endl;

    for (auto i : targets) {
        cout << i.getDestination().getName() << endl;
    }
}
