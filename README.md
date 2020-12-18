# Ride-Hailing-Analyzer
Final project for CS241

## Notes

* When clicking the "Load file" button, this program will load all of the dataset, so that users needn't to load data again when they want to change the fields or time span.

* Qt widgets can only be used in the main thread. All operations on GUI must be done in the main thread.

## Dairy

### 12.15

finish the GUI design and `loadFile()` function

### 12.16

apply multi-thread into `loadFile()` function

### 12.17

finish the progress bar and part of `displaySTDemand()` function

**TODO:**


1. 每两天之间的数据会突然变大，很奇怪
![image-20201217230506338](https://user-images.githubusercontent.com/58338486/102573860-57a82000-412a-11eb-9430-f3f2e32f330e.png)

2. 最后一天的最后时刻，有vector越界的情况

### 12.18

meet Dr. Ling in office hour

**TODO:**

1. 数据存储方式，不要用一个大数组，可以考虑每个field搞一个数组，方便调用
2. 把`timeStep`的选择做成动态的，也就是用一个`QSpinBox`，只要改变了，就reload图像
