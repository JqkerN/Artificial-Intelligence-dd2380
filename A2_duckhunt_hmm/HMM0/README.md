# HMM0 Next Emission Distribution
In this task you should show that you know how to predict how the system will evolve over time and estimate the probability for different emissions / events in the system i.e. what can be observed from the HMM. You will be given the state probability distribution (i.e. the probability that the system is in each of the N states), the transition matrix (i.e. the matrix that gives the probability to transition from one state to another) and the emission matrix (i.e. the matrix that gives the probability for the different emissions / events / observations given a certain state). </br>

More specifically, given the current state probability distribution what is the probabity for the different emissions after the next transition (i.e. after the system has made a single transition)?

- Input
  - You will be given three matrices (in this order); transition matrix, emission matrix, and initial state probability distribution. The initial state probability distribution is a row vector encoded as a matrix with only one row. Each matrix is given on a separate line with the number of rows and columns followed by the matrix elements (ordered row by row). Note that the rows and column size can be different from the sample input.</br>
  A[4x4]: 0.2 0.5 0.3 0.0 0.1 0.4 0.4 0.1 0.2 0.0 0.4 0.4 0.2 0.3 0.0 0.5</br>
  B[4x3]: 1.0 0.0 0.0 0.0 1.0 0.0 0.0 0.0 1.0 0.2 0.6 0.2</br>
  pi[1x4]: 0.0 0.0 0.0 1.0</br>

- Output
  - You should output the emission probability distribution on a single line in the same matrix format, including the dimensions.</br>
  prob.[1x3]: 0.3 0.6 0.1

To compile:
```
$ g++ main.cpp -o main
```
To compare with example:
```
$ ./main.exe < sample_00.in
```
