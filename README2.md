二维网格划分算法程序使用说明与性能测试
=========================
本项目实现了三种算法：
1. **BLG**(Baseline Greedy)
2. **NG**(Naive Greedy)
3. **LDG**(Linear Deterministic Greedy)

具体实现方法参考`README.md`。

## 目录结构说明

本项目的结构目录如下所示。

```
Graph_Paritioning  
├── Baseline_Greedy  
│   ├── CMakeLists.txt  
│   ├── build  
│   ├── include  
│   └── src  
├── Gen_Data  
│   ├── CMakeLists.txt  
│   ├── build  
│   └── main.cpp  
├── Linear_Deterministic_Greedy  
│   ├── CMakeLists.txt  
│   ├── build  
│   ├── include  
│   └── src  
├── Naive_Greedy  
│   ├── CMakeLists.txt  
│   ├── build  
│   ├── include  
│   └── src  
├── README.md  
├── data  
│   ├── data10_10.dat  
│   ├── data20_20.dat  
│   └── data80_80.dat  
├── image  
│   ├── BLG_exmaple1.png  
│   ├── NG_exmaple1.png  
│   └── LDG_example1.png  
├── log  
│   ├── test1_160_160.log  
│   ├── test2_160_160.log  
│   └── test3_160_160.log  
├── plot  
│   ├── analysis_block_num.m  
│   ├── analysis_random.m  
│   ├── analysis_size.m  
│   └── result_plot.m  
├── result  
│   ├── error_BLG1_160_160.dat  
│   ├── error_LDG1_160_160.dat  
│   ├── error_NG1_160_160.dat  
│   ├── result_BLG160_160.dat  
│   ├── result_LDG160_160.dat  
│   └── result_NG160_160.dat  
└── test  
    ├── BLG  
    ├── GenData  
    ├── LDG  
    ├── NG  
    └── test.sh  
```

**`Baseline_Greedy`** **`Naive_Greedy`** **`Linear_Deterministic_Greedy`** 为三种算法程序的文件夹，包含算法实现的代码和编译信息，三种算法可在其对应文件夹内单独编译运行。

**`Gen_Data`** 用于生成初始二维网格数据，文件夹内包含代码和编译信息，可单独运行。

**`plot`** 用于可视化数据结果，文件夹中的代码可在 $matlab$ 中运行。

**`test`** 为测试文件夹，包含`test.sh`和多个算法可执行文件，用于测试三种算法的性能。

**`data`** 用于保存二维网格数据文件，数据文件由`Gen_Data`生成，可输入到`BLG` `NG` `LDG`中输出二维网格划分后的结果。

**`result`** 用于保存划分后的二维网格数据`result.dat`和用于误差分析的`error.dat`文件。

**`log`** 用于记录测试过程信息。

**`image`** 用于保存可视化图表。

## 使用说明

本项目在MacOS中实现，编译和运行均在Terminal中进行。编译工具为**CMake**。

### 编译说明

在`Gen_Data`文件夹中，进入`build`文件夹，使用命令`cmake ..`配置CMake生成Makefile文件。使用命令`make`编译`Gen_Data`子项目，生成可执行文件 **`GenData`**。

在`Baseline_Greedy`文件夹中，进入`build`文件夹，使用命令`cmake ..`配置CMake生成Makefile文件。使用命令`make`编译`Baseline_Greedy`子项目，生成可执行文件 **`BLG`**。

同理可给`Naive_Greedy` `Linear_Deterministic_Greedy`子项目分别生成可执行文件 **`NG`** 和 **`LDG`**。

### 可执行文件说明

**`GenData`** 用于生成随机的二维网格。需要输入二维网格的列`col`、行`row`、计算网格点占比`random`以及输出文件路径`DATA_PATH`。使用命令 **`./GenData col row random DATA_PATH`** 生成相应的数据文件。例如使用命令`GenData 10 20 0.3 data.dat`，则会在当前目录的`data.dat`文件中生成10列20行规模大小的二维网格，且30%的网格点需要计算资源。

**`BLG`** **`NG`** **`LDG`** 采用不同算法划分二维网格，使用方法相同。以 **`BLG`** 为例，需要输入源数据文件`SRC_PATH`、目标数据文件`DEST_PATH`、网格块数`block_num`、误差数据文件`ERROR_PATH`。使用命令 **`./BLG SRC_PATH DEST_PATH block_num ERROR_PATH`** 生成划分后的二维网格数据文件和用于误差分析的数据文件。运行后会在终端显示此次运行的日志`log`，包含由文字描述的运行时间、误差信息和分块信息。

在多次测试时可将标准输出重定向到`LOG_PATH`，用于分析数据，可使用命令 **`./BLG SRC_PATH DEST_PATH block_num ERROR_PATH >> LOG_PATH`**。例如命令`./BLG data.dat result.dat 4 error.dat >> reuslt.log`可通过 $Baseline Greedy$ 算法将`data.dat`中的二维网格划分成4块并将二维网格数据保存在`result.dat`文件中，将误差数据保存在`error.dat`中并把运行日志输出到`result.log`文件中。 **`NG`** 和 **`LDG`** 使用方法与上述相同。

### 测试脚本说明

在`test`文件夹中，`test.sh`脚本可自动测试`BLG` `NG` `LDG`算法的性能。使用 **`./test.sh`** 即可运行脚本。该脚本可自动编译`Gen_Data` `Baseline_Greedy` `Naive_Greedy` `Linear_Deterministic_Greedy`文件夹中的代码，并将生成的` GenData` `BLG` `NG` `LDG`可执行文件复制到`./test/`目录下。用户可修改脚本，测试不同规模、不同网格块数、不同计算网格点比例下，三种算法的性能。固定参数后，可通过`GenData`生成多组数据，减小偶然误差。

本`test.sh`

<div align=center>
<img style="width:80%;" src=/Users/renlide/Projects/Graph_Paritioning/image/test_explain.png>
</div>