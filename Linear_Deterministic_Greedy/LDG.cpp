//
//  LDG.cpp
//  Linear_Deterministic_Greedy
//
//  Created by SleepyFish on 2022/10/26.
//

#include "LDG.hpp"
LDG::LDG(int k) {
    this->num = k;
    blocks.resize(k);
    for (int i = 0; i < k; i++) {
        blocks[i].SetWeights(0);
    }
    graph.InitGraph();
}

int LDG::CaculatePointEdges(int x, int y, int n) {
    int edges = 0;
    pair<int, int> up = pair<int, int>(x, y + 1);
    pair<int, int> down = pair<int, int>(x, y - 1);
    pair<int, int> left = pair<int, int>(x - 1, y);
    pair<int, int> right = pair<int, int>(x + 1, y);
    if (blocks[n].points.find(up) == blocks[n].points.end() && up.second < graph.row) edges++;
    if (blocks[n].points.find(down) == blocks[n].points.end() && down.second >= 0) edges++;
    if (blocks[n].points.find(left) == blocks[n].points.end() && left.first >= 0) edges++;
    if (blocks[n].points.find(right) == blocks[n].points.end() && right.first < graph.column) edges++;
    return edges;
}

int LDG::CaculateNeighbors(int x, int y, int n) {
    int neighbors = 0;
    pair<int, int> up = pair<int, int>(x, y + 1);
    pair<int, int> down = pair<int, int>(x, y - 1);
    pair<int, int> left = pair<int, int>(x - 1, y);
    pair<int, int> right = pair<int, int>(x + 1, y);
    if (blocks[n].points.find(up) != blocks[n].points.end() && up.second < graph.row) neighbors++;
    if (blocks[n].points.find(down) != blocks[n].points.end() && down.second >= 0) neighbors++;
    if (blocks[n].points.find(left) != blocks[n].points.end() && left.first >= 0) neighbors++;
    if (blocks[n].points.find(right) != blocks[n].points.end() && right.first < graph.column) neighbors++;
    return neighbors;
}

void LDG::LinearDeterministicGreedy(int x, int y) {
    int bnum = -1; // record the block with max score
    float score_max = -1; // record the max score
    float score;  // record current score
    for (int i = 0; i < num; i++) {
        score = CaculateNeighbors(x, y, i) * (1 - blocks[i].GetWeights() / graph.weights);
        if (score > score_max && blocks[i].GetWeights() < (1 + TOL) * graph.weights / num) {
            score_max = score;
            bnum = i;
        }
    }
    if (bnum == -1){
        for (int i = 0; i < num; i++) {
            if (blocks[i].GetWeights() <(1 + TOL) * graph.weights / num) bnum = i;
        }
    }
    blocks[bnum].AddPoint(pair<int, int>(x, y));
    graph.grid[y * graph.column + x].SetF(bnum);
    blocks[bnum].SetWeights(blocks[bnum].GetWeights() + graph.grid[y * graph.column + x].GetW());
}

void LDG::BFS(int x, int y, int n) {
    queue<pair<int, int> > seq;
    pair<int, int> point, up, down, left, right;
    seq.push(pair<int, int>(x, y));
    graph.grid[y * graph.column + x].SetF(n);
    while (!seq.empty()) {
        point = seq.front();
        up = pair<int, int>(point.first, point.second + 1);
        down = pair<int, int>(point.first, point.second - 1);
        left = pair<int, int>(point.first - 1, point.second);
        right = pair<int, int>(point.first + 1, point.second);
        if (blocks[n].points.find(up) == blocks[n].points.end() && up.second < graph.row \
            && graph.grid[up.second * graph.column + up.first].GetF() == -1) {
            seq.push(up);
            graph.grid[up.second * graph.column + up.first].SetF(n);
        }
        if (blocks[n].points.find(down) == blocks[n].points.end() && down.second >= 0 \
            && graph.grid[down.second * graph.column + down.first].GetF() == -1) {
            seq.push(down);
            graph.grid[down.second * graph.column + down.first].SetF(n);
        }
        if (blocks[n].points.find(left) == blocks[n].points.end() && left.first >= 0 \
            && graph.grid[left.second * graph.column + left.first].GetF() == -1) {
            seq.push(left);
            graph.grid[left.second * graph.column + left.first].SetF(n);
        }
        if (blocks[n].points.find(right) == blocks[n].points.end() && right.first < graph.column \
            && graph.grid[right.second * graph.column + right.first].GetF() == -1) {
            seq.push(right);
            graph.grid[right.second * graph.column + right.first].SetF(n);
        }
        if (blocks[n].GetWeights() > BFS_LOW * graph.weights / num) break;
        blocks[n].AddPoint(point);
        blocks[n].SetWeights(blocks[n].GetWeights() + graph.grid[point.second * graph.column + point.first].GetW());
        seq.pop();
    }
    while (!seq.empty()) {
        point = seq.front();
        graph.grid[point.second * graph.column + point.first].SetF(-1);
        seq.pop();
    }
}



