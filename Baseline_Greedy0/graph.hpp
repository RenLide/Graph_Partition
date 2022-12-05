//
//  graph.hpp
//  Baseline_Greedy
//
//  Created by SleepyFish on 2022/11/24.
//

#ifndef graph_hpp
#define graph_hpp

#include "global.hpp"
#include "point.hpp"
#include <vector>
#include <iomanip>
#include <random>
#include <fstream>
#include <iostream>
using namespace std;
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
