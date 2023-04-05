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

string Station::getName() const{
    return name;
}

string Station::getDistrict() const {
    return district;
}

string Station::getMunicipality() const {
    return municipality;
}

string Station::getTownship() const{
    return township;
}

string Station::getLine() const {
    return line;
}

Station::Station() {

}

Station::Station(string name) : name(name) {}
