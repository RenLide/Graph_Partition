二维均匀网格划分设计与实现
====================
# 1. 研究问题
计算流体力学网格背景(未完成)

本文以二维均匀网格作为研究对象，研究如何将网格划分为多个计算资源尽可能相同的块，同时尽可能减少块与块间的数据通信。
# 2. 基本假设
二维均匀网格($grid$)由大小相同的网格点($point$)组成，用 $G$ 表示二维均匀网格。用 $p_{ij}$ 表示坐标为 $(x,y)$ 的网格点。不同网格点对计算资源的需求不同，用 $w_{ij}$ 表示网格点 $p_{ij}$ 所需计算资源大小($weight$)。每个网格点的计算依赖于其周围各点，本文假定网格点 $p_{ij}$ 的计算依赖于其上下左右四个点 $p_{i-1j}$ 、$p_{i+1j}$ 、$p_{ij-1}$ 、$p_{ij+1}$ 。用 $e_{ij}$ 表示网格点 $p_{ij}$ 与其他网格点进行数据通信的大小（$edge$）。若 $p_{ij}$ 在网格边缘，则其依赖的上下左右四个点会出现越界的情况，越界的网格点不纳入数据通信范围内。

如下图所示，在二维均匀网格 $G$ 中，需要计算资源的网格点用黑色表示，即 $w_{ij}\gt0$ ，例如 $p_{10}$ 、$p_{22}$ ，不需要计算资源的网格点用白色表示，即 $w_{ij}=0$ ，例如 $p_{03}$ 。计算数据通信大小 $e_{ij}$ 时，由于 $p_{22}$ 相邻四点都在网格内，因此 $e_{22}=4$ 。$p_{10}$ 在网格边界，其下方的网格点出现了越界情况，不纳入数据通信范围，因此 $e_{10}=3$ 。由于 $p_{03}$ 不需要计算资源，因此 $e_{03}=0$ 。

<div align=center>
<img style="width:50%;" src=/Users/renlide/projects/Graph_paritioning/image/grid_point_example.png>
</div>

在划分二维网格时，需要输入二维网格 $G$ 的大小($row×column$)和每个网格点 $p_{ij}$ 对计算资源的需求 $w_{ij}$，并输入需要分割的块数($num$)。每个网格块($block$)用 $B_n$ 表示，若网格点 $p_{ij}$ 在网格块 $B_n$ 内，则有 $p_{ij} \in B_n$。$W_n$ 表示网格块 $B_n$ 所需计算资源，$E_n$ 表示网格块 $B_n$ 与外部数据通信的大小。

定义二维网格 $G$ 为全部网格点 $p_{ij}$ 的集合，即有
$$ G=\{\ p_{ij}\ |\ i=0,1,…column-1,\ j=0,1,…row-1\} $$

定义 $B_n$ 为 $G$ 的子集，$\{B_0,B_1,…B_{num-1}\}$ 为 $G$ 的一个划分，即有
$$ B_n \ne \emptyset \quad (n=0,1,…num-1)$$
$$ G = \bigcup B_n\quad (n=0,1,…,num-1)$$
$$ B_i \bigcap B_j = \emptyset \quad (i \ne j,\quad i=0,1,…num-1,\quad j=0,1,…num-1)$$

定义 $W_n$ 为网格块 $B_n$ 所需计算资源大小，其值为网格块 $B_n$ 内所有网格点的计算资源之和，即有
$$ W_n=\sum w_{ij}\quad (P_{ij} \in B_n)$$

定义 $E_n$ 为 $G$ 与外部数据通信的大小，即有（这个很难定义清楚 还没想好如何公式化）

定义 $W_{sum}$ 为二维网格 $G$ 所需的计算资源，即 $w_{ij}$ 之和，即有
$$W_{sum}=\sum w_{ij} \quad (P_{ij} \in G)$$

为了使得分割后的网格块拥有比较好的并行效果，应尽可能使得每个网格块所需的计算资源相同，即有
$$min\ W_{error} = \frac{1}{num} \sqrt{\frac{\sum(W_n-\overline{W})^2}{\overline{W}^2}}\quad(n=0,1,…num-1)$$

在尽可能均衡各个网格块计算资源的同时，应尽可能减小网格块之间的总通信，即有
$$min\ E_{error} = \sum E_n \quad(n=0,1,…num-1)$$

以下图为例，二维网格大小为 $8×6$ ($column=8,row=6$)，输入 $num=3$，将二维网格分成三块。需要计算资源的网格点用黑色表示，不妨令黑色网格点的计算资源为 $w_{ij}=1$，白色网格点不需要计算资源，即 $w_{ij}=0$。可能的一种划分方式如下图所示，二维网格被划分成了$Block0$ 、$Block1$ 、$Block2$。

<div align=center>
<img style="width:80%;" src=/Users/renlide/Projects/Graph_Paritioning/image/block_example.png>
</div>

根据上述定义可以得出以下数据

| |Block0|block1|block2|
|:---:|:---:|:---:|:---:|
|$W_n$|5|7|6|
|$E_n$|2|5|3|

计算可得
$$W_{sum}=18\qquad\overline{W}=6$$
$$W_{error} = \frac{1}{num} \sqrt{\frac{\sum(W_n-\overline{W})^2}{\overline{W}^2}}=\frac{1}{3}\sqrt{\frac{(5-6)^2+(7-6)^2+(6-6)^2}{{6}^2}}=0.0786$$
$$E_{error} = \sum E_n=2+5+3=10$$

# 3. Naive Greedy Algorithm(NG)
## 数据结构
介绍数据结构时，只对主要成员变量和成员函数作说明，代码均简化处理，便于理解，不代表实际代码。
### 网格点
网格点由`class Point`表示，主要成员变量`x` `y` `v`用来记录网格点的坐标位置 $(x,y)$ 和网格点的数据 $value$， `w` 用来记录网格点所需的计算资源 $weight$，`f`用来标记 $(flag)$ 网格点所属的网格块。主要成员函数包括多个`Get` `Set`用于获取和修改成员变量， `PrintInfo`用于打印网格点各项数据信息。
```C++
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
    void PrintInfo();
};
```
### 网格图
网格图即为二维网格，由`class Graph`表示，
### 网格块
## 算法设计
## 测试样例
# 4. Linear Deterministic Greedy(LDG)
## 数据结构
## 算法设计
## 测试样例
