# Big-Oh Analyzer

Analyzes running-time data of algorithms to determine big-Oh time complexity. Uses regression techniques to determine the fit of different big Oh functions (1, log(n), n, n^2, etc.) to the running-time data of functions. Goal is to create wrappers for different languages which will allow users to easily determine the running time complexity of algorithms which take a variety of inputs.

Currently, the regression algorithm is fully implemented in C++ and can determine with relative accuracy the big-Oh time complexity of C++ functions which take in exactly one int n as input. The regression algorithm works by plotting n on the x axis against the log of the running time data on the y axis. Then, given a function f(int n) which you want to fit, the algorithm takes the log of f and determines the best coefficient D such that the sum of the errors between the running time data and log(f(n)) + D is minimized. The algorithm returns this sum of errors as an accuracy value which approximates how good of a fit f(n) is to the running-time data, with lower values being a better fit. Based on the coefficient D, you can also mathematically determine an ideal coefficient C such that Cf(n) best fits the running time data. 

The advantages of this algorithm include its simplicity and robustness against running-time data which can range from very small to very big. By taking the log of the running time data and the input function, the algorithm gives weight based on "multiplicative" differences rather than "additive" differences. This is better than a simple least squares approach because such an approach would give very little weight to small times while giving a lot of weight to minimizing the differences in the biggest times. This is especially a big problem in this scenario given how much running times can vary between small inputs of n and big inputs of n.

The algorithm has been tested against different algorithms in C++ and has been largely successful. For example, it can accurately determine, with enough data, that the stl sort algorithm in C++ is O(nlog(n)).
