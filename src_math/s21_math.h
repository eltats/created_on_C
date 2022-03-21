#ifndef SRC_S21_MATH_H_
#define SRC_S21_MATH_H_

#if __APPLE__
    #define S21_APPLE
#elif _WIN32
    #define S21_MINGW
#elif __linux__
    #define S21_LINUX
#else
    #define S21_LINUX
#endif

#define S21_NAN __builtin_nanf("")
#define S21_NEG_NAN -0.0/0.0
#define S21_POS_INF 1.0/0.0
#define S21_NEG_INF -1.0/0.0
#define S21_EPS 1e-16
#define S21_NEG_EPS -1e-16
#define S21_PI 3.14159265358979323846
#define S21_PI_2 1.57079632679489661923
#define S21_PI_4 0.78539816339744830962
#define S21_3PI_2 4.712388980384689674
#define S21_PI_L 3.141592653589793238462643383279502884L
#define S21_E 2.718281828459045235360287471352L
#define S21_LOG10 2.3025850929940459L
#define S21_LOG2 0.6931471805599453L


static const double epsilon = 1e-6;
long int s21_abs(int x);
long double s21_fabs(double x);
long double s21_sqrt(double x);
long double s21_fmod(double x, double y);
long double s21_acos(double x);
long double s21_asin(double x);
long double s21_atan(double x);
long double s21_ceil(double x);
long double s21_cos(double x);
long double s21_exp(double x);
long double s21_floor(double x);
long double s21_log(double x);
long double s21_sin(double x);
long double s21_tan(double x);
long double s21_pow(double base, double exp);

// narchang
int s21_isnan(double x);
int s21_isinf(double x);

// sredguar
int dEquals(long double a, long double b, int rate);
int isWholeInteger(long double ld_num, int rate);
long double s21_powInteger(long double base, int exp);
int getSign(double x);
long int s21_fact(int n);
double normalizeToRadian(double x);
long double getSin(double x);
long double getCos(double x);

long double s21_taylor(double x);


#endif  // SRC_S21_MATH_H_
