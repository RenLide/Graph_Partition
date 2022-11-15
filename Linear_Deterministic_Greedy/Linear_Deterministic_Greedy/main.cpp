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
//    ifstream infile("/Users/renlide/Projects/Graph_Paritioning/result/result.dat", ios_base::in);
//    LDG ldg(BLOCK_NUM, infile);
//    infile.close();
    ldg.graph.PrintGraphWeight();
    cout << endl;
    ldg.PrintScores();
    while (!ldg.score_queue.empty()) {
        cout.precision(4);
        cout << "(" << get<1>(ldg.score_queue.top());
        cout << "," << get<2>(ldg.score_queue.top()) << ")";
        cout << "[" << setw(5) << right << setfill(' ') << get<0>(ldg.score_queue.top()) << "]";
        cout << endl;
        ldg.score_queue.pop();
    }
    cout << ldg.graph.weights << endl;
//    ldg.DistributeBlocks();
    ofstream outfile("/Users/renlide/Projects/Graph_Paritioning/result/result.dat", ios_base::out);
    ldg.OutputResult(outfile);
    outfile.close();
    return 0;
}
