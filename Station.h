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
    Station();
    Station(string name);
    Station(string name, string district, string municipality, string township, string line);

    string getName() const;
    string getDistrict() const;
    string getMunicipality() const;
    string getTownship() const;
    string getLine() const;
};


#endif //PROJETO_STATION_H
