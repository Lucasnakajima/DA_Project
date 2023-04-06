//
// Created by Utilizador on 3/9/2023.
//

#ifndef PROJETO_STATION_H
#define PROJETO_STATION_H
#include <iostream>

using namespace std;

class Station {
private:
    /// @brief The name of the station.
    string name;
    /// @brief The district where the station is located.
    string district;
    /// @brief The municipality where the station is located.
    string municipality;
    /// @brief The township where the station is located.
    string township;
    /// @brief The line to which the station belongs.
    string line;


public:
    /**
     * @brief Constructs a Station object.
     * @param name The name of the station.
     * @param district The district where the station is located.
     * @param municipality The municipality where the station is located.
     * @param township The township where the station is located.
     * @param line The line to which the station belongs.
     */
    Station(string name, string district, string municipality, string township, string line);

    /**
     * @brief Constructs an empty Station object.
     */
    Station();

    /**
     * @brief Constructs a Station object with a given name.
     * @param name The name of the station.
     */
    Station(string name);

    /**
     * @brief Returns the name of the station.
     * @return The name.
     */
    string getName() const;

    /**
     * @brief Returns the district where the station is located.
     * @return The district.
     */
    string getDistrict() const;

    /**
     * @brief Returns the municipality where the station is located.
     * @return The municipality.
     */
    string getMunicipality() const;

    /**
     * @brief Returns the township where the station is located.
     * @return The township.
     */
    string getTownship() const;

    /**
     * @brief Returns the line to which the station belongs.
     * @return The line.
     */
    string getLine() const;
};


#endif //PROJETO_STATION_H
