//
// Created by ianbe on 13/03/2023.
//

#ifndef PROJETO_CONNECTION_H
#define PROJETO_CONNECTION_H

#include "Station.h"
#include <string>

using namespace std;


/**
 * @brief The Connection class represents a connection between two stations in a transportation network.
 */
class Connection {
private:
    /// @brief The source station.
    Station source; 
    /// @brief The destination station.
    Station destination; 
    /// @brief The capacity of the connection.
    int capacity; 
    /// @brief The type of service provided by the connection.
    string service; 
    /// @brief The residual capacity of the connection.
    int residual; /// @brief The residual capacity of the connection.

public:

    /**
     * @brief Constructs an empty Connection object.
     */
    Connection();

    /**
     * @brief Constructs a Connection object.
     * @param source The source station.
     * @param destination The destination station.
     * @param capacity The capacity of the connection.
     * @param service The type of service provided by the connection.
     */
    Connection(Station source, Station destination, int capacity, string service);

    /**
     * @brief Assigns a Connection object to another Connection object.
     * @param other The Connection object to assign to.
     * @return A reference to the assigned Connection object.
     */
    Connection& operator=(Connection *other);

    /**
     * @brief Returns the source station of the connection.
     * @return The source station.
     */
    Station getSource() const;
    /**
     * @brief Sets the source station of the connection.
     * @param newSource The new source station.
     */
    void setSource(Station newSource);

    /**
     * @brief Returns the destination station of the connection.
     * @return The destination station.
     */
    Station getDestination() const;
    /**
     * @brief Sets the destination station of the connection.
     * @param newDestination The new destination station.
     */
    void setDestination(Station newDestination);

    /**
     * @brief Returns the capacity of the connection.
     * @return The capacity.
     */
    int getCapacity() const;
    void setCapacity(int newCapacity);

    /**
     * @brief Returns the type of service provided by the connection.
     * @return The service type.
     */
    string getService() const;
    /**
     * @brief Sets the type of service provided by the connection.
     * @param newService The new service type.
     */
    void setService(string newService);

    /**
     * @brief Returns the remaining capacity of the connection.
     * @return The remaining capacity.
     */
    int getResidual();

    /**
     * @brief Sets the remaining capacity of the connection.
     * @param newResidual The new remaining capacity.
     */
    void setResidual(int newResidual);

};


#endif //PROJETO_CONNECTION_H
