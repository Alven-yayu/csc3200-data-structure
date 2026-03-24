#include "student_math.h"

namespace student_std {

const double PI = 3.14159265358979323846;

// 实现n次方
double npow(double x, int n) {
    if (n == 0) return 1.0;
    if (x == 0.0) return 0.0;

    int exp;
    double base;
    double result = 1.0;

    if (n < 0) {
        exp = -n;         
        base = 1.0 / x;   
    } else {
        exp = n;          
        base = x;         
    }
    for (int i = 0; i < exp; ++i) {  
        result = base * result;
    }
    return result;
}

// 实现阶乘.
double factorial(int n) {
    if (n <= 0) return 1.0;  
    double result = 1.0;    
    for (int i = 1; i <= n; ++i) {
        result = i * result;
    }
    return result;
}

// 实现绝对值
double abs(double x) {
    if (x < 0) {
        return -x;  
    } else {
        return x;   
    }
}

// 将角度归一化到 [-PI, PI]（新增：提升大角度精度）
double normalize_rad(double x) {
    while (x > PI) x -= 2 * PI;
    while (x < -PI) x += 2 * PI;
    return x;
}

// 计算三角函数(弧度制)
double sin(double x) {
    x = normalize_rad(x);  
    double sum = 0.0;
    double term = x;
    int k = 0;

    while (abs(term) > 1e-15) {
        sum += term;
        k++;
        term = -term * x * x / ((2 * k) * (2 * k + 1));
    }
    return sum;
}

double cos(double x) {
    x = normalize_rad(x);  
    double sum = 0.0;
    double term = 1.0;  
    int k = 0;

    while (abs(term) > 1e-15) {
        sum += term;
        k++;
        
        if (k >= 1) {
            term = -term * x * x / ((2 * k - 1) * (2 * k));
        }
    }
    return sum;
}

double tan(double x) {
    double cosx = cos(x);
    if (abs(cosx) < 1e-10) {
        if (sin(x) > 0) {
            return 1e10;
        } else {
            return -1e10;
        }
    } else {
        return sin(x) / cosx;
    }
}

double cot(double x) {
    double sinx = sin(x);
    if (abs(sinx) < 1e-10) {
        if (cos(x) > 0) {
            return 1e10;
        } else {
            return -1e10;
        }
    } else {
        return cos(x) / sinx;
    }
}

// 将角度制转化为弧度制
double deg_to_rad(double x) {
    return x * PI / 180.0;
}

// 计算三角函数（角度制）
double sin_deg(double x) {
    return sin(deg_to_rad(x));
}

double cos_deg(double x) {
    return cos(deg_to_rad(x));
}

double tan_deg(double x) {
    return tan(deg_to_rad(x));
}

double cot_deg(double x) {
    return cot(deg_to_rad(x));
}

}