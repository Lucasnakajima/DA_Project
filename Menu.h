#ifndef AIRTRANSPORT_MENU_H
#define AIRTRANSPORT_MENU_H
#include "Graph.h"
#include <stdlib.h>
///Classe para o Menu.
///
///Um menu apenas apresenta as opcoes.
class Menu {
private:

public:
    Menu();
    void run();

    bool inputTest(char choice, vector<int> values);
};


#endif //AIRTRANSPORT_MENU_H