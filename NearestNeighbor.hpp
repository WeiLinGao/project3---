#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <list>
#include <chrono>
#include <limits>
#include <algorithm>
#include <climits>
#include <fstream>
#include <sstream>
#ifndef NearestNeighbor_HPP
#define NearestNeighbor_HPP


/*
 * NearestNeighbor.hpp
 * Header file for the Nearest Neighbor algorithm implementation.
 */


class Node
{
public:
    int node;
    double x, y;

    // Constructor for the Node class.
    Node(int node_id, double x_coordinate, double y_coordinate)
    {
        node = node_id;
        x = x_coordinate;
        y = y_coordinate;
    }


    bool operator==(const Node& other) const
    {
        return node == other.node && x == other.x && y == other.y;
    }

    // Calculate the Euclidean distance between two nodes.
    int distance(const Node& other) const
    {
        double distance = sqrt(pow(x - other.x, 2) + pow(y - other.y, 2)); 
        return static_cast<int>(round(distance));
    }
};

/*
 * Read nodes' information from a file and return a vector of Node objects.
 
 * return: A vector of Node objects representing the nodes in the file.
 */
std::vector<Node> readFromFile(std::string filename)
{
    std::vector<Node> nodes;
    std::ifstream file(filename);

    if (file.is_open())
    {
        std::string line;
  

        while (std::getline(file, line))
        {
        
            std::istringstream iss(line);
            int node_id;
            double x, y;

            if (iss >> node_id >> x >> y)
            {
                nodes.emplace_back(node_id, x, y);
            }
     
        }

        file.close();
    }


    return nodes;
}

/*
  Implement the Nearest Neighbor algorithm to find a tour.
*/

void nearestNeighbor(std::string filename)
{
    std::clock_t start_time = std::clock();   // Record the start time 
    std::vector<Node> nodes = readFromFile(filename);  // Read nodes from the file into a vector
 
    std::list<Node> visited;                     // store list of visited node in 'visited'
    int totaldistance = 0;                        //inintiallize the distance to 0
    Node start = nodes.front();                   // Start with the first node.
    Node first = start;                           // Save the first node for calculating the final distance
    visited.push_back(start);                     // Mark the first node as visited
    nodes.erase(nodes.begin());                   // delete the first node from the nodes vector because it has been visisted.

    while (!nodes.empty())
    {
        int minDistance = INT_MAX;                     
        auto nearest = nodes.begin();             //Initialize the current nearest node to the first node in the nodes vector.


        for (auto i = nodes.begin(); i != nodes.end(); ++i)       // iterate through the nodes 
        {
            int d = start.distance(*i);                           // calcualte the distance between the first node and every other node 

            if (d < minDistance)                                  // Check if the calculated distance is smaller than the current minimum distance 
            {
                minDistance = d;                                  // update the minnimum distance 
                nearest = i;                                       // update the current nearest node 
            }
        }

        start = *nearest;                             // Move to the nearest node, so in the next loop it's calculating the minimum distance between this node and every other node remaining in the vector
        visited.push_back(start);                  // store the next shorest visisted node in visited vector
        totaldistance += minDistance;               // add the distance to total 

        nodes.erase(nearest);                       // Remove the nearest node from the remaining nodes.
    }

    visited.push_back(first);                       // push the first node from vector to the back of the vector, so it forms a complete tour
    totaldistance += start.distance(first);          //calculate the distance between the last visited node and the first node. 


    for (const auto& node : visited)
    {
        std::cout << node.node << " ";                    // Print out the tour
    }
    std::cout << std::endl;
    std::cout << "Total Distance: " << totaldistance << "\n";         //Print out the distance 
    std::clock_t end_time = std::clock();
    double elapsed_time = (end_time - start_time) / (double)CLOCKS_PER_SEC ;
    std::cout << "Time in ms: " << elapsed_time << "\n";           // Print out Time
}


#endif 
