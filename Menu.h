#ifndef AIRTRANSPORT_MENU_H
#define AIRTRANSPORT_MENU_H
#include "Graph.h"
#include <stdlib.h>
///Classe para o Menu.
///
///Um menu apenas apresenta as opcoes.
class Menu {
private:
    Graph g; //Graph for the original railroad
    Graph rc; //Graph for reduced connectivity
public:
    Menu();
    void run();
    void maxBetweenTwoStations();
    bool inputTest(char choice, vector<int> values);

    vector<string> stationsFetch();

    bool validStation(Graph g, string station);

    bool validConnection(Graph g, string s1, string s2);
};


#endif //AIRTRANSPORT_MENU_H