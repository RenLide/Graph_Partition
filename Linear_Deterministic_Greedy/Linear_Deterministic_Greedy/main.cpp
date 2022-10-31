//
//  main.cpp
//  Linear_Deterministic_Greedy
//
//  Created by SleepyFish on 2022/10/25.
//

#include <iostream>
#include "point.hpp"
#include "global.hpp"
#include "graph.hpp"
#include "LDG.hpp"
using namespace std;
int main(int argc, const char * argv[]) {
    LDG ldg(BLOCK_NUM);
    ldg.DistributeBlocks();
//    ldg.graph.PrintGraphWeight();
    cout << ldg.graph.weights << endl;
    ofstream outfile("/Users/renlide/Projects/Graph_Paritioning/result.dat", ios_base::out);
    ldg.OutputResult(outfile);
    outfile.close();
    return 0;
}
