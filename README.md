# CS F214: Logic Assignment 1

Submission for CS F214: Logic assignment 1: Parse Trees

Main test expression: `~((r+(s+a))*((~p)*q))`

Use already compiled files/binaries (only linux supported). Example:

```bash
./task1
```

(or)

Follow format in `tasks.json` file.

(or)

compile all the task file along with all header `(*.h)` and cpp `(*cpp)` files in the functionalities folder:

```bash
g++ -o <task> <task>.cpp ./functionalities/utils.h ./functionalities/utils.cpp ./functionalities/node.cpp ./functionalities/node.cpp
```

CSV file with analysis of code in -O1 and -O3 optimizations: [analysis.csv](https://github.com/majimearun/logic_assignment_1/blob/main/analysis/analysis.csv)

-   Note: time of execution and cpu usage is measured using `/usr/bin/time`
-   Test cases were generated using `makeTestCases.py`
-   Computer specifications on which tests were run:
    -   Processor: Intel i5 core 10th gen
    -   OS: Pop!\_OS 22.04

| task number | optimization level | size of expression (no. of atoms = operands + operators) | execution time: wall clock time (s) | cpu alloted (%) |
| ----------- | ------------------ | -------------------------------------------------------- | ----------------------------------- | --------------- |
| 1           | -O1                | 7500                                                     | 0.01                                | 92              |
|             | -O1                | 75000                                                    | 0.53                                | 97              |
|             | -O3                | 75000                                                    | 0.49                                | 98              |
| 2           | -O1                | 7500                                                     | 0.03                                | 100             |
|             | -O1                | 75000                                                    | 0.35                                | 93              |
|             | -O3                | 75000                                                    | 0.33                                | 87              |
| 3           | -O1                | 7500                                                     | 0.02                                | 96              |
|             | -O1                | 75000                                                    | 0.48                                | 96              |
|             | -O3                | 75000                                                    | 0.46                                | 97              |
| 4           | -O1                | 7500                                                     | 0.11                                | 97              |
|             | -O1                | 75000                                                    | 0.46                                | 98              |
|             | -O3                | 75000                                                    | 0.47                                | 85              |
| 5           | -O1                | 7500                                                     | 0.02                                | 10              |
|             | -O1                | 75000                                                    | 0.78                                | 5               |
|             | -O3                | 75000                                                    | 0.47                                | 6               |
