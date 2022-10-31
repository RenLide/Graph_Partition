//
//  LDG.hpp
//  Linear_Deterministic_Greedy
//
//  Created by SleepyFish on 2022/10/26.
//

#ifndef LDG_hpp
#define LDG_hpp
#include "block.hpp"
#include "graph.hpp"
#include <cstdio>
#include <queue>
#include <fstream>
class LDG {
private:
    int CaculatePointEdges(int x, int y, int n);
    int CaculateNeighbors(int x, int y, int n);
    void LinearDeterministicGreedy(int x, int y);
    void BFS(int x, int y, int n);
public:
    int num; // block num
    vector<class Block> blocks;
    Graph graph;
    LDG(int k);
    void CaculateBlockWeights(int n);
    void CaculateBlockEdges(int n);
    void DistributeBlocks();
    void OutputResult(ofstream& outfile);
};
#endif /* LDG_hpp */
