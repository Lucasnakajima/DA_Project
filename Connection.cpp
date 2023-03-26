//
// Created by ianbe on 13/03/2023.
//

#include "Connection.h"

Connection::Connection(Station source, Station destination, int capacity, string service) {
    this->source = source;
    this->destination = destination;
    this->capacity = capacity;
    this->service = service;
}

Station Connection::getSource() const{
    return source;
}

Station Connection::getDestination() const{
    return destination;
}

int Connection::getCapacity() const{
    return capacity;
}

string Connection::getService() const{
    return service;
}

Connection::Connection() {
    Station a;
    Station b;
    this->source = a;
    this->destination = b;
    this->capacity = 0;
    this->service = "";
}

Connection &Connection::operator=(Connection *other) {
    this->source = other->getSource();
    this->destination = other->destination;
    this->capacity = other->getCapacity();
    this->service = other->getService();
    return *this;
}

void Connection::setSource(Station newSource) {
    source = newSource;
}

void Connection::setDestination(Station newDestination) {
    destination = newDestination;
}

void Connection::setCapacity(int newCapacity) {
    capacity = newCapacity;
}

void Connection::setService(string newService) {
    service = newService;
}
