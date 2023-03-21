//
// Created by Utilizador on 3/9/2023.
//

#include "Station.h"

Station::Station(string name, string district, string municipality, string township, string line) {
    this->name = name;
    this->district=district;
    this->municipality = municipality;
    this->township = township;
    this->line = line;
}

string Station::getName() {
    return name;
}

string Station::getDistrict() {
    return district;
}

string Station::getMunicipality() {
    return municipality;
}

string Station::getTownship() {
    return township;
}

string Station::getLine() {
    return line;
}

Station::Station() {

}
