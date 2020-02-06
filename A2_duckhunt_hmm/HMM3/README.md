# HMM3 Estimate Model
In this task you should show that you know how to estimate the model parameters for an HMM. You will be given a starting guess of a HMM (transition matrix, emission matrix and initial state probability distribution) and a sequence of emissions and you should train the HMM to maximize the probability of observing the given sequence of emissions.

- Input
  - You will be given a starting guess of the three matrices; transition matrix, emission matrix, and initial state probability distribution followed by the number of emissions and the sequence of emissions itself. The initial state probability distribution is a row vector encoded as a matrix with only one row. Each matrix is given on a separate line with the number of rows and columns followed by the matrix elements (ordered row by row). Note that the rows and column size can be different from the sample input. It is assumed that there are M different discrete emission types and these are indexed 0 through M-1 in the emission sequence. For example, if there were M=3 possible different emissions (could be the three colours red, green and blue for example), they would be identified by 0, 1 and 2 in the emission sequence.

- Output
  - You should output the estimated transition matrix and emission matrix on one line each in the same matrix format as they were given, including the dimensions. Do not output the estimated initial state probability distribution.
