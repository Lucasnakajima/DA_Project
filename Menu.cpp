#include <unistd.h>
#include "Menu.h"
#include <locale>
#include <algorithm>
#include <string>

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
                "||  Stations by Districts                         [12] |                                                            ||\n"
                "||  Pairs of stations require the most trains     [13] |                                                            ||\n"
                "||==================================================================================================================||\n"
                "||                REDUCED CONNECTIVITY                 |                    TRANSPORTATION NEEDS                    ||\n"
                "||==================================================================================================================||\n"
                "||                                                     |                                                            ||\n"
                "||  Add a segment failure                         [31] |  Top-k municipalities regarding transportation needs  [41] ||\n"
                "||  Most affected stations                        [32] |  Top-k districts regarding transportation needs       [42] ||\n"
                "||                                                     |  Max number of trains that can arrive at a station    [43] ||\n"
                "||==================================================================================================================||\n"
                "||                                                   EXIT [0]                                                       ||\n"
                "||==================================================================================================================||\n"
                "Choose an option: ";
        string s;
        bool flag;
        int choice;
        wstring a;
        vector<int> values = {0,11,12,13,21,23,31,32,41,42,43};
        cin >> choice;
        if(!inputTest(choice,values)) continue;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch(choice){
            case 11:
                stationByMunicipality();
                break;
            case 12:
                stationByDistrict();
                break;
            case 21:
                maxBetweenTwoStations();
                break;
            case 13:
                pairsMostTrains();
                break;

            case 31:
                addSegFail(rc);
                break;
            case 32:
                g.MostAffectStations(rc);
                break;
            case 41:
                budgetMunicipalities();
                break;
            case 42:
                budgetDistricts();
                break;
            case 43:
                maxNumberInStation();
                break;
            case 0:
                cout << string(15,'\n');
                cout << "                                                  Thank you for using the railway network system!";
                cout << string(15,'\n');
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
                "|| Exit                                      [0] ||\n"
                "||===============================================||\n"
                "Choose an option: ";
        cin >> choice;
        vector<int> values = {0, 1, 2, 3};
        if (!inputTest(choice, values)) continue;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch(choice){
            case 0:
                return;
                break;
            case 1:
                maxFullRail();
                break;
            case 2:
                maxMinumumCost();
                break;
            case 3:
                maxReducedConectivity();
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

bool Menu:: validStation(Graph a, string station){
    cout << station << endl;
    return a.ValidStation(station);
}

bool Menu:: validConnection(Graph g, string s1, string s2){
    if(!(validStation(g,s1) && validStation(g,s2))){ //not really necessary
        return false;
    }
    //auto v= g.getTargets().find(s1)->first;
    vector<Connection> v = g.getTargets().find(s1)->second;
    for(auto i = v.begin(); i!=v.end(); i++){
        if(i->getDestination().getName() == s2){
            return true;
        }
    }
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

void Menu:: addSegFail(Graph& rc){
    vector<string> stationsNames = stationsFetch();
    if(!validConnection(rc,stationsNames[0],stationsNames[1])){
        cout << "This two stations are not adjacent or do not represent a valid connection in the Reduced Connectivity Railroad!\n Try again!\n";
        sleep(1);
    }
    else{
        rc.removeConnection(stationsNames[0], stationsNames[1]);
        cout << "Connection removed successfully!\n";
        system("pause");
    }
}

void Menu:: stationByMunicipality(){
    string s, l;
    int c=0;
    while(true) {
        cout << "Type the municipality:";
        getline(cin, s);
        l = s;
        transform(l.begin(), l.end(), l.begin(), ::toupper);
        for (auto i: g.getStations()) {
            if (i.second.getMunicipality() == l) {
                cout << i.second.getName() << "\n";
                c++;
            }
        }
        if (c == 0) {
            cout << "This municipality does not exist! Try again!";
            sleep(1);
            continue;
        }
        else{
            system("pause");
            return;
        }
    }
}

void Menu:: stationByDistrict(){
    string s, l;
    int c=0;
    while(true) {
        cout << "Type the district:";
        getline(cin, s);
        l = s;
        transform(l.begin(), l.end(), l.begin(), ::toupper);
        for (auto i: g.getStations()) {
            if (i.second.getDistrict() == s or i.second.getDistrict() == l) {
                cout << i.second.getName() << "\n";
                c++;
            }
        }
        if (c == 0) {
            cout << "This district does not exist! Try again!";
            sleep(1);
            continue;
        }
        else{
            system("pause");
            return;
        }
    }
}

void Menu:: maxNumberInStation(){
    string s;
    while(true) {
        cout << "Type the station:";
        getline(cin, s);
        cout << s <<endl;
        if (!validStation(g, s)) {
            cout << "Invalid station! Make sure you typed correctly and try again!\n";
            continue;
        }
        else{
        int m = g.maxTrainsAtStation(s);
        cout << "The maximum number of trains to arrive at " << s << " station is: " << m;
        system("pause");
        return;
        }
    }
}

void Menu:: pairsMostTrains(){
//    vector<string> s = stationsFetch();
//    vector<pair<string, string>> v = g.highestMaxFlowPairsPath(s[0], s[1]);
    vector<pair<string, string>> v = g.highestMaxFlowPairs();
//    cout << "The pair(s) of station(s) between " << s[0] << " station\n" << "and " << s[1] << " station are:\n";
    for(auto i : v){
        cout << i.first << "->" << i.second << "\n";
    }
    system("pause");
}

void Menu:: budgetMunicipalities(){
    auto v = g.topkbudgetMunicipality();
    int k;
    while(true) {
        cout << "Type the k value:";
        cin >> k;
        if (cin.fail() || cin.peek() != '\n') {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Invalid input! Try again!" << endl;
            sleep(1);
            continue;
        }
        else{
            cout << "Those are the top-" << k << " municipalities that need more budget:\n";
            for(int i=0; i<k and i<v.size(); i++){
                cout << v[i] << "\n";
            }
            sleep(1);
            system("pause");
            return;
        }
    }
}

void Menu:: budgetDistricts(){
    auto v = g.topkbudgetDistrict();
    int k;
    while(true) {
        cout << "Type the k value:";
        cin >> k;
        if (cin.fail() || cin.peek() != '\n') {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Invalid input! Try again!" << endl;
            sleep(1);
            continue;
        }
        else{
            cout << "Those are the top-" << k << " districts that need more budget:\n";
            for(int i=0; i<k and i<v.size(); i++){
                cout << v[i] << "\n";
            }
            sleep(1);
            system("pause");
            return;
        }
    }
}

void Menu:: maxFullRail(){
    vector<string> s = stationsFetch();
    cout << "The max number of trains tha can travel in the full railway network\n"
            "between " << s[0] << " station\n"
                                  "and " << s[1] << " station is:" << g.calculateMaxFlow(s[0], s[1]) << "\n";
    system("pause");
}

void Menu:: maxReducedConectivity(){
    vector<string> s = stationsFetch();
    cout << "The max number of trains tha can travel in the reduced connectivity network\n"
            "between " << s[0] << " station\n"
                                  "and " << s[1] << " station is:" << rc.calculateMaxFlow(s[0], s[1]) << "\n";
    system("pause");
}

void Menu:: maxMinumumCost(){
    vector<string> s = stationsFetch();
    auto m = g.calculateMinCostMaxFlow(s[0], s[1]);
    cout << "The max number of trains tha can travel in the full railway network,\n"
            "between " << s[0] << " station\n"
                                  "and " << s[1] << " station is:" << m.first << "\n"
                                                                                 "With a minimum cost for the company of:" << m.second << "\n";
    system("pause");
}