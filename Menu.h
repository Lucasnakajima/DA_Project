#ifndef AIRTRANSPORT_MENU_H
#define AIRTRANSPORT_MENU_H
#include "Graph.h"
#include <stdlib.h>
///Classe para o Menu.
///
///Um menu apenas apresenta as opcoes.
class Menu {
private:
    Graph g;
public:
    Menu();
    void run();
    void maxBetweenTwoStations();
    bool inputTest(char choice, vector<int> values);

    vector<string> stationsFetch();

    bool validStation(Graph g, string station);
};


#endif //AIRTRANSPORT_MENU_H