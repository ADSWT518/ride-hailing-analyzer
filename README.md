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
![image-20201217230506338](https://raw.githubusercontent.com/tyz518/pictureForTypora/main/20201217230513.png?token=ASCENRYM5Z3QPE6QMSUOBDK73NZ6Q)
2. 最后一天的最后时刻，有vector越界的情况