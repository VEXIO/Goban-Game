#ifndef HELPERS_H_
#define HELPERS_H_

#define threshold 0.1
#define upper(x) ((x)+((x)>0?1:-1)*(x)*threshold)
#define lower(x) ((x)-((x)>0?1:-1)*(x)*threshold)
// math

template<class T>
bool greaterThan(const int a, const T b) {
    return a > upper(b);
}

template<class T>
bool greaterOrEqualThan(const int a, const T b) {
    return a > lower(b);
}

template<class T>
bool smallerThan(const int a, const T b) {
    return a < lower(b);
}

template<class T>
bool smallerOrEqualThan(const int a, const T b) {
    return a < upper(b);
}

template<class T>
bool equal(const int a, const T b) {
    return (a >= lower(b)) && (a <= upper(b));;
}

#endif //HELPERS_H
