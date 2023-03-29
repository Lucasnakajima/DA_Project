#include <unistd.h>
#include "Menu.h"
#include <algorithm>

using namespace std;
Menu::Menu() {
    run();
}

void Menu::run() {
    while(true){
        cout << string(50,'\n');
        cout << "||==================================================================================================================||\n"
                "||                         .__.__                                        __                       __                ||\n"
                "||           ____________  |__|  |__  _  _______  ___.__.   ____   _____/  |___  _  _____________|  | __            ||\n"
                "||           \\_  __ \\__  \\ |  |  |\\ \\/ \\/ /\\__  \\<   |  |  /    \\_/ __ \\   __\\ \\/ \\/ /  _ \\_  __ \\  |/ /            ||\n"
                "||            |  | \\// __ \\|  |  |_\\     /  / __ \\\\___  | |   |  \\  ___/|  |  \\     (  <_> )  | \\/    <             ||\n"
                "||            |__|  (____  /__|____/\\/\\_/  (____  / ____| |___|  /\\___  >__|   \\/\\_/ \\____/|__|  |__|_ \\            ||\n"
                "||                       \\/                     \\/\\/           \\/     \\/                              \\/            ||\n"
                "||==================================================================================================================||\n"
                "||                       NETWORK                       |         OPERATIONS BETWEEN TWO SPECIFIC STATIONS           ||\n"
                "||==================================================================================================================||\n"
                "||                                                     |                                                            ||\n"
                "||  Stations by municipalities                    [11] |  Max number of trains that can travel...              [21] ||\n"
                "||  Stations by Districts                         [12] |  Which pairs of stations require the most trains      [22] ||\n"
                "||                                                     |  Top-k stations most affected by each seg. failure    [23] ||\n"
                "||                                                     |                                                            ||\n"
                "||==================================================================================================================||\n"
                "||                REDUCED CONNECTIVITY                 |                    TRANSPORTATION NEEDS                    ||\n"
                "||==================================================================================================================||\n"
                "||                                                     |                                                            ||\n"
                "||  Add a segment failure                         [31] |  Top-k municipalities regarding transportation needs  [41] ||\n"
                "||  Remove a segment failure                      [32] |  Top-k districts regarding transportation needs       [42] ||\n"
                "||  Existent segment failures                     [33] |                                                            ||\n"
                "||                                                     |                                                            ||\n"
                "||==================================================================================================================||\n"
                "||                                                   EXIT [0]                                                       ||\n"
                "||==================================================================================================================||\n"
                "Choose an option: ";
        int choice;
        cin >> choice;
        vector<int> values = {0,11,12,21,22,23,31,32,33,41,42};
        if(!inputTest(choice,values)) continue;
        switch(choice){
            case 11:
                break;
            case 12:
                /*string srcAirport, destAirport;
                cout << "Digite o aeroporto de partida:";
                cin >> srcAirport;
                cout << "Digite o aeroporto de chegada:";
                cin >> destAirport;
                airlines = airlineSubmenu();
                pathByAirport(srcAirport, destAirport, airlines);
                system("pause");*/
                break;
            case 21:
                cout << "||===============================================||"
                        "|| Max number of trains that can travel:         ||"
                        "|| In the full railway network               [ ] ||"
                        "|| With a minimum cost for the company       [ ] ||"
                        "|| In the network with reduced connectivity  [ ] ||"
                        "||===============================================||";
                break;
            case 22:
                break;
            case 23:
                break;

            case 24:
                /*int y;
                cout << "Digite o aeroporto que deseja pesquisar:";
                cin >> airport;
                cout << "Digite o valor de y:";
                cin >> y;
                airportMaxYByAirport(airport, y);
                system("pause");*/
                break;

            case 0:
                cout << string(15,'\n');
                cout << "                                                  Thank you for using the railway network system!";
                cout << string(15,'\n');
                sleep(1);
                exit(0);
            default:
                cout << "Invalid Input !";
                system("pause");
        }

    }
}

