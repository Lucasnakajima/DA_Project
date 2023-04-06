//
// Created by Utilizador on 3/9/2023.
//

#ifndef PROJETO_GRAPH_H
#define PROJETO_GRAPH_H

#include <string>
#include <vector>
#include <unordered_map>
#include <limits>
#include <unordered_set>
#include <queue>
#include "Station.h"
#include "Connection.h"

using namespace std;

class Graph {

private:
    /// @brief A map of station names to station objects
    unordered_map<string, Station> stations; 
    /// @brief A map of station names to a vector of connections
    unordered_map<string, vector<Connection>> targets; 
    /// @brief A vector of connections
    vector<Connection> connections; 
    /// @brief A map of station names to their parent station names
    unordered_map<string, string> parent; 
    /// @brief A map of station names to a vector of pairs of station names and residual capacities
    unordered_map<string, vector<pair<string, int>>> residual; 

public:
    Graph();

    /**
     * @brief Loads station data from a CSV file into a graph object.
     * @return bool True if the file was successfully opened, false otherwise.
     */
    bool loadStations();

    /**
     * @brief Loads connections data from a CSV file into a graph object.
     * @return bool True if the file was successfully opened, false otherwise.
     */
    bool loadConnections();

    /**
     * @brief Get the Stations object
     * 
     * @return unordered_map<string, Station> 
     */
    unordered_map<string, Station> getStations();

    /**
     * @brief Get the Connections object
     * 
     * @return vector<Connection> 
     */
    vector<Connection> getConnections();

    /**
     * @brief Get the Targets object
     * 
     * @return unordered_map<string, vector<Connection>> 
     */
    unordered_map<string, vector<Connection>> getTargets();

    /**
     * @brief Performs breadth-first search to find the shortest path between the source and destination stations with available capacity.
     * @param source Source station name
     * @param destination Destination station name
     * @return True if a path with available capacity exists, false otherwise
     * Time Complexity: O(V+E)
     */
    bool bfs(string source, string destination);

    /**
     * @brief Get the Parent object 
     * 
     * @param source  Source station name 
     * @param destination  Destination station name
     * @param visited Visited stations
     * @return True if a path with available capacity exists, false otherwise
     * Time Complexity: O(V+E)
     */
    bool dfsHelper(const string &source, const string &destination, unordered_map<string, bool> &visited);

    /**
     * @brief Performs depth-first search to find if there is a path between the source and destination stations.
     * @param source Source station name
     * @param destination Destination station name
     * @return True if a path exists, false otherwise
     * Time Complexity: O(V+E)
     */
    bool dfs(string source, string destination);

    /**
     * @brief Performs Dijkstra's algorithm to find the shortest path between the source and destination stations based on service cost.
     * @param source Source station name
     * @param destination Destination station name
     * @return True if a path exists, false otherwise
     * Time Complexity: O(V^2)
     */
    bool dijkstra(string source, string destination);

    /**
     * @brief Get the Path object
     * 
     * @param source Source station name
     * @param destination Destination station name
     * @return vector<string> 
     * Time Complexity: O(V+E)
     */
    int findAugmentingPath(const string &source, const string &sink, int flow, unordered_map<string, bool> &visited);

    /**
     * @brief Calculates the maximum flow between the source and sink stations using the Edmonds-Karp algorithm.
     * @param source Source station name
     * @param sink Sink station name
     * @return The maximum flow value
     * Time Complexity: O(VE^2)
     */
    int calculateMaxFlow(string source, string sink);

    /**
     * @brief Calculates the minimum cost maximum flow between the source and sink stations using the Edmonds-Karp algorithm.
     * @param source Source station name
     * @param sink Sink station name
     * @return A pair containing the minimum cost and maximum flow values
     * Time Complexity: O(V^2 E^2)
     */
    vector<pair<string, string>> highestMaxFlowPairsPath(string source, string sink);

