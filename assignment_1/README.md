# CS F214: Logic Assignment

Submission for CS F214: Logic assignment 1

Done by:

1. Arunachala Amuda Murugan (2021A7PS0205H)

2. Ayush Bhauwala (2021A7PS0180H)

3. Suryansh Chandola (2021A7PS0058H)

Main test expression: `~((r+(s+a))*((~p)*q))`

Follow format in `tasks.json` file.

(or)

Compile the task file along with all header `(*.h)` and cpp `(*cpp)` files in the functionalities folder. Example:

```bash
g++  task1.cpp ./functionalities/*.h ./functionalities/*.cpp -o task1
```

CSV file with analysis of code in -O1 and -O3 optimizations: [analysis.csv](https://github.com/majimearun/logic_assignment_1/blob/main/analysis/analysis.csv)

-   **Note:** time of execution and cpu usage is measured using `/usr/bin/time`
-   Test cases were generated using `makeTestCases.py`
-   Computer specifications on which tests were run:
    -   Processor: Intel i5 core 10th gen
    -   8gb RAM
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
