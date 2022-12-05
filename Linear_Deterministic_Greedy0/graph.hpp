//
//  graph.hpp
//  Linear_Deterministic_Greedy
//
//  Created by SleepyFish on 2022/10/25.
//

#ifndef graph_hpp
#define graph_hpp
#include "global.hpp"
#include "block.hpp"
#include "point.hpp"
#include <vector>
#include <stdio.h>
#include <iomanip>
#include <random>
#include <fstream>
class Graph {
public:
    int row;
    int column;
    float weights;
    vector<class Point> grid;
    Graph (int r = (int)((Y_MAX - Y_MIN) / RE), int col = (int)((X_MAX - X_MIN) / RE));
    void InitGraph();
    void InitGraph(ifstream& infile);
    void PrintGraphWeight();
};
#endif /* graph_hpp */
