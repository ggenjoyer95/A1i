//solve changed
#include <iostream>
#include <random>
#include <iomanip>
#include <vector>
#include <cmath>
#include <fstream>
using namespace std;

bool f1(double a, double b, double c, double d, double e) {
    return (a - c) * (a - c) + (b - d) * (b - d) <= e * e;
}

bool f2(double a, double b, double a1, double b1, double e1, double a2, double b2, double e2, double a3, double b3, double e3) {
    return f1(a, b, a1, b1, e1) && f1(a, b, a2, b2, e2) && f1(a, b, a3, b3, e3);
}

vector<pair<double, double>> f3(int n, double a, double b, double c, double d, mt19937& g) {
    uniform_real_distribution<> u1(a, b);
    uniform_real_distribution<> u2(c, d);
    vector<pair<double, double>> r(n);
    for (int i = 0; i < n; ++i) {
        r[i] = {u1(g), u2(g)};
    }
    return r;
}

int f4(const vector<pair<double, double>>& r, double a1, double b1, double e1, double a2, double b2, double e2, double a3, double b3, double e3) {
    int t = 0;
    for (const auto& [x, y] : r) {
        if (f2(x, y, a1, b1, e1, a2, b2, e2, a3, b3, e3)) {
            ++t;
        }
    }
    return t;
}

int main() {
    double a1 = 1.0, b1 = 1.0, e1 = 1.0;
    double a2 = 2.0, b2 = 1.0, e2 = 1.0;
    double a3 = 1.5, b3 = 2.0, e3 = 1.0;
    double x1 = min(a1 - e1, min(a2 - e2, a3 - e3));
    double x2 = max(a1 + e1, min(a2 + e2, a3 + e3));
    double y1 = min(b1 - e1, min(b2 - e2, b3 - e3));
    double y2 = max(b1 + e1, min(b2 + e2, b3 + e3));
    double exact_area = M_PI * e1 * e1 / 2;
    random_device rd;
    mt19937 g(rd());
    ofstream data_file("results.csv");
    data_file << "N,ApproximatedArea,RelativeError\n";
    for (int n = 100; n <= 100000; n += 500) {
        vector<pair<double, double>> r = f3(n, x1, x2, y1, y2, g);
        int p = f4(r, a1, b1, e1, a2, b2, e2, a3, b3, e3);
        double ar = (x2 - x1) * (y2 - y1);
        double approx_area = (static_cast<double>(p) / n) * ar;
        double rel_error = abs(approx_area - exact_area) / exact_area;
        data_file << n << "," << approx_area << "," << rel_error << "\n";
    }
    data_file.close();
    return 0;
}

