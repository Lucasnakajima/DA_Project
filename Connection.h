//
// Created by ianbe on 13/03/2023.
//

#ifndef PROJETO_CONNECTION_H
#define PROJETO_CONNECTION_H

#include "Station.h"
#include <string>

using namespace std;

/**

@brief The Connection class represents a connection between two stations in a transportation network.
*/
class Connection {
private:
    Station source; ///< The source station of the connection.
    Station destination; ///< The destination station of the connection.
    int capacity; ///< The maximum flow that can be passed through the connection.
    string service; ///< The name of the transportation service associated with the connection.
    int residual; ///< The remaining capacity of the connection.

public:
/**
* @brief Default constructor for the Connection class.
*
*/
    Connection();
/**
 * @brief Constructor for the Connection class.
 *
 * @param source The source station of the connection.
 * @param destination The destination station of the connection.
 * @param capacity The maximum flow that can be passed through the connection.
 * @param service The name of the transportation service associated with the connection.
 */
Connection(Station source, Station destination, int capacity, string service);

/**
 * @brief Overloaded assignment operator for the Connection class.
 *
 * @param other Pointer to the Connection object to be assigned.
 * @return Connection& The Connection object after assignment.
 */
Connection& operator=(Connection *other);

/**
 * @brief Getter function for the source station of the connection.
 *
 * @return Station The source station of the connection.
 */
Station getSource() const;

/**
 * @brief Setter function for the source station of the connection.
 *
 * @param newSource The new source station of the connection.
 */
void setSource(Station newSource);

/**
 * @brief Getter function for the destination station of the connection.
 *
 * @return Station The destination station of the connection.
 */
Station getDestination() const;

/**
 * @brief Setter function for the destination station of the connection.
 *
 * @param newDestination The new destination station of the connection.
 */
void setDestination(Station newDestination);

/**
 * @brief Getter function for the maximum flow that can be passed through the connection.
 *
 * @return int The maximum flow that can be passed through the connection.
 */
int getCapacity() const;

/**
 * @brief Setter function for the maximum flow that can be passed through the connection.
 *
 * @param newCapacity The new maximum flow that can be passed through the connection.
 */
void setCapacity(int newCapacity);

/**
 * @brief Getter function for the name of the transportation service associated with the connection.
 *
 * @return string The name of the transportation service associated with the connection.
 */
string getService() const;

/**
 * @brief Setter function for the name of the transportation service associated with the connection.
 *
 * @param newService The new name of the transportation service associated with the connection.
 */
void setService(string newService);

/**
 * @brief Getter function for the remaining capacity of the connection.
 *
 * @return int The remaining capacity of the connection.
 */
int getResidual();

/**
 * @brief Setter function for the remaining capacity of the connection.
 *
 * @param newresidual The new remaining capacity of the connection.
 */
void setResidual(int newresidual);



#endif //PROJETO_CONNECTION_H
