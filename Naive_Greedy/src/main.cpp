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
    ifstream infile(argv[1], ios_base::in);
    NG ng(atoi(argv[3]), infile);
    infile.close();
//    ng.graph.PrintGraphWeight();
//    cout << endl;
    clock_t start, end;
    start = clock();
    ng.DistributeBlocks(0, atoi(argv[3]));
    end = clock();
    float sum = 0;
    pair<float, float> error;
    cout << "************* NG *************" << endl;
    for (int i = 0; i < ng.num; i++) {
        sum += ng.blocks[i].weights;
    }
    cout << "Total Weight : " << ng.graph.weights << endl;
    if (sum == ng.graph.weights) {
        ng.PrintResult();
        cout<< "Time : "<< double(end-start) / CLOCKS_PER_SEC * 1000 << " ms" << endl;
        error = ng.CaculateError();
        cout << "Weight Error : " << error.first << endl;
        cout << "Edge Error : " << error.second << endl;
        cout << "Distributed successfully!" << endl;
    }
    else cout << "Distributed ERROR!" << endl;
    cout << "******************************" << endl;
    ofstream outfile(argv[2], ios_base::out);
    ng.OutputResult(outfile);
    outfile.close();
    ofstream plotfile(argv[4], ios_base::out|ios::app);
    plotfile << error.first << " " << error.second << endl;
    plotfile.close();
    return 0;
}
