#ifndef MY_VECTOR_H_
#include<math.h>
#define MY_VECTOR_H_

template<typename T>
class Vector {
    T *a{nullptr};
public:
    int length{0};

    Vector() = default;

    explicit Vector(const vector<T> &a) {
        this->length = a.size();
        delete this->a;
        this->a = new T[length];
        for (int i = 0; i < length; i++)
            this->a[i] = a[i];
    }

    explicit Vector(const int &length, T *a) {
        this->length = length;
        delete this->a;
        this->a = new T[length];
        for (int i = 0; i < length; i++)
            this->a[i] = a[i];
    }

    Vector(const Vector<T> &b) {
        this->length = b.length;
        delete this->a;
        this->a = new T[length];
        for (int i = 0; i < length; i++)
            this->a[i] = b[i];
    }

    Vector<T> &operator=(const Vector<T> &b) {
        Vector<T> tmp(b);
        tmp.swap(*this);
        return *this;
    }

    ~Vector() {
        length = 0;
        delete a;
        a = nullptr;
    }

    void swap(Vector<T> &b) {
        std::swap(this->length, b.length);
        std::swap(this->a, b.a);
    }

    T operator[](const int &index) const {
        return a[index];
    }

    void set(const int &index, const T &value) {
        a[index] = value;
    }

    Vector<T> operator+(const Vector<T> &b) const {
        T res[this->length];
        for (int i = 0; i < this->length; i++) {
            res[i] = this->a[i] + b[i];
        }
        return Vector<T>(this->length, res);
    }

    Vector<T> operator-(const Vector<T> &b) const {
        T res[this->length];
        for (int i = 0; i < this->length; i++) {
            res[i] = this->a[i] - b[i];
        }
        return Vector<T>(this->length, res);
    }

    Vector<T> operator*(const Vector<T> &b) const {
        T res[this->length];
        for (int i = 0; i < this->length; i++) {
            res[i] = this->a[i] * b[i];
        }
        return Vector<T>(this->length, res);
    }

    Vector<T> operator*(const T &b) const {
        T res[this->length];
        for (int i = 0; i < this->length; i++) {
            res[i] = this->a[i] * b;
        }
        return Vector<T>(this->length, res);
    }

    Vector<T> operator/(const Vector<T> &b) const {
        T res[this->length];
        for (int i = 0; i < this->length; i++) {
            res[i] = b[i] ? (this->a[i] / b[i]) : 0;
        }
        return Vector<T>(this->length, res);
    }

    Vector<T> operator/(const T &b) const {
        T res[this->length];
        for (int i = 0; i < this->length; i++) {
            res[i] = b ? (this->a[i] / b) : 0;
        }
        return Vector<T>(this->length, res);
    }

    T dot(const Vector<T> &b) const {
        T res = 0;
        for (int i = 0; i < this->length; i++) {
            res += this->a[i] * b[i];
        }
        return res;
    }

    Vector<T> square() const {
        T res[this->length];
        for (int i = 0; i < this->length; i++) {
            res[i] = this->a[i] * this->a[i];
        }
        return Vector<T>(this->length, res);
    }

    Vector<T> randomChoice(mt19937_64 gen, int s) {
        vector<T> b = a;
        random_shuffle(b.begin(), b.end(), [&](int i) {
            return gen() % i;
        });
        while ((int) b.size() > s)
            b.pop_back();
        return Vector<T>(b);
    }
};

template<typename T>
Vector<T> maximum(const Vector<T> &a, const Vector<T> &b) {
    T res[a.length];
    for (int i = 0; i < a.length; i++) {
        res[i] = max(a[i], b[i]);
    }
    return Vector<T>(a.length, res);
}
template<typename T>
Vector<T> maximum1(const Vector<T> &a, const Vector<T> &b) {
    T res11[a.length];
    for (int i = 0; i < a.length; i++) {
        res11[i] = log((a[i]+1)/ (b[i]+1)) / (max(log(a[i]+1), log(b[i]+1)));
    }
    return Vector<T>(a.length, res11);
}
template<typename T>
T norm(const Vector<T> &a) {
    T res = 0;
    for (int i = 0; i < a.length; i++) {
        res += a[i] * a[i];
    }
    return sqrt(res);
}

template<typename T>
T sum(const Vector<T> &a) {
    T res = 0;
    for (int i = 0; i < a.length; i++) {
        res += a[i];
    }
    return res;
}

template<typename T>
T amax(const Vector<T> &a) {
    T res = a[0];
    for (int i = 0; i < a.length; i++) {
        res = max(res, a[i]);
    }
    return res;
}

template<typename T>
ostream &operator<<(ostream &os, const Vector<T> &a) {
    os << "[";
    for (int i = 0; i < a.length; i++)
        os << a[i] << ((i == a.length - 1) ? "]" : ", ");
    return os;
}

#endif // MY_VECTOR_H_
