//
//  block.cpp
//  Baseline_Greedy
//
//  Created by SleepyFish on 2022/11/24.
//

#include "block.hpp"

Block::Block (int xmin, int xmax, int ymin, int ymax, int f) {
    x_min = xmin;
    x_max = xmax;
    y_min = ymin;
    y_max = ymax;
    flag = f;
    weights = 0;
    edges = 0;
    row_weights.resize(y_max - y_min + 1);
    col_weights.resize(x_max - x_min + 1);
}

void Block::AddPoint(pair<int, int> p) {
    points.insert(p);
}

void Block::DeletePoint(pair<int, int> p) {
    points.erase(p);
}

void Block::SetWeights(float w) {
    this->weights = w;
}

void Block::SetEdges(float e) {
    this->edges = e;
}

float Block::GetWeights() {
    return this->weights;
}

float Block::GetEdges() {
    return this->edges;
}
