
#include <vector>
#include <functional>
#include <utility>
#include <cmath>
#include <limits>
#include "bigOh.hpp"
#include <iostream>
#include <algorithm>


using namespace std;
using namespace bigOh;




TestResult bigOh::bigOhRegressTest(const function<double(double)>& bigOh, const vector<pair<int, double>>& pts, BigOhTestType testType, bool ptsAlreadySorted) {
    vector<pair<int, double>> testPts = pts;
    int numPts = testPts.size();
    if(testType == BigOhTestType::bigOh || testType == BigOhTestType::bigOmega) {
        if(!ptsAlreadySorted) {
            sort(testPts.begin(), testPts.end(), [&](const pair<int, double>& first, const pair<int, double>& second){ return first.first < second.first; });
        }
        if     (testType == BigOhTestType::bigOh) {
            vector<pair<int, double>> out{};
            int curInt = testPts[0].first;
            double curMaxValue = testPts[0].second;
            const pair<int, double>* curPt = &testPts[0];
            for(const auto& pt : testPts) {
                if(curInt < pt.first) {
                    if(curPt != nullptr) out.push_back(*curPt);
                    curPt = nullptr;
                    curInt = pt.first;
                }
                if(curMaxValue <= pt.second) {
                    curPt = &pt;
                    curMaxValue = pt.second;
                }
            }
            testPts = out;
        }
        else if(testType == BigOhTestType::bigOmega) {
            vector<pair<int, double>> out{};
            reverse(testPts.begin(), testPts.end());
            int curInt = testPts[0].first;
            double curMinValue = testPts[0].second;
            const pair<int, double>* curPt = &testPts[0];
            for(const auto& pt : testPts) {
                if(curInt > pt.first) {
                    if(curPt != nullptr) out.push_back(*curPt);
                    curPt = nullptr;
                    curInt = pt.first;
                }
                if(curMinValue >= pt.second) {
                    curPt = &pt;
                    curMinValue = pt.second;
                }
            }
            reverse(out.begin(), out.end());
            testPts = out;
        }
    }
    
    const double startupTime = testPts[0].second;
    for(auto& pt : testPts) {
        pt.second -= startupTime;
    }

    {
        vector<pair<int, double>> newTestPts{};
        for(const auto& pt : testPts) {
            if(pt.second > 0) newTestPts.push_back(pt);
        }
        testPts = newTestPts;
        numPts = testPts.size();
    }
    
    for(auto& pt : testPts) {
        pt.second = log(pt.second);
    }

    const function<double(double)> logFunction = [&](double d){
        return log(bigOh(d));
    };

    vector<double> logDifferences = [&]{
        vector<double> out{};
        out.reserve(numPts);
        for(const auto& pt : testPts) {
            out.push_back(pt.second - logFunction(pt.first));
        }
        return out;
    }();

    const double logChange = [&]{
        sort(logDifferences.begin(), logDifferences.end());
        double logChange;
        if     (numPts % 2 == 0) {
            logChange = (logDifferences[numPts/2] + logDifferences[numPts/2 - 1])/2;
        }
        else if(numPts % 2 == 1) {
            logChange = logDifferences[numPts/2];
        }
        for(double& difference : logDifferences) {
            difference -= logChange;
        }
        return logChange;
    }();

    const double constant = exp(logChange);
    const double accuracyValue = [&]{
        double out = 0.0;
        for(double diff : logDifferences) {
            out += abs(diff);
        }
        return out;
    }();

    return {constant, accuracyValue};

}