#include <unistd.h>
#include "Menu.h"
#include <algorithm>

using namespace std;
Menu::Menu() {
    run();
}

void Menu::run() {
    if(!(g.loadStations() && rc.loadStations())){
        cout << "Fail to open the Stations files!!";
        exit(0);
    }
    if(!(g.loadConnections() && rc.loadConnections())){
        cout << "Fail to open the Connections files!!";
        exit(0);
    }
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
                "||  Existent segment failures                     [33] |  Max number of trains that can arrive at a station    [43] ||\n"
                "||                                                     |                                                            ||\n"
                "||==================================================================================================================||\n"
                "||                                                   EXIT [0]                                                       ||\n"
                "||==================================================================================================================||\n"
                "Choose an option: ";
        vector<string> s;
        bool flag;
        int choice;
        vector<int> values = {0,11,12,21,22,23,31,32,33,41,42,43};
        cin >> choice;
        if(!inputTest(choice,values)) continue;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch(choice){
            case 11:
                s = stationsFetch();
                flag = validConnection(g, s[0], s[1]);
                cout << (flag);
                //TODO stationsByMunicipality
                break;
            case 12:
                //TODO stationsByDistricts
                break;
            case 21:
                maxBetweenTwoStations();
                break;
            case 22:
                //TODO pairsMostTrains();
                break;
            case 23:
                //TODO affectedStations();
                break;

            case 31:
                //TODO addSegFailure
                break;
            case 32:
                //TODO remSegFailure
                break;
            case 33:
                //TODO existentSegFailures
                break;
            case 41:
                g.topkbudgetMunicipality();
                g.topkbudgetDistrict();
                break;
            case 42:
                //TODO DistRegardignTranspNeeds
                break;
            case 43:
                //TODO maxNumberInStation
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

void Menu::maxBetweenTwoStations(){
    int choice;
    while(true) {
        cout << "||===============================================||\n"
                "|| Max number of trains that can travel:         ||\n"
                "|| In the full railway network               [1] ||\n"
                "|| With a minimum cost for the company       [2] ||\n"
                "|| In the network with reduced connectivity  [3] ||\n"
                "||===============================================||\n"
                "Choose an option: ";
        cin >> choice;
        vector<int> values = {1, 2, 3};
        if (!inputTest(choice, values)) continue;
        switch(choice){
            case 1:{
                //TODO maxFullRail();
                break;}
            case 2:
                //TODO maxMinumumCost();
                break;
            case 3:
                //TODO maxReducedConectivity();
                break;
            default:
                break;
        }
    }
}

vector<string> Menu:: stationsFetch(){
    string source, target;
        while(true) {
        cout << "Type the source:";
        getline(cin,source);
        if (!validStation(g, source)) {
            cout << "Invalid source! Make sure you typed correctly and try again!\n";
            sleep(1);
            cout << string(50,'\n');
            continue;
        }
        cout << "Type the target:";
        getline(cin,target);
        if (!validStation(g, target)) {
            cout << "Invalid target! Make sure you typed correctly and try again!\n";
            sleep(1);
            cout << string(50,'\n');
            continue;
        }
        if (source==target){
            cout << "You typed the same station twice! Try again!\n";
            sleep(1);
            cout << string(50,'\n');
            continue;
        }
        return {source, target};
    }
}

bool Menu:: validStation(Graph g, string station){
    if(g.getStations().find(station) == g.getStations().end()){
        return false;
    }
    return true;
}

bool Menu:: validConnection(Graph g, string s1, string s2){
    if(!(validStation(g,s1) && validStation(g,s2))){
        return false;
    }
    auto v= g.getTargets().find(s1)->first;
    //vector<Connection> v = g.getTargets().find(s1)->second;
//    for(auto i = v.begin(); i!=v.end(); i++){
//        if(i->getDestination().getName() == s2){
//            return true;
//        }
//    }
    return false;
}


bool Menu:: inputTest(char choice ,vector<int> values) {
    if (cin.fail() || cin.peek() != '\n') {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Invalid input! Try again!" << endl;
        sleep(1);
        return false;
    }
    if (!binary_search(values.begin(),values.end(),choice)) {
        cout << "Invalid choice! Try again!" << endl;
        sleep(1);
        return false;
    }
    return true;
}