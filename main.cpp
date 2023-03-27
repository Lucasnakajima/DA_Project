#include <iostream>

#include "Graph.h"

int main() {
    Graph g;

    bool bstations = g.loadStations();
    bool bconnections = g.loadConnections();

    unordered_map<string, Station> stations = g.getStations();
    string source = "Vila Nova de Gaia-Devesas";
    string destination = "Lisboa Oriente";

    string source2 = "Bencanta";
    string destination2 = "Aguim";

    //vector<Connection> targets = g.getTargets()[destination];

    cout << g.calculateMaxFlow("Espinho", "Porto Campanhã") << endl;
    cout << g.calculateMaxFlow(source, destination) << endl;
    //cout << bstations << " " << bconnections << endl;

    //cout << shortest<< endl;

    //vector<Station> shortest_path = g.shortestPath(source2, destination2);

    //for (auto i : shortest_path) {
        //cout << i.getName() << endl;}

   //bool dfs = g.dfs(source2, destination2);

   //cout << "  a " << g.calculateMaxFlow("Bencanta","Aguim") << endl;

   //cout << dfs << endl;

    vector<pair<string, string>> pairs = g.highestMaxFlowPairs();

    //cout << pairs.size() << endl;

    for (auto i : pairs) {
        cout << i.first << " " << i.second << endl;
    }



    //Station a = g.findHeaviestEdgesInPath("Lisboa Oriente", "Espinho");

}
