二维均匀网格划分设计与实现
====================
# 1. 研究问题
计算流体力学网格背景(未完成)

本文以二维均匀网格作为研究对象，研究如何将网格划分为多个计算资源尽可能相同的块，同时尽可能减少块与块间的数据通信。
# 2. 基本假设
二维均匀网格( $grid$ )由大小相同的网格点( $point$ )组成，用 $G$ 表示二维均匀网格。用 $p_{ij}$ 表示坐标为 $(x,y)$ 的网格点。不同网格点对计算资源的需求不同，用 $w_{ij}$ 表示网格点 $p_{ij}$ 所需计算资源大小( $weight$ )。每个网格点的计算依赖于其周围各点，本文假定网格点 $p_{ij}$ 的计算依赖于其上下左右四个点 $p_{i-1j}$ 、 $p_{i+1j}$ 、 $p_{ij-1}$ 、 $p_{ij+1}$ 。用 $e_{ij}$ 表示网格点 $p_{ij}$ 与其他网格点进行数据通信的大小（ $edge$ ）。若 $p_{ij}$ 在网格边缘，则其依赖的上下左右四个点会出现越界的情况，越界的网格点不纳入数据通信范围内。

如下图所示，在二维均匀网格 $G$ 中，需要计算资源的网格点用黑色表示，即 $w_{ij}\gt0$ ，例如 $p_{10}$ 、 $p_{22}$ ，不需要计算资源的网格点用白色表示，即 $w_{ij}=0$ ，例如 $p_{03}$ 。计算数据通信大小 $e_{ij}$ 时，由于 $p_{22}$ 相邻四点都在网格内，因此 $e_{22}=4$ 。 $p_{10}$ 在网格边界，其下方的网格点出现了越界情况，不纳入数据通信范围，因此 $e_{10}=3$ 。由于 $p_{03}$ 不需要计算资源，因此 $e_{03}=0$ 。

<div align=center>
<img style="width:50%;" src=https://github.com/RenLide/Graph_Partition/blob/main/image/grid_point_example.png>
</div>

<!--
<div align=center>
<img style="width:50%;" src=https://github.com/RenLide/Graph_Partition/blob/main/image/grid_point_example.png>
</div>
-->

在划分二维网格时，需要输入二维网格 $G$ 的大小( $column×row$ )和每个网格点 $p_{ij}$ 对计算资源的需求 $w_{ij}$，并输入需要分割的块数( $num$ )。每个网格块( $block$ )用 $B_n$ 表示，若网格点 $p_{ij}$ 在网格块 $B_n$ 内，则有 $p_{ij} \in B_n$。$W_n$ 表示网格块 $B_n$ 所需计算资源，$E_n$ 表示网格块 $B_n$ 与外部数据通信的大小。

定义二维网格 $G$ 为全部网格点 $p_{ij}$ 的集合，即有 
$$ G=\{p_{ij}|i=0,1,…column-1,j=0,1,…row-1\} $$

定义 $B_n$ 为 $G$ 的子集， $\{B_0,B_1,…B_{num-1}\}$ 为 $G$ 的一个划分，即有 
$$ B_n \ne \emptyset \quad (n=0,1,…num-1)$$
$$ G = \bigcup B_n\quad (n=0,1,…,num-1)$$
$$ B_i \bigcap B_j = \emptyset \quad (i \ne j,\quad i=0,1,…num-1,\quad j=0,1,…num-1)$$

定义 $W_n$ 为网格块 $B_n$ 所需计算资源大小，其值为网格块 $B_n$ 内所有网格点的计算资源之和，即有 
$$ W_n=\sum w_{ij}\quad (P_{ij} \in B_n)$$

定义 $E_n$ 为 $G$ 与外部数据通信的大小，即有（这个很难定义清楚 还没想好如何公式化）

定义 $W_{total}$ 为二维网格 $G$ 所需的计算资源，即 $w_{ij}$ 之和，即有 
$$W_{total}=\sum w_{ij} \quad (P_{ij} \in G)$$

为了使得分割后的网格块拥有比较好的并行效果，应尽可能使得每个网格块所需的计算资源相同，即有 
$$minW_{error} = \frac{1}{num} \sqrt{\frac{\sum(W_n-\overline{W})^2}{\overline{W}^2}}\quad(n=0,1,…num-1)$$

在尽可能均衡各个网格块计算资源的同时，应尽可能减小网格块之间的总通信，即有 
$$minE_{error} = \sum E_n \quad(n=0,1,…num-1)$$

