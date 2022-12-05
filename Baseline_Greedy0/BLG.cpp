//
//  BLG.cpp
//  Baseline_Greedy
//
//  Created by SleepyFish on 2022/11/24.
//

#include "BLG.hpp"

BLG::BLG (int k) {
    num = k;
    _xmin = X_MIN;
    _xmax = X_MAX;
    _ymin = Y_MIN;
    _ymax = Y_MAX;
    re = RE;
    random = RANDOM;
    blocks.resize(k,Block(0, (int)(X_MAX - X_MIN) / RE - 1, 0, (int)(Y_MAX - Y_MIN) / RE - 1));
    for (int i = 0; i < k; i++) {
        blocks[i].SetWeights(0);
    }
    graph.InitGraph();
    for (int i = 0; i < graph.row; i++) {
        for (int j = 0; j < graph.column; j++) {
            graph.grid[i * graph.column + j].SetF(0);
            blocks[0].AddPoint(pair<int, int>(j, i));
        }
    }
    blocks[0].flag = 0;
}

BLG::BLG (int k, ifstream& infile) {
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
    blocks.resize(k,Block(0, col - 1, 0, row - 1));
    graph = Graph(row, col);
    for (int i = 0; i < k; i++) {
        blocks[i].SetWeights(0);
    }
    graph.InitGraph(infile);
    for (int i = 0; i < graph.row; i++) {
        for (int j = 0; j < graph.column; j++) {
            graph.grid[i * graph.column + j].SetF(0);
            blocks[0].AddPoint(pair<int, int>(j, i));
        }
    }
    blocks[0].flag = 0;
}

void BLG::CaculateBlockWeights (int n) {
    float weights = 0;
    fill(blocks[n].row_weights.begin(), blocks[n].row_weights.end(), 0);
    fill(blocks[n].col_weights.begin(), blocks[n].col_weights.end(), 0);
    for (int i = blocks[n].y_min; i <= blocks[n].y_max; i++) {
        for (int j = blocks[n].x_min; j <= blocks[n].x_max; j++) {
            if (graph.grid[i * graph.column + j].GetF() == blocks[n].flag) {
                weights += graph.grid[i * graph.column + j].GetW();
                blocks[n].row_weights[i - blocks[n].y_min] += graph.grid[i * graph.column + j].GetW();
                blocks[n].col_weights[j - blocks[n].x_min] += graph.grid[i * graph.column + j].GetW();
            }
        }
    }
    blocks[n].SetWeights(weights);
}

