//
//  NG.hpp
//  Naive_Greedy
//
//  Created by SleepyFish on 2022/11/9.
//

#ifndef NG_hpp
#define NG_hpp
#include "block.hpp"
#include "graph.hpp"
#include <queue>
#include <vector>
#include <fstream>
class NG {
private:
    int CaculatePointEdges(int x, int y, int n);
    pair<int, float> CaculateKeyPoints(int n, vector<pair<int, int> > &kp, bool f);
    float _xmin, _xmax, _ymin, _ymax, re, random;
public:
    int num;
    Graph graph;
    vector<class Block> blocks;
    NG(int k);
    NG(int k, ifstream& infile);
    void CaculateBlockWeights(int n);
    void CaculateBlockEdges(int n);
    void DistributedBlocks(int n, int k);
    void OutputResult(ofstream& outfile);
    void PrintResult();
};
#endif /* NG_hpp */
