//
// Created by ianbe on 13/03/2023.
//

#ifndef PROJETO_CONNECTION_H
#define PROJETO_CONNECTION_H

#include "Station.h"
#include <string>

using namespace std;

class Connection {
private:
    Station source;
    Station destination;
    int capacity;
    string service;

public:
    Connection();

    Connection(Station source, Station destination, int capacity, string service);

    Connection& operator=(Connection *other);

    Station getSource();
    void setSource(Station newSource);

    Station getDestination();
    void setDestination(Station newDestination);

    int getCapacity();
    void setCapacity(int newCapacity);

    string getService();
    void setService(string newService);
};


#endif //PROJETO_CONNECTION_H
