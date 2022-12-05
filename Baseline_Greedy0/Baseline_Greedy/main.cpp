//
//  main.cpp
//  Baseline_Greedy
//
//  Created by SleepyFish on 2022/11/24.
//

#include <iostream>
#include <time.h>
#include "point.hpp"
#include "global.hpp"
#include "graph.hpp"
#include "BLG.hpp"
using namespace std;
int main(int argc, const char * argv[]) {
//    BLG blg(BLOCK_NUM);
    ifstream infile(argv[1], ios_base::in);
    BLG blg(atoi(argv[3]), infile);
    infile.close();
//    blg.graph.PrintGraphWeight();
//    cout << endl;
//    blg.PrintScores();
//    while (!blg.score_queue.empty()) {
//        cout.precision(4);
//        cout << "(" << get<1>(blg.score_queue.top());
//        cout << "," << get<2>(blg.score_queue.top()) << ")";
//        cout << "[" << setw(5) << right << setfill(' ') << get<0>(blg.score_queue.top()) << "]";
//        cout << endl;
//        blg.score_queue.pop();
//    }
//    cout << blg.graph.weights << endl;
    clock_t start, end;
    start = clock();
    blg.DistributeBlocks(0, atoi(argv[3]));
    end = clock();
    float sum = 0;
    pair<float, float> error;
    cout << "************ BLG *************" << endl;
    for (int i = 0; i < blg.num; i++) {
        sum += blg.blocks[i].GetWeights();
    }
    cout << "Total Weight : " << blg.graph.weights << endl;
    if (sum == blg.graph.weights) {
        blg.PrintResult();
        cout << "Time : "<< double(end-start) / CLOCKS_PER_SEC * 1000 << " ms" << endl;
        error = blg.CaculateError();
        cout << "Weight Error : " << error.first << endl;
        cout << "Edge Error : " << error.second << endl;
        cout << "Distributed successfully!" << endl;
    }
    else cout << "Distributed ERROR!" << endl;
    cout << "******************************" << endl;
    ofstream outfile(argv[2], ios_base::out);
    blg.OutputResult(outfile);
    outfile.close();
    return 0;
}
