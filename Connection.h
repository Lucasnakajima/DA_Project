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
    int residual;

public:
    Connection();

    Connection(Station source, Station destination, int capacity, string service);

    Connection& operator=(Connection *other);

    Station getSource() const;
    void setSource(Station newSource);

    Station getDestination() const;
    void setDestination(Station newDestination);

    int getCapacity() const;
    void setCapacity(int newCapacity);

    string getService() const;
    void setService(string newService);

    int getResidual();
    void setResidual(int newresidual);
};


#endif //PROJETO_CONNECTION_H