/*vector<string> Menu:: airlineSubmenu(){
    vector<string> airlines;
    char n;
    while(true) {
        cout << "Deseja utilizar companhias aereas especificas na sua rota?Y/N\n";
        cin >> n;
        if (n == 'y' or n == 'Y') {
            int quant;
            string comp;
            cout << "Digite quantas companias estao em sua rota: ";
            cin >> quant;
            for (int i = 1; i <= quant; i++) {
                cout << "Companhia " << i << "/" << quant << ":";
                cin >> comp;
                airlines.push_back(comp);
            }
            return airlines;
        }
        else if (n == 'n' or n == 'N') return airlines;
        else{
            cout << "Escolha invalida! Tente novamente!";
            sleep (1);
        }
    }
}

void Menu:: pathByCoordinates(double srcLati, double srcLongi, double destLati, double destLongi, vector<string> airlines){
    vector<vector<vector<string>>> path = database.coordsPath(srcLati, srcLongi, destLati, destLongi, airlines);
    cout << "================================\n||     Voce possui " << path.size() << " rotas    ||\n================================\n\n";

    for(int k = 0; k<path.size(); k++) {
        cout << "=======Rota " << k+1 << "=======\n";
        for (int i = 0; i < path[k].size()-1; i++) {
            cout << "De " << path[k][i][0] << " para " << path[k][i+1][0] << ". Podendo ir com as seguintes companias aereas:\n";
            for (int j = 1; j < path[k][i].size(); j++) {
                cout << " --> " << path[k][i][j];
            }
            cout << "\n";
        }
        cout << "\n";
    }
}

void Menu:: pathByAirport(string srcAirport, string destAirport, vector<string> airlines){
    vector<vector<vector<string>>> path = database.path(srcAirport, destAirport, airlines);
    cout << "================================\n"
            "||     Voce possui " << path.size() << " rotas    ||\n"
                                                    "================================\n\n";

    for(int k = 0; k<path.size(); k++) {
        cout << "=======Rota " << k+1 << "=======\n";
        for (int i = 0; i < path[k].size()-1; i++) {
            cout << "De " << path[k][i][0] << " para " << path[k][i+1][0] << ". Podendo ir com as seguintes companias aereas:\n";
            for (int j = 1; j < path[k][i].size(); j++) {
                cout << " --> " << path[k][i][j];
            }
            cout << "\n";
        }
        cout << "\n";
    }
}

void Menu:: pathByCity(string srcCity, string srcCountry, string destCity, string destCountry, vector<string> airlines){
    vector<vector<vector<string>>> path = database.cityPath(srcCity, srcCountry, destCity, destCountry, airlines);
    cout << "================================\n"
            "||     Voce possui " << path.size() << " rotas    ||\n"
                                                    "================================\n\n";

    for(int k = 0; k<path.size(); k++) {
        cout << "=======Rota " << k+1 << "=======\n";
        for (int i = 0; i < path[k].size()-1; i++) {
            cout << "De " << path[k][i][0] << " para " << path[k][i+1][0] << ". Podendo ir com as seguintes companias aereas:\n";
            for (int j = 1; j < path[k][i].size(); j++) {
                cout << " --> " << path[k][i][j];
            }
            cout << "\n";
        }
        cout << "\n";
    }
}

void Menu:: flightsByAirport(string airport){
    unordered_set<string> dest = database.airportList(airport,1);
    cout << "Existem " << dest.size() << " voos a partir deste aerorporto\n";
    char n;
    while(true) {
        cout << "Deseja lista-los?Y/N\n";
        cin >> n;
        if (n == 'y' or n == 'Y') {
            for(auto i: dest){
                cout << airport << "-->" << i << "\n";
            }
            return;
        }
        else if (n == 'n' or n == 'N') return;
        else{
            cout << "Escolha invalida! Tente novamente!";
            sleep (1);
        }
    }
}

void Menu:: airlinesByAirport(string airport){
    unordered_set<string> dest = database.airportList(airport,2);
    cout << "Existem " << dest.size() << " linhas aereas que tem voos nesse aerorporto\n";
    char n;
    while(true) {
        cout << "Deseja lista-las?Y/N\n";
        cin >> n;
        if (n == 'y' or n == 'Y') {
            for(auto i: dest){
                cout << i << "\n";
            }
            return;
        }
        else if (n == 'n' or n == 'N') return;
        else{
            cout << "Escolha invalida! Tente novamente!";
            sleep (1);
        }
    }
}

void Menu:: cityByAirport(string airport){
    unordered_set<string> dest = database.airportList(airport,3);
    cout << "Existem " << dest.size() << " cidades atingiveis a partir deste aerorporto\n";
    char n;
    while(true) {
        cout << "Deseja lista-las?Y/N\n";
        cin >> n;
        if (n == 'y' or n == 'Y') {
            for(auto i: dest){
                cout << i << "\n";
            }
            return;
        }
        else if (n == 'n' or n == 'N') return;
        else{
            cout << "Escolha invalida! Tente novamente!";
            sleep (1);
        }
    }
}

void Menu:: airportMaxYByAirport(string airport, int y){
    unordered_set<string> dest = database.airportMaxY(airport,y);
    cout << "Existem " << dest.size() << " aeroportos atingiveis a "<< y << " voos de distancia\n";
    char n;
    while(true) {
        cout << "Deseja lista-los?Y/N\n";
        cin >> n;
        if (n == 'y' or n == 'Y') {
            for(auto i: dest){
                cout << airport << "-->" << i << "\n";
            }
            return;
        }
        else if (n == 'n' or n == 'N') return;
        else{
            cout << "Escolha invalida! Tente novamente!";
            sleep (1);
        }
    }
}*/

bool Menu:: inputTest(char choice ,vector<int> values) {
    if (cin.fail() || cin.peek() != '\n') {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Invalid input! Try again!" << endl;
        sleep(1);
        return false;
    }
    //binary_search(values.begin(),values.end(),choice);
    if (!binary_search(values.begin(),values.end(),choice)) {
        cout << "Invalid choice! Try again!" << endl;
        sleep(1);
        return false;
    }
    return true;
}