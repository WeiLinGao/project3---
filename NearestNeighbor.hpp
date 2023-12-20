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

void nearestNeighbor(std::string filename)
{
    std::clock_t start_time = std::clock();
    std::vector<Node> nodes = readFromFile(filename);
    if (nodes.empty()) {
        std::cerr << "Erro\n";
        return;
    }
    std::list<Node> visited;
    int totaldistance = 0;
    Node start = nodes.front();
    Node first = start;
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

    visited.push_back(first);
    totaldistance += start.distance(first);
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
