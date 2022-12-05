//
//  main.cpp
//  Linear_Deterministic_Greedy
//
//  Created by SleepyFish on 2022/10/25.
//

#include <iostream>
#include <time.h>
#include "point.hpp"
#include "global.hpp"
#include "graph.hpp"
#include "LDG.hpp"
using namespace std;
int main(int argc, const char * argv[]) {
//    LDG ldg(BLOCK_NUM);
    ifstream infile(argv[1], ios_base::in);
    LDG ldg(atoi(argv[3]), infile);
    infile.close();
//    ldg.graph.PrintGraphWeight();
//    cout << endl;
//    ldg.PrintScores();
//    while (!ldg.score_queue.empty()) {
//        cout.precision(4);
//        cout << "(" << get<1>(ldg.score_queue.top());
//        cout << "," << get<2>(ldg.score_queue.top()) << ")";
//        cout << "[" << setw(5) << right << setfill(' ') << get<0>(ldg.score_queue.top()) << "]";
//        cout << endl;
//        ldg.score_queue.pop();
//    }
//    cout << ldg.graph.weights << endl;
    clock_t start, end;
    start = clock();
    ldg.DistributeBlocks();
    end = clock();
    float sum = 0;
    pair<float, float> error;
    cout << "************ LDG *************" << endl;
    for (int i = 0; i < ldg.num; i++) {
        sum += ldg.blocks[i].GetWeights();
    }
    cout << "Total Weight : " << ldg.graph.weights << endl;
    if (sum == ldg.graph.weights) {
        ldg.PrintResult();
        cout << "Time : "<< double(end-start) / CLOCKS_PER_SEC * 1000 << " ms" << endl;
        error = ldg.CaculateError();
        cout << "Weight Error : " << error.first << endl;
        cout << "Edge Error : " << error.second << endl;
        cout << "Distributed successfully!" << endl;
    }
    else cout << "Distributed ERROR!" << endl;
    cout << "******************************" << endl;
    ofstream outfile(argv[2], ios_base::out);
    ldg.OutputResult(outfile);
    outfile.close();
    ofstream plotfile(argv[4], ios_base::out|ios::app);
    plotfile << error.first << " " << error.second << endl;
    plotfile.close();
    return 0;
}
