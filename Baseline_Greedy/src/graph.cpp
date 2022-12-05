//
//  graph.cpp
//  Baseline_Greedy
//
//  Created by SleepyFish on 2022/11/24.
//

#include "graph.hpp"

Graph::Graph(int r, int col) : row(r), column(col) {
    this->grid.resize(this->row * this->column, Point(0, 0));
    weights = 0;
}

void Graph::InitGraph () {
    default_random_engine e(time(0));
    uniform_real_distribution<float> u(0, 1);
    float x, y, w;
    for (int i = 0; i < this->row; i++) {
        for (int j = 0; j < this->column; j++) {
            y = Y_MIN + i * RE;
            x = X_MIN + j * RE;
            w = u(e);
            //cout << w << "\t";
//            w = (w < RANDOM) ? w + 1 : 0;
            w = (w < RANDOM) ? 1 : 0;
            //cout << w << "\t";
            grid[i * column + j] = Point(x, y, w, x + y);
            weights += w;
            //cout << grid[i * column + j].GetW() << endl;
            //test (x,y)
            //grid[i * column + j].PrintInfo();
        }
    }
}

void Graph::InitGraph (ifstream& infile) {
    float x, y, w;
    int flag;
    for (int i = 0; i < this->row; i++) {
        for (int j = 0; j < this->column; j++) {
            y = Y_MIN + i * RE;
            x = X_MIN + j * RE;
            //cout << w << "\t";
            infile >> w;
            infile >> flag;
            //cout << w << "\t";
            grid[i * column + j] = Point(x, y, w, x + y);
            weights += w;
            //cout << grid[i * column + j].GetW() << endl;
            //test (x,y)
            //grid[i * column + j].PrintInfo();
        }
    }
}

void Graph::PrintGraphWeight() {
//    for (int i = 0; i < this->row; i++) {
    for (int i = this->row - 1; i >= 0; i--) {
        for (int j = 0; j < this->column; j++) {
            cout.precision(4);
            //test (x,y)
//            cout << "(" << setw(4) << left << setfill(' ') << grid[i * column + j].GetX();
//            cout << "," << setw(4) << left << setfill(' ') << grid[i * column + j].GetY() << ")";
            cout << "(" << j;
            cout << "," << i << ")";
            cout << "[" << setw(5) << right << setfill(' ') << grid[i * column + j].GetW() << "]";
//            cout << "{" << setw(2) << right << setfill(' ')<< grid[i * column + j].GetF() << "}";
            cout << (j != this->column - 1? "\t" : "\n");
        }
        cout << endl;
    }
}
