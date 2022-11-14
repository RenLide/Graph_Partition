//
//  NG.cpp
//  Naive_Greedy
//
//  Created by SleepyFish on 2022/11/9.
//

#include "NG.hpp"

NG::NG (int k) {
    num = k;
    blocks.resize(k,Block(X_MIN, X_MAX - 1, Y_MIN, Y_MAX - 1));
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

NG::NG (int k, ifstream& infile) {
    num = k;
    blocks.resize(k,Block(X_MIN, X_MAX - 1, Y_MIN, Y_MAX - 1));
    int row, col;
    infile >> row;
    infile >> col;
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

void NG::CaculateBlockWeights (int n) {
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

int NG::CaculatePointEdges(int x, int y, int n) {
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

void NG::CaculateBlockEdges (int n) {
    float edges = 0;
    for (auto it = blocks[n].points.cbegin(); it != blocks[n].points.cend(); it++) {
        if (graph.grid[it->second * graph.column + it->first].GetW() > 0) {
            edges += CaculatePointEdges(it->first, it->second, n);
        }
    }
    blocks[n].SetEdges(edges);
}

pair<int, float> NG::CaculateKeyPoints(int n, vector<pair<int, int> > &kp, bool f) {
    int kp_divid, kp_min, kp_max, kp_index = -1; //depend on f(bool)
    float front_edges, back_edges, edges, edges_min = blocks[n].weights;
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

void NG::DistribitedBlocks(int n, int k) {
    CaculateBlockWeights(n);
    if (k == 1 || k == 0) return;
    float weight = 0;
    float count = 1;
    int f;
    vector<pair<int, int> > keypoints[2], pre_points[2];
    vector<int> kp_count[2];
    pair<int, int> pre_point;
    pair<int, float> kp_result[2];
    int first_min = -1, first_max = -1, second_min = -1, second_max = -1, grid_index = -1, kp_index = -1;
    for (f = 0; f <= 1; f++) {
        weight = 0;
        count = 1;
        if (f) {
            first_min = blocks[n].y_min;
            first_max = blocks[n].y_max;
            second_min = blocks[n].x_min;
            second_max = blocks[n].x_max;
        }
        else {
            first_min = blocks[n].x_min;
            first_max = blocks[n].x_max;
            second_min = blocks[n].y_min;
            second_max = blocks[n].y_max;
        }
        //caculate the keypoint for distribitng
        bool pre_flag = false;
        int pre_index;
        for (int i = first_min; i <= first_max; i++) {
            for (int j = second_min; j <= second_max; j++) {
                grid_index = f ? (i * graph.column + j) : (j * graph.column + i);
                if (pre_flag) {
                    if (graph.grid[grid_index].GetW() == 0 && graph.grid[grid_index].GetF() == blocks[n].flag) {
                        pre_point = f ? pair<int, int>(j, i) : pair<int, int>(i, j);
                        keypoints[f].push_back(pre_point);
                        kp_count[f].push_back(count - 1);
                    }
                    else pre_flag = false;
                }
                if (graph.grid[grid_index].GetF() == blocks[n].flag) {
                    weight += graph.grid[grid_index].GetW();
                    if (count < k && weight >= (float)(count / k * blocks[n].weights)) {
                        while (!pre_points[f].empty()) {
//                            pre_index = pre_points[f].back().second * graph.column + pre_points[f].back().first;
                            if (weight != (float)(count / k * blocks[n].weights)) {
                                keypoints[f].push_back(pre_points[f].back());
                                kp_count[f].push_back(count);
                            }
                            pre_points[f].pop_back();
                        }
                        pair<int, int> keypoint = f ? pair<int, int>(j, i) : pair<int, int>(i, j);
                        keypoints[f].push_back(keypoint);
                        kp_count[f].push_back(count);
                        count++;
                        pre_flag = true;
                    }
                    if (graph.grid[grid_index].GetW() > 0) pre_points[f].clear();
                    pre_point = f ? pair<int, int>(j, i) : pair<int, int>(i, j);
                    pre_points[f].push_back(pre_point);
                }
            }
        }
    }
    kp_result[0] = CaculateKeyPoints(n, keypoints[0], 0);
    kp_result[1] = CaculateKeyPoints(n, keypoints[1], 1);
    f = kp_result[0].second > kp_result[1].second;
    kp_index = kp_result[f].first;
    int bound[2][4];
    bound[0][0] = blocks[n].x_max;
    bound[0][1] = blocks[n].x_min;
    bound[0][2] = blocks[n].y_max;
    bound[0][3] = blocks[n].y_min;
    bound[1][0] = blocks[n].x_max;
    bound[1][1] = blocks[n].x_min;
    bound[1][2] = blocks[n].y_max;
    bound[1][3] = blocks[n].y_min;
    bool front = true;
    int new_num = n;
    if (f) {
        first_min = blocks[n].y_min;
        first_max = blocks[n].y_max;
        second_min = blocks[n].x_min;
        second_max = blocks[n].x_max;
    }
    else {
        first_min = blocks[n].x_min;
        first_max = blocks[n].x_max;
        second_min = blocks[n].y_min;
        second_max = blocks[n].y_max;
    }
    for (int i = first_min; i <= first_max; i++) {
        for (int j = second_min; j <= second_max; j++) {
            grid_index = f ? (i * graph.column + j) : (j * graph.column + i);
            if (graph.grid[grid_index].GetF() == blocks[n].flag) {
                if (f) {
                    if (j < bound[front][0]) bound[front][0] = j;
                    if (j > bound[front][1]) bound[front][1] = j;
                    if (i < bound[front][2]) bound[front][2] = i;
                    if (i > bound[front][3]) bound[front][3] = i;
                    if (!front) {
                        blocks[n].DeletePoint(pair<int, int>(j, i));
                        blocks[new_num].AddPoint(pair<int, int>(j, i));
                        graph.grid[grid_index].SetF(new_num);
                    }
                }
                else {
                    if (i < bound[front][0]) bound[front][0] = i;
                    if (i > bound[front][1]) bound[front][1] = i;
                    if (j < bound[front][2]) bound[front][2] = j;
                    if (j > bound[front][3]) bound[front][3] = j;
                    if (!front) {
                        blocks[n].DeletePoint(pair<int, int>(i, j));
                        blocks[new_num].AddPoint(pair<int, int>(i, j));
                        graph.grid[grid_index].SetF(new_num);
                    }
                }
                if (grid_index == (keypoints[f][kp_index].second * graph.column + keypoints[f][kp_index].first)) {
                    front = false;
                    for (int i = 0; i < num; i++) {
                        if (blocks[i].weights == 0) {
                            new_num = i;
                            blocks[new_num].flag = new_num;
                            break;
                        }
                    }
                }
            }
        }
    }
    blocks[new_num].x_min = bound[0][0];
    blocks[new_num].x_max = bound[0][1];
    blocks[new_num].y_min = bound[0][2];
    blocks[new_num].y_max = bound[0][3];
    blocks[n].x_min = bound[1][0];
    blocks[n].x_max = bound[1][1];
    blocks[n].y_min = bound[1][2];
    blocks[n].y_max = bound[1][3];
    DistribitedBlocks(new_num, k - kp_count[f][kp_index]);
    DistribitedBlocks(n, kp_count[f][kp_index]);
}

void NG::OutputResult(ofstream& outfile) {
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

void NG::PrintResult() {
    for (int i = 0; i < num; i++) {
        CaculateBlockEdges(i);
//        cout << "Block["<< i <<"] Info : ";
        cout << "(weights,edges) = (" << blocks[i].GetWeights() << "," << blocks[i].GetEdges() << ")\n";
//        for (auto it = blocks[i].points.cbegin(); it != blocks[i].points.cend(); it++) {
//            graph.grid[it->second * graph.column + it->first].PrintInfo();
//        }
        cout << endl;
    }
}
