#ifndef BIGOH_H
#define BIGOH_H

#include <functional>
#include <vector>
#include <utility>

using namespace std;

namespace bigOh {

    struct TestResult {
        double constant, accuracyValue; // constant is the estimated multiple on the function, and accuracyValue is the sum differences between pts and log function. 
                                        // lower accuracy value is better. Accuraccy values generally increase with #pts tested.
    };

    enum class BigOhTestType {
        bigOh, bigOmega, average
    };

    // Make sure to plug in a big Oh function which is positive for all values above 0, and possibly 0 at 0. This may require slight changes to the big
    // Oh function. For example, instead of using nlog(n), which is negative between 0 and 1, you should  use nlog(n+1).
    // If you use a function which is negative for some positive values, you may receive extraneous values for your accuracy.
    TestResult bigOhRegressTest(const function<double(double)>& bigOh, const vector<pair<int, double>>& pts, BigOhTestType testType, bool ptsAlreadySorted);

}

#endif