#pragma once
#include <vector>
#include <iostream>

using std::vector;
using std::cout;

namespace task {

    vector<double> operator+ (const vector<double>& a, const vector<double>& b) {
        vector<double> c;
        for (size_t i = 0; i < a.size(); ++ i) {
            c.push_back(a[i] + b[i]);
        }
        return c;
    }

    vector<double> operator+ (const vector<double>& a) {
        vector<double> c;
        for (size_t i = 0; i < a.size(); ++ i) {
            c.push_back(+a[i]);
        }
        return c;
    }

    vector<double> operator- (const vector<double>& a, const vector<double>& b) {
        vector<double> c;
        for (size_t i = 0; i < a.size(); ++ i) {
            c.push_back(a[i] - b[i]);
        }
        return c;
    }

    vector<double> operator- (const vector<double>& a) {
        vector<double> c;
        for (size_t i = 0; i < a.size(); ++ i) {
            c.push_back(-a[i]);
        }
        return c;
    }

    double operator* (const vector<double>& a, const vector<double>& b) {
        double c = 0;
        for (size_t i = 0; i < a.size(); ++ i) {
            c += a[i] * b[i];
        }
        return c;
    }

    vector<double> operator% (const vector<double>& a, const vector<double>& b) {
        vector<double> c(3);
        c[0] = a[1] * b[2] - a[2] * b[1];
        c[1] = - a[0] * b[2] + a[2] * b[0];
        c[2] = a[0] * b[1] - a[1] * b[0];
        
        return c;
    }

    bool operator|| (const vector<double>& a, const vector<double>& b) {
        bool flag = true;
        double frac = a[0] / b[0];
        for (size_t i = 1; i < a.size(); ++ i) {
            if (fabs(frac - a[i] / b[i]) > 0.00001) {
                flag = false;
                break;
            }
        }
        return flag;
    }

    bool operator&& (const vector<double>& a, const vector<double>& b) {
        bool flag = true;
        double frac = a[0] / b[0];
        for (size_t i = 1; i < a.size(); ++ i) {
            if ((fabs(frac - a[i] / b[i]) > 0.00001) || (a[i] / b[i] < 0)) {
                flag = false;
                break;
            }
        }
        return flag;
    }

    std::istream& operator>> (std::istream &is, vector<double>& a) {
        a.clear();
        size_t size_a;
        is >> size_a;
        for (size_t i = 0; i < size_a; ++ i) {
            double x;
            is >> x;
            a.push_back(x);
        }   
        return is;
    }

    std::ostream& operator<< (std::ostream &os, const vector<double>& a) {
        for (size_t i = 0; i < a.size(); ++ i) {
            os << a[i] << " ";
        }
        os << std::endl;
        return os;
    }

    void reverse (vector<double>& a) {
        size_t i = 0;
        size_t j = a.size() - 1;
        while (i < j) {
            double tmp;
            tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
            ++ i;
            -- j;
        }
    }

    vector<int> operator| (const vector<int>& a, const vector<int>& b) {
        vector<int> c;
        for (size_t i = 0; i < a.size(); ++ i) {
            c.push_back(a[i] | b[i]);
        }
        return c;
    }

    vector<int> operator& (const vector<int>& a, const vector<int>& b) {
        vector<int> c;
        for (size_t i = 0; i < a.size(); ++ i) {
            c.push_back(a[i] & b[i]);
        }
        return c;
    }


}  // namespace task
