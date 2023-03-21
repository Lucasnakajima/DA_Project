#include <iostream>

#include "Graph.h"

int main() {
    Graph g;

    bool bstations = g.loadStations();
    bool bconnections = g.loadConnections();
    g.updateAdjacencyMatrix();

    unordered_map<string, Station> stations = g.getStations();
    string source = "Lisboa Oriente";
    string destination = "Vila Nova de Gaia-Devesas";

    vector<Station> bfs = g.bfs(stations[source], stations[destination]);

    cout << bstations << " " << bconnections << endl;

    int maxTrains = g.maxTrainsBetweenStations(source, destination);
    cout << "Maximum number of trains that can simultaneously travel between " << source << " and " << destination << " is: " << maxTrains << endl;
}
