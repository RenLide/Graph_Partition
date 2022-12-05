//
//  main.cpp
//  Naive_Greedy
//
//  Created by SleepyFish on 2022/11/9.
//

#include <iostream>
#include <time.h>
#include "global.hpp"
#include "NG.hpp"
using namespace std;
int main(int argc, const char * argv[]) {
//    NG ng(BLOCK_NUM);
    ifstream infile("/Users/renlide/Projects/Graph_Paritioning/data/data.dat", ios_base::in);
    NG ng(3, infile);
    infile.close();
//    ng.graph.PrintGraphWeight();
//    cout << endl;
    clock_t start,end;
    start = clock();
    ng.DistributedBlocks(0, 3);
    end = clock();
    float sum = 0;
    for (int i = 0; i < ng.num; i++) {
        sum += ng.blocks[i].weights;
    }
    cout << "Total Weight : " << ng.graph.weights << endl;
    if (sum == ng.graph.weights) {
        ng.PrintResult();
        cout<< "Time : "<< double(end-start) / CLOCKS_PER_SEC * 1000 << " ms" << endl;
        cout << "Distributed successfully!" << endl;
    }
    else cout << "Distributed ERROR!" << endl;
    ofstream outfile("/Users/renlide/Projects/Graph_Paritioning/result/result.dat", ios_base::out);
    ng.OutputResult(outfile);
    outfile.close();
    return 0;
}

