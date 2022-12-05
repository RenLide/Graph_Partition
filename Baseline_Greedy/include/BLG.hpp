//
//  BLG.hpp
//  Baseline_Greedy
//
//  Created by SleepyFish on 2022/11/24.
//

#ifndef BLG_hpp
#define BLG_hpp

#include "block.hpp"
#include "graph.hpp"
#include <queue>
#include <vector>
#include <fstream>
class BLG {
private:
    int CaculatePointEdges(int x, int y, int n);
    pair<int, float> CaculateKeyPoints(int n, vector<pair<int, int> > &kp, bool f);
    float _xmin, _xmax, _ymin, _ymax, re, random;
public:
    int num;
    Graph graph;
    vector<class Block> blocks;
    BLG(int k);
    BLG(int k, ifstream& infile);
    void CaculateBlockWeights(int n);
    void CaculateBlockEdges(int n);
    void DistributeBlocks(int n, int k);
    void OutputResult(ofstream& outfile);
    void PrintResult();
    pair<float, float> CaculateError();
};

#endif /* BLG_hpp */
