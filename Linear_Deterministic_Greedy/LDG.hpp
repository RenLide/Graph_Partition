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
    void CaculateScores();
    int CaculatePointEdges(int x, int y, int n);
    int CaculateNeighbors(int x, int y, int n);
    bool LinearDeterministicGreedy(int x, int y);
    void BFS(int x, int y, int n);
    bool ScoreFirstSearch(int x, int y, int n);
public:
    int num; // block num
    vector<class Block> blocks;
    vector<float> scores;
    priority_queue<tuple<float, int, int> > score_queue;
    set<pair<int, int> > edge_points;
    Graph graph;
    LDG(int k);
    LDG(int k, ifstream& infile);
    void CaculateBlockWeights(int n);
    void CaculateBlockEdges(int n);
    void DistributeBlocks();
    void OutputResult(ofstream& outfile);
    void PrintScores();
};
#endif /* LDG_hpp */
