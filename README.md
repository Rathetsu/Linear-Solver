# Linear-Solver-2
It's a program that solves systems of linear equations. It solves using Gaussian Elimination. 

It was, at first, a university project that is required to solve up to a hundred equations in a hundred different variables.

I wrote the code using Cramer's Rule which did the job but had a complexity O(n*n!) so it solved a maximum of 13 equations in 13 different variables before starting to take an unreasonable amount of time to solve.

I still got an A because my program had way more functionality than other students. ie: adding/subtracting equations and multiplying/dividing equations by constants.

I rewrote most of the code base to use Gaussian Elimination instead of Cramer's and it worked out great, complexity now is O(n^3).

I switched to Object-Oriented programming and implemented Multi-threading as well.
