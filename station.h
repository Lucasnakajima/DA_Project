//
// Created by Utilizador on 3/9/2023.
//

#ifndef PROJETO_STATION_H
#define PROJETO_STATION_H
#include <iostream>

using namespace std;

class station {
private:
    string name;
    string district;
    string municipality;
    string township;
    string line;


public:
    station(string name, string district, string municipality, string township, string line);

};


#endif //PROJETO_STATION_H
