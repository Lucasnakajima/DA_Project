//
// Created by Utilizador on 3/9/2023.
//

#ifndef PROJETO_GRAPH_H
#define PROJETO_GRAPH_H

#include <string>
#include <vector>
#include "Station.h"
#include "Connection.h"

using namespace std;

class Graph {

private:
    vector<Station> stations;
    vector<Connection> connections;


public:
    Graph();

    bool loadStations();
    bool loadConnections();

    vector<Station> getStations();
    vector<Connection> getConnections();
};


#endif //PROJETO_GRAPH_H
