//
// Created by ianbe on 13/03/2023.
//

#include "Connection.h"

Connection::Connection(Station* source, Station* destination, int capacity, string service) {
    this->source = source;
    this->destination = destination;
    this->capacity = capacity;
    this->service = service;
}

Station* Connection::getSource(){
    return source;
}

Station* Connection::getDestination(){
    return destination;
}

int Connection::getCapacity(){
    return capacity;
}

string Connection::getService() {
    return service;
}