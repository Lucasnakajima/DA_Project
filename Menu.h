#ifndef AIRTRANSPORT_MENU_H
#define AIRTRANSPORT_MENU_H
#include "Graph.h"
#include <stdlib.h>
///Classe para o Menu.
///
///Um menu apenas apresenta as opcoes.
class Menu {
private:
    /// @brief Graph for the original railroad
    Graph g; //Graph for the original railroad
    /// @brief Graph for the reduced connectivity
    Graph rc; //Graph for reduced connectivity
public:
     /**
     * @brief Constructs a Menu object.
     */
    Menu();

    /**
     * @brief Runs the menu.
     */
    void run();

    /**
     * @brief Computes the maximum number of trains that can travel between two stations.
     */
    void maxBetweenTwoStations();

    /**
     * @brief Tests whether the input is valid.
     * @param choice The user's choice.
     * @param values A vector containing the values associated with the user's choice.
     * @return True if the input is valid, false otherwise.
     */
    bool inputTest(char choice, std::vector<int> values);

    /**
     * @brief Fetches the names of all the stations in the transportation network.
     * @return A vector containing the names of all the stations.
     */
    std::vector<std::string> stationsFetch();

    /**
     * @brief Tests whether a station is valid.
     * @param a The graph containing the station.
     * @param station The name of the station.
     * @return True if the station is valid, false otherwise.
     */
    bool validStation(Graph a, std::string station);

    /**
     * @brief Tests whether a connection between two stations is valid.
     * @param g The graph containing the connection.
     * @param s1 The name of the first station.
     * @param s2 The name of the second station.
     * @return True if the connection is valid, false otherwise.
     */
    bool validConnection(Graph g, std::string s1, std::string s2);

    /**
     * @brief Adds a segment to the reduced connectivity graph, and prints an error message if the segment cannot be added.
     * @param rc The reduced connectivity graph.
     */
    void addSegFail(Graph& rc);

    /**
     * @brief Prints the stations in each municipality in alphabetical order.
     */
    void stationByMunicipality();

    /**
     * @brief Prints the stations in each district in alphabetical order.
     */
    void stationByDistrict();

    /**
     * @brief Workflow to get the station with the maximum number of passengers.
     */
    void maxNumberInStation();

    /**
     * @brief Workflow to get the pair of stations with the most trains travelling between them.
     */
    void pairsMostTrains();

    /**
     * @brief Workflow to get the total budget for each municipality.
     */
    void budgetMunicipalities();

    /**
     * @brief Workflow to get the total budget for each district.
     */
    void budgetDistricts();

    /**
     * @brief Workflow to get the maximum number of passengers that can travel along the entire rail network.
     */
    void maxFullRail();

    /**
     * @brief Workflow to get the maximum number of passengers that can travel along the reduced connectivity rail network.
     */
    void maxReducedConectivity();

    /**
     * @brief Workflow to get the minimum cost to connect all the stations in the transportation network.
     */
    void maxMinumumCost();

    /**
     * @brief Workflow to get the most affected when using the reduced connectivity rail network.
     */
    void Mostafffected();


    void pause();
};


#endif //AIRTRANSPORT_MENU_H