void LDG::CaculateBlockWeights(int n) {
    float weights = 0;
    for (auto it = blocks[n].points.cbegin(); it != blocks[n].points.cend(); it++) {
        weights += graph.grid[it->second * graph.column + it->first].GetW();
    }
    blocks[n].SetWeights(weights);
}

void LDG::CaculateBlockEdges(int n) {
    float edges = 0;
    for (auto it = blocks[n].points.cbegin(); it != blocks[n].points.cend(); it++) {
        if (graph.grid[it->second * graph.column + it->first].GetW() > 1) {
            edges += CaculatePointEdges(it->first, it->second, n);
        }
    }
    blocks[n].SetEdges(edges);
}

void LDG::DistributeBlocks() {
    BFS(0, 0, 0);
    for (int i = 0; i < graph.row; i++) {
        for (int j = 0; j < graph.column; j++) {
            if (graph.grid[i * graph.column + j].GetF() != -1) continue;
            LinearDeterministicGreedy(j, i);
        }
    }
    vector<int> seq;
    for (int i = 0; i < graph.row * graph.column; i++) {
        seq.push_back(i);
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(seq.begin(), seq.end(), std::default_random_engine (seed));
//    for (int i = 0; i < num; i++) {
//        BFS(seq[i] % graph.column, seq[i] / graph.column, i);
//    }
    for (int i = 0; i < graph.row * graph.column; i++) {
        if (graph.grid[seq[i]].GetF() != -1) continue;
        LinearDeterministicGreedy(seq[i] % graph.column, seq[i] / graph.column);
    }
    for (int i = 0; i < num; i++) {
        CaculateBlockWeights(i);
        CaculateBlockEdges(i);
//        cout << "Block["<< i <<"] Info : ";
        cout << "(weights,edges) = (" << blocks[i].GetWeights() << "," << blocks[i].GetEdges() << ")\n";
//        for (auto it = blocks[i].points.cbegin(); it != blocks[i].points.cend(); it++) {
//            graph.grid[it->second * graph.column + it->first].PrintInfo();
//        }
        cout << endl;
    }
}

//void LDG::DistributeBlocks() {
//    BFS(0, 0, 0);
//    default_random_engine e(time(0));
//    uniform_real_distribution<float> u(0, 1);
//    for (int i = 0; i < graph.row; i++) {
//        for (int j = 0; j < graph.column; j++) {
//            if (graph.grid[i * graph.column + j].GetF() != -1) continue;
//            LinearDeterministicGreedy(j, i);
//        }
//    }
//    for (int i = 0; i < num; i++) {
//        CaculateBlockWeights(i);
//        CaculateBlockEdges(i);
////        cout << "Block["<< i <<"] Info : ";
//        cout << "(weights,edges) = (" << blocks[i].GetWeights() << "," << blocks[i].GetEdges() << ")\n";
////        for (auto it = blocks[i].points.cbegin(); it != blocks[i].points.cend(); it++) {
////            graph.grid[it->second * graph.column + it->first].PrintInfo();
////        }
//        cout << endl;
//    }
//}

void LDG::OutputResult(ofstream& outfile) {
    outfile << graph.row << " ";
    outfile << graph.column << endl;
    for (int i = 0; i < graph.row; i++) {
        for (int j = 0; j < graph.column; j++) {
            outfile << graph.grid[i * graph.column + j].GetW() << " ";
            outfile << graph.grid[i * graph.column + j].GetF();
            outfile << endl;
        }
    }
}