int BLG::CaculatePointEdges(int x, int y, int n) {
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

void BLG::CaculateBlockEdges (int n) {
    float edges = 0;
    for (auto it = blocks[n].points.cbegin(); it != blocks[n].points.cend(); it++) {
        if (graph.grid[it->second * graph.column + it->first].GetW() > 0) {
            edges += CaculatePointEdges(it->first, it->second, n);
        }
    }
    blocks[n].SetEdges(edges);
}

pair<int, float> BLG::CaculateKeyPoints(int n, vector<pair<int, int> > &kp, bool f) {
    int kp_divid, kp_min, kp_max, kp_index = -1; //depend on f(bool)
    float front_edges, back_edges, edges, edges_min = graph.weights + 1;
    kp_min = f ? blocks[n].x_min : blocks[n].y_min;
    kp_max = f ? blocks[n].x_max : blocks[n].y_max;
    for (int i = 0; i < kp.size(); i++) {
        kp_divid = f ? kp[i].first : kp[i].second;
        front_edges = 0;
        back_edges = 0;
        for (int j = kp_min; j <= kp_max; j++) {
            if (j <= kp_divid) {
                if (f && graph.grid[kp[i].second * graph.column + j].GetW() > 0) front_edges++;
                if (f && kp[i].second + 1 <= blocks[n].y_max && graph.grid[(kp[i].second + 1) * graph.column + j].GetW() > 0) back_edges++;
                if (!f && graph.grid[j * graph.column + kp[i].first].GetW() > 0) front_edges++;
                if (!f && kp[i].first + 1 <= blocks[n].x_max && graph.grid[j * graph.column + kp[i].first + 1].GetW() > 0) back_edges++;
                if (j == kp_divid) {
                    if (f && j + 1 <= kp_max && graph.grid[kp[i].second * graph.column + j].GetW() > 0) front_edges++;
                    if (!f && j + 1 <= kp_max && graph.grid[j * graph.column + kp[i].first].GetW() > 0) front_edges++;
                }
            }
            else {
                if (f && kp[i].second - 1 >= 0 && graph.grid[(kp[i].second - 1) * graph.column + j].GetW() > 0) front_edges++;
                if (f && graph.grid[kp[i].second * graph.column + j].GetW() > 0) back_edges++;
                if (!f && kp[i].first - 1 >= 0 && graph.grid[j * graph.column + kp[i].first - 1].GetW() > 0) front_edges++;
                if (!f && graph.grid[j * graph.column + kp[i].first].GetW() > 0) back_edges++;
                if (j == kp_divid + 1) {
                    if (f && j - 1 >= 0 && graph.grid[kp[i].second * graph.column + j].GetW() > 0) back_edges++;
                    if (!f && j - 1 >= 0 && graph.grid[j * graph.column + kp[i].first].GetW() > 0) back_edges++;
                }
            }
        }
        edges = front_edges + back_edges;
        if (edges < edges_min) {
            edges_min = edges;
            kp_index = i;
        }
    }
    if (kp_index == -1) {
        kp_index = kp_index;
        exit(-1);
    }
    return pair<int, float>(kp_index, edges_min);
}

void BLG::DistributeBlocks(int n, int k) {
    CaculateBlockWeights(n);
    if (k == 1 || k == 0) return;
    float col_weight = 0;
    float row_weight = 0;
    int front = k/2;
    int back = k - front;
    int col_index = 0;
    int row_index = 0;
    int new_num = 0;
    for (col_index = 0; col_index < graph.column; col_index++) {
        col_weight += blocks[n].col_weights[col_index];
        if (col_weight >= blocks[n].weights * front / k) break;
    }
    for (row_index = 0; row_index < graph.row; row_index++) {
        row_weight += blocks[n].row_weights[row_index];
        if (row_weight >= blocks[n].weights * front / k) break;
    }
    for (int i = 0; i < num; i++) {
        if (blocks[i].weights == 0) {
            new_num = i;
            blocks[new_num].flag = new_num;
            break;
        }
    }
    if (blocks[n].col_weights[col_index] < blocks[n].row_weights[row_index]) {
        blocks[new_num].x_min = blocks[n].x_min + col_index + 1;
        blocks[new_num].x_max = blocks[n].x_max;
        blocks[new_num].y_min = blocks[n].y_min;
        blocks[new_num].y_max = blocks[n].y_max;
        blocks[n].x_min = blocks[n].x_min;
        blocks[n].x_max = blocks[n].x_min + col_index;
        blocks[n].y_min = blocks[n].y_min;
        blocks[n].y_max = blocks[n].y_max;
    }
    else {
        blocks[new_num].x_min = blocks[n].x_min;
        blocks[new_num].x_max = blocks[n].x_max;
        blocks[new_num].y_min = blocks[n].y_min + row_index + 1;
        blocks[new_num].y_max = blocks[n].y_max;
        blocks[n].x_min = blocks[n].x_min;
        blocks[n].x_max = blocks[n].x_max;
        blocks[n].y_min = blocks[n].y_min;
        blocks[n].y_max = blocks[n].y_min + row_index;
    }
    for (int i = blocks[new_num].x_min; i <= blocks[new_num].x_max; i++) {
        for (int j = blocks[new_num].y_min; j <= blocks[new_num].y_max; j++) {
            blocks[n].DeletePoint(pair<int, int>(i, j));
            blocks[new_num].AddPoint(pair<int, int>(i, j));
            graph.grid[j * graph.column + i].SetF(new_num);
        }
    }
    DistributeBlocks(new_num, back);
    DistributeBlocks(n, front);
}

void BLG::OutputResult(ofstream& outfile) {
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

void BLG::PrintResult() {
    for (int i = 0; i < num; i++) {
        CaculateBlockEdges(i);
//        cout << "Block["<< i <<"] Info : ";
        cout << "Block[" << i << "]";
        cout << "(weights,edges) = (" << blocks[i].GetWeights() << "," << blocks[i].GetEdges() << ")";
//        for (auto it = blocks[i].points.cbegin(); it != blocks[i].points.cend(); it++) {
//            graph.grid[it->second * graph.column + it->first].PrintInfo();
//        }
        cout << endl;
    }
}

pair<float, float> BLG::CaculateError() {
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

