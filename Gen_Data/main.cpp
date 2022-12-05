//
//  main.cpp
//  DataGenaration
//
//  Created by SleepyFish on 2022/11/22.
//

#include <iostream>
#include <fstream>
//#include <random>
#include <ctime>
using namespace std;
int main(int argc, const char * argv[]) {
    int col = atoi(argv[1]);
    int row = atoi(argv[2]);
    float random = atof(argv[3]);
//    int col = 8;
//    int row = 6;
//    float random = 0.3;
    float w;
    ofstream outfile(argv[4]);
    outfile << 0 << " ";
    outfile << col << endl;
    outfile << 0 << " ";
    outfile << row << endl;
    outfile << 1 << " ";
    outfile << random << endl;
//    default_random_engine e(time(0));
//    uniform_real_distribution<float> u(0, 1);
    struct timespec tp;
    clock_gettime(CLOCK_THREAD_CPUTIME_ID,&tp);
    srand(tp.tv_nsec);
//    srand((int)time(NULL));
    for (int i = 0; i < col * row; i++) {
//        w = u(e);
        w = (float)(rand() % 1000) /1000;
        w = (w < random) ? 1 : 0;
        outfile << w << " ";
        outfile << 0;
        if (i != col * row - 1) outfile << endl;
    }
    outfile.close();
    return 0;
}