以下图为例，二维网格大小为 $8×6$ ( $column=8,row=6$ )，输入 $num=3$，将二维网格分成三块。需要计算资源的网格点用黑色表示，不妨令黑色网格点的计算资源为 $w_{ij}=1$，白色网格点不需要计算资源，即 $w_{ij}=0$。可能的一种划分方式如下图所示，二维网格被划分成了$Block0$ 、 $Block1$ 、 $Block2$。

<div align=center>
<img style="width:60%;" src=https://github.com/RenLide/Graph_Partition/blob/main/image/block_example.png>
</div>

<!--
<div align=center>
<img style="width:60%;" src=https://github.com/RenLide/Graph_Partition/blob/main/image/block_example.png>
</div>
-->

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

在`global.hpp`定义全局变量用于控制二维网格的基本数据。`RE`表示网格的最小分辨率，`X_MAX` `X_MIN` `Y_MAX` `Y_MIN`表示二维坐标的范围。`RANDOM`表示需要计算资源的网格点占总体的比例，用于控制随机生成网格点。`TOL`表示容许的最大误差，用于均衡每个网格块的计算资源。`BLOCK_NUM`表示网格块的数量。

```C++
const float RE = 1;
const float X_MAX = 8;
const float X_MIN = 0;
const float Y_MAX = 6;
const float Y_MIN = 0;
const float RANDOM = 0.3;
const float TOL = 0.01;
const int BLOCK_NUM = 3;
```

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
网格图即为二维网格，由`class Graph`表示，主要成员变量`row` `column`用于记录二维网格的行列，`weights`用于记录整个二维网格所需的总计算资源。`grid`使用一维`vector`记录二维网格的所有网格点，长度为 $row×column$。坐标为 $(x,y)$ 的网格点在一维向量中表示为 $grid[y*column+x]$。主要成员函数`InitGraph`用于初始化二维网格中各个网格点，有随机生成和文件读取两种方式。`PrintGraphWeight`以二维的方式输出网格中计算资源的分布信息。

```C++
class Graph {
public:
    int row;
    int column;
    float weights;
    vector<class Point> grid;
    Graph (int r = (int)((Y_MAX - Y_MIN) / RE), int col = (int)((X_MAX - X_MIN) / RE));
    void InitGraph();
    void InitGraph(ifstream& infile);
    void PrintGraphWeight();
};
```

### 网格块
网格块由`class Block`表示，主要成员变量`x_min` `x_max` `y_min` `y_max`用于记录网格块的坐标边界。`flag`用于标记 $block$，例如 $block0$ 、$block4$ 等。 `weights`表示网格块所需的计算资源，即 $W_n$。`edges`表示网格块与外界数据通信的大小，即 $E_n$。`row_weights` `col_weights`分别用于记录网格块每行或者每列所需的计算资源。`points`用于记录在网格块内的所有网格点的坐标。主要成员函数有多个 `Get` `Set`，用于获取和修改成员变量。`AddPoint`和`DeletePoint`分别用于在网格块内添加和删除网格点。

```C++
class Block {
public:
    int x_min;
    int x_max;
    int y_min;
    int y_max;
    int flag;
    float weights;
    float edges;
    vector<float> row_weights;
    vector<float> col_weights;
    set<pair<int, int> > points;
    Block(int xmin, int xmax, int ymin, int ymax, int flag = -1);
    void SetWeights(float w);
    void SetEdges(float e);
    float GetWeights();
    float GetEdges();
    void AddPoint(pair<int, int> p);
    void DeletePoint(pair<int, int> p);
    
};
```

### 举例说明

在下图中，`class Graph`为 $8×6$ 的二维网格($col=8，row =6$)，`gird`是长度为48的一维向量。通过 $y*column+x$ 可知坐标为 $(2,1)$ 的网格点在`grid`中对应的下标为10。`class Block`中，$block0$ 的`flag=0`，其边界范围为`x_min=0` `x_max=5` `y_min=1` `y_max=5`。

<div align=center>
<img style="width:80%;" src=https://github.com/RenLide/Graph_Partition/blob/main/image/grid_example.png>
</div>

在 $block0$ 中，确定边界后可以统计出网格块中每行和每列的计算资源需求。网格块的列数为`block_col = x_max - x_min + 1 = 6`，行数为`block_row = y_max - y_min + 1 = 5`。统计后的计算资源信息分别存在`col_weights` `row_weights`中，具体数据如下图所示。

<div align=center>
<img style="width:70%;" src=https://github.com/RenLide/Graph_Partition/blob/main/image/col_row_example.png>
</div>

## 算法设计

### 核心思想

