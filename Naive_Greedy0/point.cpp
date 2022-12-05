//
//  point.cpp
//  Naive_Greedy
//
//  Created by SleepyFish on 2022/11/9.
//

#include "point.hpp"

Point::Point(float xlabel, float ylabel, float weight, float value, float flag) \
: x(xlabel), y(ylabel), w(weight), v(value), f(flag) {}

float Point::GetX() {
    return this->x;
}

float Point::GetY() {
    return this->y;
}

float Point::GetW() {
    return this->w;
}

float Point::GetV() {
    return this->v;
}

int Point::GetF() {
    return this->f;
}

void Point::SetW(float weight) {
    this->w = weight;
}

void Point::SetV(float value) {
    this->v = value;
}

void Point::SetF(int flag) {
    this->f = flag;
}

float Point::Caculate() {
    return 0;
}
void Point::PrintInfo() {
    std::cout << "Point Info : ";
    std::cout << "(x,y) = (" << this->x << "," << this->y << ")  ";
    std::cout << "(w,v) = (" << this->w << "," << this->v << ")\n";
}
