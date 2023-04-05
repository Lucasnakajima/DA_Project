//
// Created by Utilizador on 3/9/2023.
//

#ifndef PROJETO_STATION_H
#define PROJETO_STATION_H
#include <iostream>

using namespace std;

/**
 * @brief The Station class represents a station in the transportation network.
 */
class Station {
private:

    string name;        /**< The name of the station. */
    string district;    /**< The district where the station is located. */
    string municipality;/**< The municipality where the station is located. */
    string township;    /**< The township where the station is located. */
    string line;        /**< The line where the station is located. */

public:
    /**
     * @brief Default constructor for the Station class.
     */
    Station();

    /**
     * @brief Constructor for the Station class that sets the name of the station.
     * @param name The name of the station.
     */
    Station(string name);

    /**
     * @brief Constructor for the Station class that sets the name, district, municipality, township, and line of the station.
     * @param name The name of the station.
     * @param district The district where the station is located.
     * @param municipality The municipality where the station is located.
     * @param township The township where the station is located.
     * @param line The line where the station is located.
     */
    Station(string name, string district, string municipality, string township, string line);

    /**
     * @brief Gets the name of the station.
     * @return The name of the station.
     */
    string getName() const;

    /**
     * @brief Gets the district where the station is located.
     * @return The district where the station is located.
     */
    string getDistrict() const;

    /**
     * @brief Gets the municipality where the station is located.
     * @return The municipality where the station is located.
     */
    string getMunicipality() const;

    /**
     * @brief Gets the township where the station is located.
     * @return The township where the station is located.
     */
    string getTownship() const;

    /**
     * @brief Gets the line where the station is located.
     * @return The line where the station is located.
     */
    string getLine() const;
};



#endif //PROJETO_STATION_H
