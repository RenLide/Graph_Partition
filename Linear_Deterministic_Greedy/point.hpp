//
//  point.hpp
//  Linear_Deterministic_Greedy
//
//  Created by SleepyFish on 2022/10/25.
//

#ifndef point_hpp
#define point_hpp
#include <iostream>
#include <stdio.h>
class Point {
private:
    float x;    //xlabel
    float y;    //ylabel
    float w;    //weight
    float v;    //value
    int f;      //block flag
public:
    Point(float xlabel, float ylabel, float weight = 1, float value = 0, float flag = -1);
    float GetX();
    float GetY();
    float GetW();
    float GetV();
    int GetF();
    void SetW(float weight);
    void SetV(float value);
    void SetF(int flag);
    float Caculate();
    void PrintInfo();
};
#endif /* point_hpp */
