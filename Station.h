//
// Created by Utilizador on 3/9/2023.
//

#ifndef PROJETO_STATION_H
#define PROJETO_STATION_H
#include <iostream>

using namespace std;

class Station {
private:
    string name;
    string district;
    string municipality;
    string township;
    string line;


public:
    Station(string name, string district, string municipality, string township, string line);

    string getName();
    string getDistrict();
    string getMunicipality();
    string getTownship();
    string getLine();
};


#endif //PROJETO_STATION_H
