//
//  block.cpp
//  Linear_Deterministic_Greedy
//
//  Created by SleepyFish on 2022/10/25.
//

#include "block.hpp"
Block::Block(){
    this->weights = 0;
    this->edges = 0;
    points.clear();
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
