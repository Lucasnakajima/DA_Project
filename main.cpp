#include <iostream>
#include "Menu.h"
#include "Graph.h"
using namespace std;
int main() {
    Graph g;

    bool bstations = g.loadStations();
    bool bconnections = g.loadConnections();

    //unordered_map<string, Station> stations = g.getStations();
    //string source = "Vila Nova de Gaia-Devesas";
    //string destination = "Lisboa Oriente";
//
    //string source2 = "Bencanta";
    //string destination2 = "Aguim";
    //vector<Connection> targets = g.getTargets()[destination];

    //cout << g.calculateMaxFlow(source, "Porto Campanhã") << endl;
    //cout << g.calculateMaxFlow(source, destination) << endl;
    //pair<int, int> a = g.calculateMinCostMaxFlow(source, destination);
    //cout << a.first << endl << a.second;
    //cout << bstations << " " << bconnections << endl;

    //cout << shortest<< endl;

    //vector<Station> shortest_path = g.shortestPath(source2, destination2);

    //for (auto i : shortest_path) {
        //cout << i.getName() << endl;}

   //bool dfs = g.dfs(source2, destination2);

   //cout << "  a " << g.calculateMaxFlow("Bencanta","Aguim") << endl;

   //cout << dfs << endl;

    //cout << pairs.size() << endl;

    //vector<pair<string, string>> pairs = g.highestMaxFlowPairs();

    //for (auto i : pairs) cout << i.first << " " << i.second << endl;

    //cout << g.maxTrainsAtStation("Coimbra B");

    //Station a = g.findHeaviestEdgesInPath("Lisboa Oriente", "Espinho");

//    pair<int, int> pair = g.calculateMinCostMaxFlow("Porto Campanhã", "Lisboa Oriente");
//
//    cout << pair.first << " " << pair.second << endl;

    Menu menu;
    return 0;
}
