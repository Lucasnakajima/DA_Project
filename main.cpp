#include <iostream>

#include "Graph.h"

int main() {
    Graph g;

    bool bstations = g.loadStations();
    bool bconnections = g.loadConnections();

    unordered_map<string, Station> stations = g.getStations();

    vector<Connection> connections = g.getTargets()["Vila Nova de Gaia-Devesas"];

    cout << bstations << " " << bconnections << endl;

    cout << connections.size() << endl;



    for (auto i : connections) {
        cout << i.getSource()->getName() << endl;
        cout << i.getDestination()->getName() << endl;
    }
}
