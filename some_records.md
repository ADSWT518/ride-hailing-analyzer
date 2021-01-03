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


- [x] 每两天之间的数据会突然变大，很奇怪
  ![image-20201217230506338](https://user-images.githubusercontent.com/58338486/102573860-57a82000-412a-11eb-9430-f3f2e32f330e.png)

- [x] 最后一天的最后时刻，有vector越界的情况

### 12.18

meet Dr. Ling in office hour

* 先只要实现基础部分就可以了
* elective task 1 可以去申请百度/高德地图的key

**TODO:**

- [ ] ~~数据存储方式，不要用一个大数组，可以考虑每个field搞一个数组，方便调用~~ 这样行不通的
- [x] 把`timeStep`的选择做成动态的，也就是用一个`QSpinBox`，只要改变了，就reload图像
- [x] 使用`departure_time`来排序，而不是使用没有实际意义的`mid_time`
- [x] 把画图与计算分离，计算部分放到一个新的thread里面去
- [ ] 或许可以把读文件和排序分两个线程来加快速度？

### 12.19

:cry:

### 12.20

大致把绘制整个成都的图像的功能做好了，同时还把grid的存储方式做了优化

**TODO:**

- [x] 快速改变`QSpinBox`的值的时候，图像会出现问题。原因应该是我不知道怎么在开启下一个线程时，结束之前的线程。
- [x] 开始做按照grid的绘图

### 12.23

- [x] 改变`timeStep`之后，统计得到的`sum of orderCountVector`怎么也变了orz

### 12.24

* finish display of data in each grid!!!

**TODO:**

- [ ] 在拉格朗日插值里面，为啥把数组`timeVector`的类型设为`qint32`就不对，设置成`qint64`就对了。。。

- [ ] `如果最后一组数据在达到timeStep之前就超过了endTimeStamp，那么舍弃它`
  
  感觉不能用这个规则，不然有时候舍弃的太多了

### 12.25

- [x] 奇怪的bug：按照grid绘图的时候，前两次会画出来大概两倍于正常的点——第三次就正常了

### 1.2

我怎么还没做完:broken_heart:

- [x] 一开始没选中fee，第二次导入时选中，结果还是显示不出来

### 1.3

终于做完了orz