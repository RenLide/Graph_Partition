//
//  LDG.cpp
//  Linear_Deterministic_Greedy
//
//  Created by SleepyFish on 2022/10/26.
//

#include "LDG.hpp"
LDG::LDG(int k) {
    num = k;
    _xmin = X_MIN;
    _xmax = X_MAX;
    _ymin = Y_MIN;
    _ymax = Y_MAX;
    re = RE;
    random = RANDOM;
    blocks.resize(k);
    for (int i = 0; i < k; i++) {
        blocks[i].SetWeights(0);
    }
    graph.InitGraph();
    scores.resize(graph.row * graph.column);
    scores.assign(scores.size(), 0);
}

LDG::LDG(int k, ifstream& infile) {
    num = k;
    infile >> _xmin;
    infile >> _xmax;
    infile >> _ymin;
    infile >> _ymax;
    infile >> re;
    infile >> random;
    int row, col;
    row = (int)(_ymax - _ymin) / re;
    col = (int)(_xmax - _xmin) / re;
    blocks.resize(k);
    graph = Graph(row, col);
    for (int i = 0; i < k; i++) {
        blocks[i].SetWeights(0);
    }
    graph.InitGraph(infile);
    scores.resize(graph.row * graph.column);
    scores.assign(scores.size(), 0);
}

