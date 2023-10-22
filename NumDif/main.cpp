#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include "SimpFunctions.h"

using namespace std;

double func(double x) { // Это наша функция - в данном случае exp^x
    return exp(x);
}

int main(){
    double x0 = 1;
    double h = 0.1;
    int N = 3;
    vector<double> points(N);

//Сделаем шаблон для h = 1

    int min = int(N/2) + 1 - N;
    for(int i = 0, j = 0; i < N; j++){
        if (min + j != 0){
            points[i] = min + j;
            i++;
        }
        else{
            continue;
        }
    }

    std::cout << "Points are ";
    for(int i = 0; i < points.size(); i++){

        std::cout << points[i] << "; ";

    }
    std:: cout << std::endl;
    // std::cout << int(5/2) << std::endl;
    // points[0] = -2;
    // points[1] = -1;
    // points[2] = 1;
    // points[3] = 2;
    // points[4] = 3;

    vector<double> A = GetSolution(points);

    int CentCoefNum = 0;
    for(int i = 0; i < A.size(); i++){
        if (points[i] == x0){
            cout << "Central coef = " << A[i] << endl;
            CentCoefNum = i;
            break;
        }
    }

    cout << "Other coef = ";
    for (int i = 0; i < A.size(); i++){
        if (i == A.size()  - 1) break;
        if(i != CentCoefNum) cout << A[i] / h << ", ";
    }
    cout << A[A.size()-1] / h << endl;

    // производная для e^x в точке x0
    // считаем точки на шаблоне

    double dfdx = 0; //Производная
    for (int i = 0; i < N; i++) {
        dfdx += func(x0 + points[i] * h) * A[i] / h;
    }
    cout << "df/dx = " << dfdx << endl;


    // построим график зависимости логарифма ошибки от логарифма шага
    ofstream err, lnh;

    // окрываем файлы для записи
    err.open("err.txt"); 
    lnh.open("lnh.txt");
    err.precision(16);
    lnh.precision(16);
    double real_dfdx = exp(x0);  //реальное значение производной в точке x0
    double h_iteration;
    if (err.is_open() and lnh.is_open())
    {

        for(int i = 0; i < 16; i++){ //16 это максимальные кол-во нулей после запятой в значении h

            h_iteration = 1 * pow(10, -i);

            lnh << h_iteration << endl;
            cout << h_iteration << endl;

            dfdx = 0;
            for (int j = 0; j < N; j++) {
                dfdx += func(x0 + points[j] * h_iteration) * A[j] / h_iteration;
            }
            err << abs(real_dfdx - dfdx) << endl;
        }

    }
    err.close();
    lnh.close();

    return 0;
}
