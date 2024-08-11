#ifndef MY_UTILS_H_
#define MY_UTILS_H_

#include <bits/stdc++.h>

using namespace std;

#include "myVector.h"

const double EPS = 1e-6;

const double D_PI = 6.283185307179586476925286766559;

inline bool in_list(const int &x, const vector<int> &li) {
    for (auto e: li)
        if (e == x)
            return true;
    return false;
}

inline bool is_less_equal(const double &a, const double &b) {
    return a <= b + EPS;
}

inline bool is_less_than(const double &a, const double &b) {
    return a < b - EPS;
}

inline bool is_equal(const double &a, const double &b) {
    return abs(a - b) <= EPS;
}

inline double get_angle(const Vector<double> &a, const Vector<double> &b) {
    return acos(a.dot(b) / (norm(a) * norm(b)));
}

inline double get_distance(const Vector<double> &a, const Vector<double> &b) {
    return norm(a - b);
}

inline double square(const double &x) {
    return x * x;
}

inline double cube(const double &x) {
    return x * x * x;
}

inline vector<string> split(const string &target, const string &delimiter) {
    vector<string> res;
    int pos = -1, nxt = 0;
    while ((nxt = (int) target.find(delimiter, pos + 1)) != -1) {
        res.push_back(target.substr(pos + 1, nxt - pos - 1));
        pos = nxt + (int) delimiter.size() - 1;
    }
    res.push_back(target.substr(pos + 1, target.size() - pos - 1));
    return res;
}

inline int stringToInt(const string &target) {
    stringstream ss;
    ss << target;
    int res;
    ss >> res;
    return res;
}

inline void replace_all(string &s, string const &toReplace, string const &replaceWith) {
    string buf;
    size_t pos = 0;
    size_t prevPos;

    // Reserves rough estimate of final size of string.
    buf.reserve(s.size());

    while (true) {
        prevPos = pos;
        pos = s.find(toReplace, pos);
        if (pos == std::string::npos)
            break;
        buf.append(s, prevPos, pos - prevPos);
        buf += replaceWith;
        pos += toReplace.size();
    }

    buf.append(s, prevPos, s.size() - prevPos);
    s.swap(buf);
}

inline double stringToDouble(const string &target) {
    stringstream ss;
    ss << target;
    double res;
    ss >> res;
    return res;
}

inline ostream &operator<<(ostream &os, const vector<pair<double, int>> &li) {
    for (int i = 0; i < (int) li.size(); i++)
        os << (!i ? "[" : ", ") << "(" << li[i].first << ", " << li[i].second << ")";
    os << "]";
    return os;
}

class Random {
    mt19937_64 gen;
public:
    Random() {
        uint64_t timeSeed = chrono::high_resolution_clock::now().time_since_epoch().count();
        seed_seq ss{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed >> 32)};
        gen.seed(ss);
    }

    double random() {
        uniform_real_distribution<> dis(0.0, 1.0);
        return dis(gen);
    }

    int randInt(int l, int h, bool exclude = false) {
        uniform_int_distribution<> dis(l, h);
        int res = dis(gen);
        if (exclude) {
            while (res == h)
                res = dis(gen);
        }
        return res;
    }

    double uniform(double l, double h, bool exclude = false) {
        uniform_real_distribution<> dis(l, h);
        double res = dis(gen);
        if (exclude) {
            while (res == h)
                res = dis(gen);
        }
        return res;
    }

    Vector<double> uniform(double l, double h, int s, bool exclude = false) {
        vector<double> res(s);
        for (int i = 0; i < s; i++)
            res[i] = uniform(l, h, exclude);
        return Vector<double>(res);
    }

    double normal(double m, double s) {
        normal_distribution<> dis{m, s};
        return dis(gen);
    }

    double cauchy(double m, double s) {
        cauchy_distribution<> dis{m, s};
        return dis(gen);
    }

    template<typename T>
    T choice(Vector<T> a) {
        return a[randInt(0, a.length, true)];
    }

    template<typename T>
    Vector<T> choice(Vector<T> a, int s) {
        vector<T> tmp;
        tmp.reserve(s);
        while (s--)
            tmp.push_back(a[randInt(0, a.length, true)]);
        return Vector<T>(tmp);
    }

    template<typename T>
    Vector<T> choices(Vector<T> a, int s) {
        return a.randomChoice(gen, s);
    }
};

static Random random;

#endif // MY_UTILS_H_
