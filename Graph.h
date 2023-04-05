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
    unordered_map<string, Station> stations;
    unordered_map<string, vector<Connection>> targets;
    vector<Connection> connections;
    unordered_map<string, string> parent;
    unordered_map<string, vector<pair<string, int>>> residual; // Add an adjacency matrix

public:
    Graph();

    /**
     @brief Loads the station information from a CSV file

     This function reads in station information from a CSV file and populates the stations unordered_map with Station objects.

     @return true if the file was successfully opened and the data was loaded, false otherwise

     @complexity O(n), where n is the number of stations in the CSV file
 */
    bool loadStations();

    /**
    @brief Loads the connection information from a CSV file

    This function reads in connection information from a CSV file and populates the connections vector and targets unordered_map with Connection objects.

    @return true if the file was successfully opened and the data was loaded, false otherwise

    @complexity O(m), where m is the number of connections in the CSV file
 */
    bool loadConnections();

    /**
    @brief Returns the stations unordered_map

    This function returns the unordered_map of stations, with the station name as the key and the Station object as the value.

    @return the stations unordered_map

    @complexity O(1)
 */
    unordered_map<string, Station> getStations();

    /**
    @brief Returns the connections vector

    This function returns the vector of connections.

    @return the connections vector

    @complexity O(1)
 */
    vector<Connection> getConnections();

    /**
    @brief Returns the targets unordered_map

    This function returns the unordered_map of targets, with the station name as the key and a vector of Connection objects as the value.

    @return the targets unordered_map

    @complexity O(1)
 */
    unordered_map<string, vector<Connection>> getTargets();

    /**
    @brief Performs a depth-first search from the source station to the destination station

    This function performs a depth-first search from the source station to the destination station using a recursive helper function.

    @param source the name of the source station
    @param destination the name of the destination station

    @return true if there exists a path from the source station to the destination station, false otherwise

    @complexity O(m), where m is the number of connections in the graph
 */
    bool bfs(string source, string destination);

    /**
    @brief Recursive helper function for depth-first search

    This function is a recursive helper function for the dfs() function. It performs a depth-first search from the source station to the destination station.

    @param source the name of the source station
    @param destination the name of the destination station
    @param visited an unordered_map of visited stations

    @return true if there exists a path from the source station to the destination station, false otherwise

    @complexity O(m), where m is the number of connections in the graph
 */
    bool dfsHelper(const string &source, const string &destination, unordered_map<string, bool> &visited);

    /**
    @brief Performs a breadth-first search from the source station to the destination station

    This function performs a breadth-first search from the source station to the destination station using a queue.

    @param source the name of the source station
    @param destination the name of the destination station

    @return true if there exists a path from the source station to the destination station, false otherwise

    @complexity O(m + n log n), where m is the number of connections in the graph and n is the number of stations in the graph
 */
    bool dfs(string source, string destination);

    /**
    @brief Calculates the shortest path between two nodes using Dijkstra's algorithm.
    @param source The starting node.
    @param destination The target node.
    @return A boolean indicating if a path was found.
    @complexity O(E*log(V)), where E is the number of edges and V is the number of vertices.
*/
    bool dijkstra(string source, string destination);

    /**
    @brief Finds an augmenting path in the residual graph using DFS.
    @param source The source node.
    @param sink The sink node.
    @param flow The flow so far in the augmenting path.
    @param visited A map of visited nodes.
    @return The flow of the augmenting path.
    @complexity O(E*log(V)), where E is the number of edges and V is the number of vertices.
*/
    int findAugmentingPath(const string& source, const string& sink, int flow, unordered_map<string, bool>& visited);

    /**
    @brief Calculates the maximum flow in the graph using the Edmonds-Karp algorithm.
    @param source The source node.
    @param sink The sink node.
    @return The maximum flow.
    @complexity O(V*E^2), where E is the number of edges and V is the number of vertices.
*/
    int calculateMaxFlow(string source, string sink);

    /**
    @brief Finds all pairs of stations with the highest maximum flow from a given source station.
    @param source The source station.
    @param sink The sink station.
    @return A vector of station pairs.
    @complexity O(V^2*E^2), where E is the number of edges and V is the number of vertices.
*/
    vector<pair<string, string>> highestMaxFlowPairsPath(string source, string sink);

    /**
    @brief Calculates the maximum number of trains that can be parked at a station.
    @param station The station.
    @return The maximum number of trains that can be parked.
    @complexity O(V*E^2), where E is the number of edges and V is the number of vertices.
*/
    int maxTrainsAtStation(string stationName);

    /**
    @brief Finds all source stations in the graph.
    @return A vector of source stations.
    @complexity O(V+E), where E is the number of edges and V is the number of vertices.
*/
    vector<string> findSourceStations();

    /**
    @brief Finds all pairs of stations with the highest maximum flow.
    @return A vector of station pairs.
    @complexity O(V^3*E^2), where E is the number of edges and V is the number of vertices.
*/
    vector<pair<string, string>> highestMaxFlowPairs();

    /**
    @brief Updates the residual capacities of the connections in the graph.
    @complexity O(E), where E is the number of edges in the graph.
*/
    void updateResidualConnections();

    /**
    @brief Calculates the minimum cost maximum flow from a source to a sink using Dijkstra's algorithm and updates the residual capacities of the graph.
    @param source The name of the source node.
    @param sink The name of the sink node.
    @return A pair of integers representing the maximum flow and minimum cost of the graph.
    @note The time complexity of this function is O(E^2 * log(V)), where E is the number of edges and V is the number of vertices in the graph.
 */
    pair<int, int> calculateMinCostMaxFlow(string source, string sink);


    /**
    @brief Calculates the maximum flow that can be sent from a source to a sink using the Ford-Fulkerson algorithm, considering only nodes that belong to the same municipality as the source node.

    @param source The name of the source node.
    @param sink The name of the sink node.
    @return The maximum flow that can be sent from the source to the sink, considering only nodes that belong to the same municipality as the source node.
    @note The time complexity of this function is O(E * F), where E is the number of edges and F is the maximum flow in the graph.
 */
    int calculateMaxFlowMunicipality(string source, string sink);


    /**
    @brief Performs a breadth-first search (BFS) on the graph from a source to a destination, visiting only nodes that belong to the same municipality as the source node.

    @param source The name of the source node.
    @param destination The name of the destination node.
    @return true if a path exists between the source and destination nodes that visits only nodes in the same municipality, false otherwise.
    @note The time complexity of this function is O(E), where E is the number of edges in the graph.
 */
    bool bfsMunicipality(string source, string destination);


    /**
    @brief Returns the top k municipalities with the highest maximum flow that can be sent from a station in that municipality to any other station within the same municipality.
    @return A vector of strings containing the names of the top k municipalities with the highest maximum flow.
    @note The time complexity of this function is O(E * V * F * log(V)), where E is the number of edges, V is the number of vertices, and F is the maximum flow in the graph.
 */
    vector<string> topkbudgetMunicipality();


    int calculateMaxFlowDistrict(string source, string sink);

    /**
    @brief Performs a breadth-first search (BFS) on the graph from a source to a destination, visiting only nodes that belong to the same district as the source node.

    @param source The name of the source node.
    @param destination The name of the destination node.
    @return true if a path exists between the source and destination nodes that visits only nodes in the same district, false otherwise.
    @note The time complexity of this function is O(E), where E is the number of edges in the graph.
 */
    bool bfsDistrict(string source, string destination);

/**
    @brief Finds the district(s) with the highest maximum flow capacity between its stations.
    @return A vector of the name(s) of the district(s) with the highest maximum flow capacity.
    @complexity O(E * V^2), where E is the number of edges and V is the number of vertices (stations)
 */
    vector<string> topkbudgetDistrict();

    /**
    @brief Removes the connection between two stations.
    @param s1 The name of the first station.
    @param s2 The name of the second station.
    @complexity O(E), where E is the number of edges
 */
    void removeConnection(string s1, string s2);
};


#endif //PROJETO_GRAPH_H
