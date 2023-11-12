#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

double func(double x) { // Это наша функция - в данном случае sin(x)
    return sin(x);
}

double GetRealIntegral(double a, double b){ //Реально значение интеграла sin x (нижний предел = a, верхний предел = b)
    return -cos(b) - (-cos(a));
}

class Interval{

    private:
        double start;
        double end;

        double MiniIntegrate3(double start3, double end3){
            double result3 = 0; // Значение интеграла на маленьком промежутке 

            //Квадратуры Гаусса (для инетрвала -1, +1)
            //Источник https://en.wikipedia.org/wiki/Gaussian_quadrature
            const double points[] = { (-1) * sqrt(double(3)/5), double(0), sqrt(double(3)/5) };
            const double values[] = { double(5)/9, double(8)/9, double(5)/9};

            //Множители для удобства
            double pl = (end3 + start3)/2;
            double mn = (end3 - start3)/2;

            //Значение интеграла
            for(int i = 0; i < 3; i++){
                result3 += mn * values[i] * func(mn * points[i] + pl);
            }

            return result3;
        }

        double MiniIntegrate5(double start5, double end5){
            double result5 = 0; // Значение интеграла на маленьком промежутке 

            //Квадратуры Гаусса (для инетрвала -1, +1)
            //Источник https://en.wikipedia.org/wiki/Gaussian_quadrature
            const double points[] = { sqrt(5.0 + 2 * sqrt(10.0/7)) / (-3.0), sqrt(5.0 - 2 * sqrt(10.0/7)) / (-3.0), 0, sqrt(5.0 - 2 * sqrt(10.0/7)) / (3.0), sqrt(5.0 + 2 * sqrt(10.0/7)) / (3.0) };
            const double values[] = { (322 - 13*sqrt( double(70) )) / 900, (322 + 13*sqrt( double(70))) / 900, 128.0/225, (322 + 13*sqrt( double(70))) / 900, (322 - 13*sqrt( double(70))) / 900};

            //Множители для удобства
            double pl = (end5 + start5)/2;
            double mn = (end5 - start5)/2;

            //Значение интеграла
            for(int i = 0; i < 5; i++){
                result5 += mn * values[i] * func(mn * points[i] + pl); 
            }

            return result5;
        }

    public:
        Interval(double start_build, double end_build){
            start = start_build;
            end = end_build;
        };

        double Integrate3(int NumberOfMiniIntervals){
            // h - длина отрезка, на которые разбиваем наш отрезок
            // N - кол-во точек для интегрирования в квадратурах Гаусса (сделано для N = 3 и N = 5)

            double result = 0; //Значение интеграла

            //Разбиение на подотрезки
            for(int i = 0; i < NumberOfMiniIntervals; i++){
                double MiniStart = start + i * (end - start) / NumberOfMiniIntervals;
                double MiniEnd = MiniStart + (end - start) / NumberOfMiniIntervals; 
                result += MiniIntegrate3(MiniStart, MiniEnd);
            }

            return result;
        };

        double Integrate5(int NumberOfMiniIntervals){
            // h - длина отрезка, на которые разбиваем наш отрезок
            // N - кол-во точек для интегрирования в квадратурах Гаусса (сделано для N = 3 и N = 5)

            double result = 0; //Значение интеграла

            //Разбиение на подотрезки
            for(int i = 0; i < NumberOfMiniIntervals; i++){
                double MiniStart = start + i * (end-start) / NumberOfMiniIntervals;
                double MiniEnd = MiniStart + (end - start) / NumberOfMiniIntervals; 
                result += MiniIntegrate5(MiniStart, MiniEnd);
            }

            return result;
        };



};




int main(){
    double a,b;
    a = 0; //Начало отрезка интегрирования
    b = 10;// Конец отрезка интегрирования

    Interval MySection(0,10);
    
    //cout << MySection.Integrate5(1) << endl;


    // построим график зависимости логарифма ошибки от логарифма шага
    ofstream h, ln3, ln5;

    // окрываем файлы для записи
    h.open("h.txt"); 
    ln3.open("ln3.txt");
    ln5.open("ln5.txt");
    h.precision(16);
    ln3.precision(16);
    ln5.precision(16);

    double real_integr = GetRealIntegral(a,b);

    double N_iteration;

    if (h.is_open() and ln3.is_open() and ln5.is_open())
    {

        for(int i = 0; i < 8; i++){ 

            N_iteration = 1 * pow(10, i);

            h << (b-a)/N_iteration << endl;
            ln3 << abs(real_integr - MySection.Integrate3(N_iteration)) << endl;
            ln5 << abs(real_integr - MySection.Integrate5(N_iteration)) << endl;

        }

    }
    h.close();
    ln3.close();
    ln5.close();

    return 0;
}
