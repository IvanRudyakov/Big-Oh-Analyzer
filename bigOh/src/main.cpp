#include <iostream>
#include <functional>
#include <cmath>
#include <vector>
#include <string>
#include <utility>
#include <chrono>
#include <algorithm>
#include "bigOh.hpp"

using namespace std;
using namespace bigOh;

long fibonacci(int n){
    if (n < 2) return n;
    return fibonacci(n-1) + fibonacci(n-2);
}

void mergeSort(int n) {
    vector<int> k{};
    for(int i = n; i > 0; i--) {
        k.push_back(i);
    }
    sort(k.begin(), k.end());
}

void sumUpToBad(int n) {
    vector<int> v{};
    for(int i = n; i > 0; i--) {
        v.push_back(i);
    }
    vector<int> out{};
    for(int i = 0; i < v.size(); i++) {
        int k = 0;
        for(int j = 0; j <= i; j++) {
            k += v[j];
        }
        out.push_back(k);
    }
}

void sumUpToGood(int n) {
    vector<int> v{};
    for(int i = n; i > 0; i--) {
        v.push_back(i);
    }
    vector<int> out{};
    int sumSoFar = 0;
    for(int i = 0; i < v.size(); i++) {
        sumSoFar += v[i];
        out.push_back(sumSoFar);
    }
}


vector<pair<int, double>> testFunc(const function<void(int)>& func, int start, int end, int skip = 1) {
    vector<pair<int, double>> out{};
    for(int i = start; i < end; i+=skip) {
        auto start = chrono::steady_clock::now();
        func(i);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        out.push_back({i, elapsed_seconds.count()});
    }
    return out;
}

int main() {
    cout << "start test" << endl;






    auto pts = testFunc(
        mergeSort, // int -> void algorithm to test
        2,         // starting testing number
        1000000,   // ending testing number
        1000      // how many to skip in between
    );
    const vector<pair<string, function<double(double)>>> bigOhs = {
        {"O(1)",       [&](double n){ return 1; }},
        {"O(log(n))",  [&](double n){ return log(n+1); }},
        {"O(sqrt(n))", [&](double n){ return sqrt(n); }},
        {"O(n)",       [&](double n){ return n; }},
        {"O(nlog(n))", [&](double n){ return n*log(n+1); }},
        {"O(n^1.5)",   [&](double n){ return n*sqrt(n); }},
        {"O(n^2)",     [&](double n){ return n*n; }},
        {"O(n^3)",     [&](double n){ return n*n*n; }},
        {"O(n^4)",     [&](double n){ return n*n*n*n; }},
        {"O(2^n)",     [&](double n){ return pow(2, n); }},
        {"O(3^n)",     [&](double n){ return pow(3, n); }},
    };







    cout << "biggest time: " << pts[pts.size()-1].second << endl;
    cout << endl;
    for(const auto& data : bigOhs) {
        TestResult result = bigOhRegressTest(data.second, pts, BigOhTestType::average, true);
        cout << data.first << " --- constant: " << result.constant << " -- accuracy value: " << result.accuracyValue << endl;
    }
    cout << endl;
    cout << "finish" << endl;
}