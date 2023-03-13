#include <iostream>

#include "Graph.h"

int main() {
    Graph g;

    bool bstations = g.loadStations();
    bool bconnections = g.loadConnections();

    vector<Station> stations = g.getStations();

    vector<Connection> connections = g.getConnections();

    cout << bstations << " " << bconnections << endl;

    cout << connections.size() << endl;
}