NG算法主要采用了 **贪心** 和 **分治** 的思想。在划分二维网格( $Graph$ )时，每一个网格块( $Block$ )都可以看成一个新的二维网格，只是形状更复杂，但不失二维网格的一般性质。换句话说，二维网格的划分相当于把一个大的网格块分成更多小的网格块。NG算法只处理一个问题：**将一个大网格块分成合适的两个小网格块。**

### 分治

NG算法在开始划分前需要知道两件事情：
1. 网格块( $Block$ )内每个网格点的分布和对计算资源的需求。
2. 最终被分成的块数( $num_n$ )。

在数据结构部分中提到，`class Block` 记录了网格块( $Block$ )的全部信息，最终的块数( $block\_num$ )则是定义在`global.hpp`中。将二维网格( $Graph$ )视为一个大的网格块( $Block_0$)，则NG算法就可以运作了。一般调用方法为`NG(Block_n, num_n)`，初始调用为`NG(Block_0,block_num)`。

目前的问题是在以何种方式将网格块分成两个子网格块。

假定当前网格块所需的总计算资源为10，最终要被分成5块。为了保证最终的网格块所需计算资源尽可能均衡，比较好的划分方式是分成计算资源为4和6的两个子网格块。这样就能把`NG(Block_n,5)`分解成`NG(Block_n1,2)`和`NG(Block_n2,3)`两个子问题。

<div align=center>
<img style="width:100%;" src=https://github.com/RenLide/Graph_Partition/blob/main/image/NG_example1.png>
</div>

另一种比较好的划分方式是将 $block_n$ 分成计算资源为2和8的子网格块。这样就把`NG(Block_n,5)`分解成`NG(Block_n1,1)`和`NG(Block_n2,4)`两个子问题。如果分成计算资源为5和5的两个字网格块，则不能很好保证在最终划分中得到计算资源比较均衡的子网块，因此这种划分方式是不正确的。

<div align=center>
<img style="width:100%;" src=https://github.com/RenLide/Graph_Partition/blob/main/image/NG_example2.png>
</div>

因此对于一个计算资源为 $W_n$ 且最终需要被划分为 $num$ 块的网格块，被分割的两个子网格块应该尽可能接近 $\frac{W_n}{num_n}$ 的整数倍。在`global.hpp`中定义了全局常量`TOL`，代表在分割时所能容忍的最大误差，即每个子网格块所需计算资源的范围为 $\frac{(k\pm TOL)*W_n}{num_n}$，其中 $k$ 为整数。假定分成的两个子网格块所需的计算资源分别为 $\frac{k * W_n}{num_n}$ 和 $\frac{(num_n-k) * W_n}{num_n}$，则`NG(Block_n, num_n)`可以分解成`NG(Block_n1, k)`和`NG(Block_n2, num_n - k)`两个子问题。

了解到如何将一个大网格块划分成两个小网格块之后，剩下要解决的问题就是何时停止划分。对于`NG(Block_n, num_n)`问题，当 $num_n=1$ 时，表示最终会被分成1块，也就是当前网格块本身，即当前块为最终划分方案中的一块，此时划分停止。

### 贪心

划分大网格块 $Block_n$ 时，通过分治的方法可以将`NG(Block_n, num_n)`分解成`NG(Block_n1, k)`和`NG(Block_n2, num_n - k)`两个子问题。那么如何确定 $k$ 的值以及如何找到相应的两个子网格块 $Block_{n1}$ 和 $Block_{n2}$ ？

$k$ 值的选取是多样的，子网格块的选择则更加复杂。我们考虑一种比较简单的方式：**遍历**。对网格块内的网格点( $Point$ )以某种方式遍历，并累加已经遍历过的网格点所需计算资源 $W_{sum}$，记录第一个满足 $W_{sum}\ge\frac{k * W_n}{num_n}\ (k = 1, 2,...num_n-1)$ 的网格点，这样就能得到得到`num_n - 1`个可以划分的点。

考虑网格图( $Graph$ )中`grid`对网格点的存储方式，可以按照存储方式进行遍历，也可以称作网格块的**行遍历**。如下图所示，$Block0$ 从 $(x_{min},y_{min})$ 开始逐行遍历，直至 $(x_{max},y_{max})$ 结束。通过`Point.GetF() = Block.flag`判定网格点是否属于 $Block0$，从而统计出可用于划分的网格点，不妨称其为**划分点**。

<div align=center>
<img style="width:80%;" src=https://github.com/RenLide/Graph_Partition/blob/main/image/row_traversal.png>
</div>

对于 $Block0$，如果要分成4块，即处理`NG(Block_0, 4)`，则按照行遍历和 $W_{sum}\ge\frac{k * W_n}{num_n}\ (k = 1, 2,...num_n-1)$ 规则可以找到3个划分点，如左下图所示。如果要分成3块，即处理`NG(Block_0, 3)`，则可以找到2个划分点，如右下图所示。

