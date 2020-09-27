#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

double myfun(double x) {
    return (cos(x)*tan(x));
}

int main() {
    const float eps = 0.1;
    double b = 0;
    double a = -2;
    unsigned int N = 1;
    double x;
    double current_error = 1;

    cout << "Passive search:" << endl;
    cout << "_______________________________\n"
            "|Количество|     Значение x   |\n"
            "|точек (N) |     в минимуме   |\n"
            "-------------------------------" << endl;
    while (current_error > eps){
        double min = 1.7976931348623158*pow(10, 308);
        double minx = 0;
        for (int k = 1; k < N + 1; k++) {
            x = ((b - a) * k / (N + 1)) + a;
            if (myfun(x) < min){
                min = myfun(x);
                minx = x;
            }
        }
        current_error = (b - a) / (N + 1);
        cout << "|" << setw(10) << N << "|" << setw(7) << round(minx*1000)/1000 << " +- "
             << setw(7) << round(current_error*1000)/1000 << "|" << endl;
        N++;
    }
    cout << "-------------------------------" << endl;

    const double delta = 0.01;
    double F_ak, F_bk;
    cout << "Dichotomy method:" << endl;
    cout << "_____________________________________________________________\n"
            "|   Начало  |   Конец   |   Длина   |           |           |\n"
            "| интервала | интервала | интервала |   f(ak)   |   f(bk)   |\n"
            "|    (ak)   |   (bk)    |    (l)    |           |           |\n"
            "-------------------------------------------------------------" << endl;
    cout << "|" << setw(11) << a << "|" << setw(11) << b << "|"
    << setw(11) << b - a << "|" << setw(11) <<
    myfun(a) << "|" <<  setw(11) << myfun(b) << "|" << endl;
    double ak, bk;
    while ((b - a) > eps){
        F_ak = (b + a)/2 - delta;
        F_bk = (b + a)/2 + delta;
        ak = (myfun(F_ak) < myfun(F_bk))? F_ak: F_bk;
        bk = (myfun(F_ak) < myfun(F_bk))? F_bk: F_ak;
        a = (ak>bk)?ak:a;
        b = (ak<=bk)?bk:b;
        if ((b - a) < eps){
            cout << "|" << setw(11) << a << "|" << setw(11) << b << "|"
                 << setw(11) << (b - a) << "|" << "      l < epsilon      |" << endl;
            break;
        }
        cout << "|" << setw(11) << a << "|" << setw(11) << b << "|"
             << setw(11) << (b - a) << "|" << setw(11) <<
             ak << "|";
        current_error = 0.5 * (b - a);
        cout << setw(11) << bk << "|" << endl;
    }
    cout << "-------------------------------------------------------------" << endl;
    cout << "min = " <<  (a + b) / 2 << " +- " << current_error << "\n";
    return 0;
}