void LDG::CaculateScores() {
    pair<int, int> up, down, left ,right;
    for (int i = 0; i < graph.row; i++) {
        for (int j = 0; j < graph.column; j++) {
            up = pair<int, int>(j, i + 1);
            down = pair<int, int>(j, i - 1);
            left = pair<int, int>(j - 1, i);
            right = pair<int, int>(j + 1, i);
            scores[i * graph.column + j] = graph.grid[i * graph.column + j].GetW();
            if (up.second < graph.row) scores[i * graph.column + j] += graph.grid[up.second * graph.column + up.first].GetW();
            if (down.second >= 0) scores[i * graph.column + j] += graph.grid[down.second * graph.column + down.first].GetW();
            if (left.first >= 0) scores[i * graph.column + j] += graph.grid[left.second * graph.column + left.first].GetW();
            if (right.first < graph.column) scores[i * graph.column + j] += graph.grid[right.second * graph.column + right.first].GetW();
            score_queue.push(tuple<float, int, int>(scores[i * graph.column + j], j ,i));
        }
    }
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
//BFS
//void LDG::LinearDeterministicGreedy(int x, int y) {
//    int bnum = -1; // record the block with max score
//    float score_max = -1; // record the max score
//    float score;  // record current score
//    for (int i = 0; i < num; i++) {
//        score = CaculateNeighbors(x, y, i) * (1 - blocks[i].GetWeights() / graph.weights);
//        if (score > score_max && blocks[i].GetWeights() < (1 + TOL) * graph.weights / num) {
//            score_max = score;
//            bnum = i;
//        }
//    }
//    if (bnum == -1){
//        for (int i = 0; i < num; i++) {
//            if (blocks[i].GetWeights() <(1 + TOL) * graph.weights / num) bnum = i;
//        }
//    }
//    blocks[bnum].AddPoint(pair<int, int>(x, y));
//    graph.grid[y * graph.column + x].SetF(bnum);
//    blocks[bnum].SetWeights(blocks[bnum].GetWeights() + graph.grid[y * graph.column + x].GetW());
//}

bool LDG::LinearDeterministicGreedy(int x, int y) {
    if (graph.grid[y * graph.column + x].GetF() != -1) return true;
    int bnum = -1; // record the block with max score
    float score_max = 0; // record the max score
    vector<float> ldg_scores(num, 0.01);  // record current score
    if (y + 1 < graph.row && graph.grid[(y + 1) * graph.column + x].GetF() != -1) {
        ldg_scores[graph.grid[(y + 1) * graph.column + x].GetF()] += scores[(y + 1) * graph.column + x] + 0.1;
    }
    if (y - 1 >= 0 && graph.grid[(y - 1) * graph.column + x].GetF() != -1) {
        ldg_scores[graph.grid[(y - 1) * graph.column + x].GetF()] += scores[(y - 1) * graph.column + x] + 0.1;
    }
    if (x - 1 >= 0 && graph.grid[y * graph.column + x - 1].GetF() != -1) {
        ldg_scores[graph.grid[y * graph.column + x - 1].GetF()] += scores[y * graph.column + x - 1] + 0.1;
    }
    if (x + 1 < graph.column && graph.grid[y * graph.column + x + 1].GetF() != -1) {
        ldg_scores[graph.grid[y * graph.column + x + 1].GetF()] += scores[y * graph.column + x + 1] + 0.1;
    }
    if (graph.grid[y * graph.column + x].GetW() != 0) {
        for (int i = 0; i < num; i++) {
            ldg_scores[i] = ldg_scores[i] * (1 - num / (1 + TOL) * blocks[i].GetWeights() / graph.weights);
        }
    }
    int flag = 0;
    for (int i = 0; i < num; i++) {
        if (ldg_scores[i] > score_max) {
            bnum = i;
            score_max = ldg_scores[i];
            flag = 1;
        }
        else if (ldg_scores[i] == score_max && score_max == 0) {
            flag = 0;
        }
    }
    if (bnum == -1){
        float w_min = graph.weights;
        int w_num = -1;
        for (int i = 0; i < num; i++) {
            if (blocks[i].GetWeights() < w_min) {
                w_min = blocks[i].GetWeights();
                w_num = i;
            }
        }
        bnum = w_num;
//        return false;
    }
    blocks[bnum].AddPoint(pair<int, int>(x, y));
    graph.grid[y * graph.column + x].SetF(bnum);
    blocks[bnum].SetWeights(blocks[bnum].GetWeights() + graph.grid[y * graph.column + x].GetW());
    return true;
}


void LDG::BFS(int x, int y, int n) {
    queue<pair<int, int> > seq;
    pair<int, int> center, up, down, left, right;
    seq.push(pair<int, int>(x, y));
    graph.grid[y * graph.column + x].SetF(n);
    while (!seq.empty()) {
        center = seq.front();
        up = pair<int, int>(center.first, center.second + 1);
        down = pair<int, int>(center.first, center.second - 1);
        left = pair<int, int>(center.first - 1, center.second);
        right = pair<int, int>(center.first + 1, center.second);
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
        blocks[n].AddPoint(center);
        blocks[n].SetWeights(blocks[n].GetWeights() + graph.grid[center.second * graph.column + center.first].GetW());
        seq.pop();
    }
    while (!seq.empty()) {
        center = seq.front();
        graph.grid[center.second * graph.column + center.first].SetF(-1);
        seq.pop();
    }
}

bool LDG::ScoreFirstSearch(int x, int y, int n) {
    priority_queue<tuple<float, int, int> > block_queue;
    priority_queue<tuple<float, int, int> > temp_queue;
    pair<int, int> center, up, down, left, right;
    set<pair<int ,int> > fail_edges;
    temp_queue.push(tuple<float, int, int>(scores[y * graph.column + x], x, y));
    graph.grid[y * graph.column + x].SetF(n);
    while (!temp_queue.empty() && blocks[n].GetWeights() < SFS_LOW * graph.weights / num) {
        center = pair<int, int>(get<1>(temp_queue.top()), get<2>(temp_queue.top()));
        up = pair<int, int>(center.first, center.second + 1);
        down = pair<int, int>(center.first, center.second - 1);
        left = pair<int, int>(center.first - 1, center.second);
        right = pair<int, int>(center.first + 1, center.second);
        temp_queue.pop();
        if (blocks[n].points.find(up) == blocks[n].points.end() && up.second < graph.row \
            && graph.grid[up.second * graph.column + up.first].GetF() == -1) {
            temp_queue.push(tuple<float, int, int>(scores[up.second * graph.column + up.first], up.first, up.second));
            graph.grid[up.second * graph.column + up.first].SetF(n);
        }
        if (blocks[n].points.find(down) == blocks[n].points.end() && down.second >= 0 \
            && graph.grid[down.second * graph.column + down.first].GetF() == -1) {
            temp_queue.push(tuple<float, int, int>(scores[down.second * graph.column + down.first], down.first, down.second));
            graph.grid[down.second * graph.column + down.first].SetF(n);
        }
        if (blocks[n].points.find(left) == blocks[n].points.end() && left.first >= 0 \
            && graph.grid[left.second * graph.column + left.first].GetF() == -1) {
            temp_queue.push(tuple<float, int, int>(scores[left.second * graph.column + left.first], left.first, left.second));
            graph.grid[left.second * graph.column + left.first].SetF(n);
        }
        if (blocks[n].points.find(right) == blocks[n].points.end() && right.first < graph.column \
            && graph.grid[right.second * graph.column + right.first].GetF() == -1) {
            temp_queue.push(tuple<float, int, int>(scores[right.second * graph.column + right.first], right.first, right.second));
            graph.grid[right.second * graph.column + right.first].SetF(n);
        }
        block_queue.push(tuple<float, int, int>(scores[center.second * graph.column + center.first], center.first, center.second));
        blocks[n].AddPoint(center);
        blocks[n].SetWeights(blocks[n].GetWeights() + graph.grid[center.second * graph.column + center.first].GetW());
        if (edge_points.find(center) != edge_points.end()) {
            edge_points.erase(center);
            fail_edges.insert(center);
        }
    }
    if (blocks[n].GetWeights() < SFS_LOW * graph.weights / num) {
        for (set<pair<int, int>>::iterator it = blocks[n].points.begin(); it != blocks[n].points.end(); it++) {
            graph.grid[it->second * graph.column + it->first].SetF(-1);
        }
        while (!fail_edges.empty()) {
            set<pair<int, int>>::iterator it = fail_edges.begin();
            edge_points.insert(pair<int, int>(it->first, it->second));
            fail_edges.erase(pair<int, int>(it->first, it->second));
        }
        blocks[n].points.clear();
        blocks[n].SetWeights(0);
        return false;
    }
    while (!temp_queue.empty()) {
        graph.grid[get<2>(temp_queue.top()) * graph.column + get<1>(temp_queue.top())].SetF(-1);
        pair<int, int> ep = pair<int, int>(get<1>(temp_queue.top()), get<2>(temp_queue.top()));
        if (edge_points.find(ep) == edge_points.end()) {
            edge_points.insert(ep);
        }
        temp_queue.pop();
    }
    while (!block_queue.empty() || !score_queue.empty()) {
        if (block_queue.top() == score_queue.top()) {
            block_queue.pop();
            score_queue.pop();
        }
        else {
            temp_queue.push(score_queue.top());
            score_queue.pop();
        }
    }
    while (!temp_queue.empty()) {
        score_queue.push(temp_queue.top());
        temp_queue.pop();
    }
    return true;
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
        if (graph.grid[it->second * graph.column + it->first].GetW() > 0) {
            edges += CaculatePointEdges(it->first, it->second, n);
        }
    }
    blocks[n].SetEdges(edges);
}

