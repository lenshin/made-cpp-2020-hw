#pragma once

#include <vector>
#include <iostream>
#include "math.h"

using std::vector;
using std::cout;

namespace task {

  const double MYEPS = 1e-7;

  vector<double> operator+(const vector<double> &a, const vector<double> &b) {
    vector<double> c(a.size());
    for (size_t i = 0; i < a.size(); ++i) {
      c[i] = a[i] + b[i];
    }
    return c;
  }

  vector<double> operator+(const vector<double> &a) {
    return a;
  }

  vector<double> operator-(const vector<double> &a, const vector<double> &b) {
    vector<double> c(a.size());
    for (size_t i = 0; i < a.size(); ++i) {
      c[i] = a[i] - b[i];
    }
    return c;
  }

  vector<double> operator-(const vector<double> &a) {
    vector<double> c(a.size());
    for (size_t i = 0; i < a.size(); ++i) {
      c[i] = -a[i];
    }
    return c;
  }

  double operator*(const vector<double> &a, const vector<double> &b) {
    double c = 0;
    for (size_t i = 0; i < a.size(); ++i) {
      c += a[i] * b[i];
    }
    return c;
  }

  vector<double> operator%(const vector<double> &a, const vector<double> &b) {
    vector<double> c(3);
    c[0] = a[1] * b[2] - a[2] * b[1];
    c[1] = -a[0] * b[2] + a[2] * b[0];
    c[2] = a[0] * b[1] - a[1] * b[0];

    return c;
  }

  bool operator||(const vector<double> &a, const vector<double> &b) {
    double scalar = a * b;
    double norm_a = sqrt(a * a);
    double norm_b = sqrt(b * b);
    if (norm_a > MYEPS && norm_b > MYEPS) {
      double cosAngle = fabs(scalar / (norm_a * norm_b));
      if (fabs(1 - cosAngle) < MYEPS) {
        return true;
      }
    }
    return false;
  }

  bool operator&&(const vector<double> &a, const vector<double> &b) {
    if (a || b) {
      for (size_t i = 1; i < a.size(); ++i) {
        if (fabs(b[i]) > 0) {
          if (a[i] / b[i] < 0) {
            return false;
          }
        }
      }
      return true;
    }
    return false;
  }

  std::istream &operator>>(std::istream &is, vector<double> &a) {
    a.clear();
    size_t size_a;
    is >> size_a;
    for (size_t i = 0; i < size_a; ++i) {
      double x;
      is >> x;
      a.push_back(x);
    }
    return is;
  }

  std::ostream &operator<<(std::ostream &os, const vector<double> &a) {
    for (size_t i = 0; i < a.size(); ++i) {
      os << a[i] << " ";
    }
    os << std::endl;
    return os;
  }

  void reverse(vector<double> &a) {
    size_t i = 0;
    size_t j = a.size() - 1;
    while (i < j) {
      std::swap(a[i], a[j]);
      ++i;
      --j;
    }
  }

  vector<int> operator|(const vector<int> &a, const vector<int> &b) {
    vector<int> c(a.size());
    for (size_t i = 0; i < a.size(); ++i) {
      c[i] = a[i] | b[i];
    }
    return c;
  }

  vector<int> operator&(const vector<int> &a, const vector<int> &b) {
    vector<int> c(a.size());
    for (size_t i = 0; i < a.size(); ++i) {
      c[i] = a[i] & b[i];
    }
    return c;
  }


}  // namespace task
