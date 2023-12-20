#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <list>
#include <chrono>
#include <limits>
#include <algorithm>
#include <climits>
#ifndef NearestNeighbor_HPP
#define NearestNeighbor_HPP

class Node
{
public:
    int node;
    double x, y;

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

    int distance(const Node& other) const
    {
        double distance = sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
        return static_cast<int>(round(distance));
    }
};

void nearestNeighbor(std::vector<Node>& nodes)
{
    std::clock_t start_time = std::clock();
    
    std::list<Node> visited;
    int totaldistance = 0;
    Node start= nodes.front();
    Node last = start;
    visited.push_back(start);
    nodes.erase(nodes.begin());

    while (!nodes.empty())
    {
        int minDistance = INT_MAX;
        auto nearest = nodes.begin();

        for (auto i = nodes.begin(); i != nodes.end(); ++i)
        {
            int d = start.distance(*i);

            if (d < minDistance)
            {
                minDistance = d;
                nearest = i;
            }
        }

        start = *nearest;
        visited.push_back(start);
        totaldistance += minDistance;

        nodes.erase(nearest);
    }
    totaldistance += last.distance(visited.front());
   
    for (const auto& node : visited)
    {
        std::cout << node.node << " ";
    }
    std::cout << std::endl;
    std::cout << "Total Distance: " << totaldistance << "\n";
    std::clock_t end_time = std::clock();
    double elapsed_time = (end_time - start_time) / (double)CLOCKS_PER_SEC * 1000;
    std::cout << "Time in ms: " << elapsed_time << "\n";
}



#endif 