void LDG::DistributeBlocks() {
    CaculateScores();
    bool result;
    priority_queue<tuple<float, int, int> > unfit_queue;
//    ScoreFirstSearch(get<1>(score_queue.top()), get<2>(score_queue.top()), 0);
    for (int i = 0; i < num; i++) {
        result = ScoreFirstSearch(get<1>(score_queue.top()), get<2>(score_queue.top()), i);
        while (!result) {
            unfit_queue.push(score_queue.top());
            score_queue.pop();
            if (score_queue.empty()) {
                cout << "Fail to Distribute!" << endl;
                return;
            }
            result = ScoreFirstSearch(get<1>(score_queue.top()), get<2>(score_queue.top()), i);
        }
    }
    while (!unfit_queue.empty()) {
        score_queue.push(unfit_queue.top());
        unfit_queue.pop();
    }
//    for (int i = 0; i < graph.row; i++) {
//        for (int j = 0; j < graph.column; j++) {
//            if (graph.grid[i * graph.column + j].GetF() != -1) continue;
//            LinearDeterministicGreedy(j, i);
//        }
//    }
//    int count = 0;
    while (!edge_points.empty()) {
        set<pair<int, int>>::iterator it = edge_points.begin();
//        for (bool result = false; it != edge_points.end() && result == false; it++) {
//            result = LinearDeterministicGreedy(it->first, it->second);
//        }
//        it--;
        LinearDeterministicGreedy(it->first, it->second);
        pair<int, int> up, down, left, right;
        up = pair<int, int>(it->first, it->second + 1);
        down = pair<int, int>(it->first, it->second - 1);
        left = pair<int, int>(it->first - 1, it->second);
        right = pair<int, int>(it->first + 1, it->second);
        if (edge_points.find(up) == edge_points.end() && up.second < graph.row && graph.grid[up.second * graph.column + up.first].GetF() == -1) edge_points.insert(up);
        if (edge_points.find(down) == edge_points.end() && down.second >= 0 && graph.grid[down.second * graph.column + down.first].GetF() == -1) edge_points.insert(down);
        if (edge_points.find(left) == edge_points.end() && left.first >= 0 && graph.grid[left.second * graph.column + left.first].GetF() == -1) edge_points.insert(left);
        if (edge_points.find(right) == edge_points.end() && right.first < graph.column && graph.grid[right.second * graph.column + right.first].GetF() == -1) edge_points.insert(right);
        edge_points.erase(pair<int, int>(it->first, it->second));
//        if (count == 500){
//            count = count;
////            break;
//        }
//        if (count == 1000){
//            count = count;
////            break;
//        }
    }
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
    outfile << _xmin << " ";
    outfile << _xmax << endl;
    outfile << _ymin << " ";
    outfile << _ymax << endl;
    outfile << re << " ";
    outfile << random << endl;
    for (int i = 0; i < graph.row; i++) {
        for (int j = 0; j < graph.column; j++) {
            outfile << graph.grid[i * graph.column + j].GetW() << " ";
            outfile << graph.grid[i * graph.column + j].GetF();
            outfile << endl;
        }
    }
}