    /**
     * @brief Calculates the maximum number of trains that can be at a given station at the same time
     * @param stationName  Station name
     * @return int The maximum number of trains that can be at the station at the same time
     * Time Complexity: O(VE^2)
     */
    int maxTrainsAtStation(string stationName);

    /**
     * @brief Finds all the source stations in the graph.
     * @return A vector containing the names of all the source stations
     * Time Complexity: O(E)
     */
    vector<string> findSourceStations();

    /**
     * @brief Finds the pair(s) of stations with the highest maximum flow between them.
     * @return vector<pair<string, string>> A vector containing the pairs of stations with the highest maximum flow between them
     * Time Complexity: O(V^2 E^2)
     */
    vector<pair<string, string>> highestMaxFlowPairs();

    /**
     * @brief Updates the residual capacities of all connections in the graph.
     * @return None
     * Time Complexity: O(E)
     */
    void updateResidualConnections();

    /**
     * @brief Calculates the minimum-cost maximum flow in the graph using the successive shortest path algorithm.
     * @param source Source station name
     * @param destination Destination station name
     * @return A pair of integers representing the maximum flow and minimum cost for the given source and sink stations.
     * Time Complexity: O((V + E) log V)
     */
    pair<int, int> calculateMinCostMaxFlow(string source, string sink);

    /**
     * @brief alculates the maximum flow between a source and a sink station that belong to the same municipality.
     * @param source Source station name
     * @param destination Destination station name
     * @return An integer representing the maximum flow for the given source and sink stations that belong to the same municipality
     * Time Complexity: O(V^2 E^2)
     */
    int calculateMaxFlowMunicipality(string source, string sink);

    /**
     * @brief Breadth-first search algorithm to find a path between the source and destination stations, considering only connections within the same municipality.
     * @param source  The name of the source station.
     * @param destination The name of the destination station.
     * @return True if a path exists, false otherwise.
     *  Time Complexity: O(E), where E is the number of connections in the graph.
     */
    bool bfsMunicipality(string source, string destination);

    /**
     * @brief Finds the k municipalities with the highest budget allocated to transportation.
     * 
     * @return vector<string> A vector of strings containing the names of the top k municipalities.
     * Time Complexity: O(V^3)
     */
    vector<string> topkbudgetMunicipality();

    /**
     * @brief Calculates the maximum flow between a source and a sink station that belong to the same district.
     * @param source Source station name
     * @param destination Destination station name
     * @return An integer representing the maximum flow for the given source and sink stations that belong to the same district
     * Time Complexity: O(VE^2)
     */
    int calculateMaxFlowDistrict(string source, string sink);

    /**
     * @brief Breadth-first search algorithm to find a path between the source and destination stations, considering only connections within the same district.
     * @param source The name of the source station.
     * @param destination The name of the destination station.
     * @return True if a path exists, false otherwise.
     * Time Complexity: O(EV^2)
     */
    bool bfsDistrict(string source, string destination);

    /**
     * @brief Finds the maximum flow between each district and its stations, and then returns the top k districts with the highest maximum flow
     * @return vector<string> A vector of strings containing the names of the top k districts.
     * Time Complexity: O(EV^2)
     */
    vector<string> topkbudgetDistrict();

    //pair<int, int> calculateMinCostMaxFlow(string source, string sink);

    /**
     * @brief takes two station names as input, searches for connections between them in the graph and removes them
     * @param s1  station name
     * @param s2  station name
     * Time Complexity: O(E)
     */
    void removeConnection(string s1, string s2);

    /**
     * @brief Finds the stations that are most affected by a change in the network
     * @param s1  station name
     * Time Complexity: O(V^2 E^2)
     */
    vector<string> MostAffectStations(Graph rc);

    /**
     * @brief Checks if a station is valid
     * @param name station name
     * @return true if the station is valid, false otherwise 
     */
    bool ValidStation(string name);
};


#endif //PROJETO_GRAPH_H
