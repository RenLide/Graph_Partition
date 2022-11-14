//
//  main.cpp
//  Naive_Greedy
//
//  Created by SleepyFish on 2022/11/9.
//

#include <iostream>
#include "global.hpp"
#include "NG.hpp"
using namespace std;
int main(int argc, const char * argv[]) {
//    NG ng(BLOCK_NUM);
    ifstream infile("/Users/renlide/Projects/Graph_Paritioning/result/result.dat", ios_base::in);
    NG ng(BLOCK_NUM, infile);
    infile.close();
    ng.graph.PrintGraphWeight();
    cout << endl;
    ng.DistribitedBlocks(0, BLOCK_NUM, true);
    ofstream outfile("/Users/renlide/Projects/Graph_Paritioning/result/result.dat", ios_base::out);
    ng.OutputResult(outfile);
    outfile.close();
    return 0;
}