void LDG::PrintScores() {
    CaculateScores();
//    for (int i = 0; i < graph.row; i++) {
    for (int i = graph.row - 1; i >= 0; i--) {
        for (int j = 0; j < graph.column; j++) {
            cout.precision(4);
            //test (x,y)
//            cout << "(" << setw(4) << left << setfill(' ') << grid[i * column + j].GetX();
//            cout << "," << setw(4) << left << setfill(' ') << grid[i * column + j].GetY() << ")";
            cout << "(" << j;
            cout << "," << i << ")";
            cout << "[" << setw(5) << right << setfill(' ') << scores[i * graph.column + j] << "]";
            cout << (j != graph.column - 1? "\t" : "\n");
        }
        cout << endl;
    }
}

void LDG::PrintResult () {
    for (int i = 0; i < num; i++) {
        CaculateBlockEdges(i);
//        cout << "Block["<< i <<"] Info : ";
        cout << "(weights,edges) = (" << blocks[i].GetWeights() << "," << blocks[i].GetEdges() << ")";
//        for (auto it = blocks[i].points.cbegin(); it != blocks[i].points.cend(); it++) {
//            graph.grid[it->second * graph.column + it->first].PrintInfo();
//        }
        cout << endl;
    }
}

pair<float, float> LDG::CaculateError() {
    float w_average = graph.weights / num;
    float w_error = 0; // Σ(wi - w0)^2
    float e_error = 0;
    for (int i = 0; i < num; i++) {
        w_error += (blocks[i].GetWeights() - w_average) * (blocks[i].GetWeights() - w_average);
        e_error += blocks[i].GetEdges();
    }
    w_error = sqrt(w_error / (w_average * w_average)) / num;
    return pair<float, float>(w_error, e_error);
}