<div align=center>
<img style="width:100%;" src=https://github.com/RenLide/Graph_Partition/blob/main/image/row_traversal_example.png>
</div>

当选取一个网格点用于划分时，不妨规定此网格点包含在前一个子网格块中。如左上图所示，当选择`k=2`网格点时，`Block0`被划分成`Block01` `Block02`，此时`NG(Block_0, 4)`被划分成`NG(Block_01, 2)` `NG(Block_02, 2)`。

每个划分点都能满足均衡负载的要求，如何从多个划分点中选择呢？考虑第二个目标：网格块之间的数据通信尽可能小。如下图所示，以`k=1`作为划分点，则`Block01`与`Block02`之间的数据通信为 $E_1=5$，以`k=2`作为划分点，则`Block01`与`Block02`之间的数据通信为 $E_2=4$。因此通过贪心的思想，找到数据通信最小的划分点既可。注意`k=1`时，出现了子网格块$Block_{02}$不连通的情况，这是NG算法暂时无法避免的。

<div align=center>
<img style="width:100%;" src=https://github.com/RenLide/Graph_Partition/blob/main/image/divided_points_example1.png>
</div>

同理可以计算出`k=3`时，数据通信大小$E_3=4$，因此在`k=2`与`k=3`中选择一种即可。但如果考虑右下图的情况呢？此情况与`k=2`非常相似，但其数据通信只有$E_{2'}=2$。可以观察到初始的划分点周围有一些不需要计算资源的网格点，这些点划分到`Block01`或者`Block02`不会影响负载均衡，但会对数据通信大小产生影响。在保证负载均衡的前提下，将这些不需要计算资源的网格点也当成划分点，有利于帮助找到更合适的点。因此这些不需要计算资源的网格点也将纳入到划分点的考虑范围。

<div align=center>
<img style="width:100%;" src=https://github.com/RenLide/Graph_Partition/blob/main/image/divided_points_example2.png>
</div>

如何找出这些不需要计算资源的划分点呢？对于 $W_{sum} = k \times W_{total}/num_n$ 的情况，每个初始划分点必须放在 $Block01$ 中，因此只能继续向后遍历寻找不需要计算资源的网格点，遇到需要计算资源的网格点则停止，否则会影响负载均衡，如左下图所示。对于 $W_{sum} > k \times W_{total}/num_n$ 的情况，每个初始划分点在 $Block01$ 和 $Block02$ 中均可，因此其可搜寻的划分点更多，可以向前追溯也可以向后寻找。向前追溯时，遇到第一个需要计算资源的网格点时停止，此网格点虽然需要计算资源但不影响负载均衡，因此也可以纳入划分点中。先后遍历寻找则和 $W_{sum} = k \times W_{total}/num_n$ 一样，遇到第一个需要计算资源的网格点时停止，但此网格点不纳入划分点中，如右下图所示。

<div align=center>
<img style="width:100%;" src=https://github.com/RenLide/Graph_Partition/blob/main/image/divided_points_example3.png>
</div>

至此，算法的实现思路已经基本清晰。但如果只考虑行遍历，网格块会越分越薄，因此可以定义一种类似的遍历方法，**列遍历**。如左下图所示，$Block0$ 从 $(x_{min},y_{min})$ 开始逐列遍历，直至 $(x_{max},y_{max})$ 结束。划分点也可以按类似的方式寻找，以 $(2,2)$作为划分点后的子网格块如右下图所示。

<div align=center>
<img style="width:100%;" src=https://github.com/RenLide/Graph_Partition/blob/main/image/col_traversal.png>
</div>

## 算法实现

## 测试样例
6×8 **行遍历**和**列遍历**
<div align=center>
<img style="width:30%;" src=https://github.com/RenLide/Graph_Partition/blob/main/result/NG_sample2_6_8.png>
<img style="width:30%;" src=https://github.com/RenLide/Graph_Partition/blob/main/result/NG_sample_6_8.png>
</div>

50×50 NG算法测试

<div align=center>
<img style="width:70%;" src=https://github.com/RenLide/Graph_Partition/blob/main/result/NG_Sample_50_50.png>
</div>

20×30 NG算法与LDG算法测试对比

<div align=center>
<img style="width:40%;" src=https://github.com/RenLide/Graph_Partition/blob/main/result/NG_Sample_20_30.png>
<img style="width:40%;" src=https://github.com/RenLide/Graph_Partition/blob/main/result/LDG_Sample_20_30.png>
</div>


# 4. Linear Deterministic Greedy(LDG)
## 数据结构
## 算法设计
## 测试样例
