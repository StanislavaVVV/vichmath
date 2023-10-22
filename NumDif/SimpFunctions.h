#include <vector>
#include <string>
#include <cmath>
using namespace std;

vector<double> GaussSolver(double** a, double* y, int n)
{
    double max;
    int k, index;
    const double eps = std::numeric_limits<double>::min();  //Точность
    vector<double> x;
    k = 0;
    for (; k < n; k++)
    {
        //Поиск строки с максимальным a[i][k]
        max = abs(a[k][k]);
        index = k;
        for (int i = k + 1; i < n; i++)
        {
            if (abs(a[i][k]) > max)
            {
                max = abs(a[i][k]);
                index = i;
            }
        }

        //Переносим строку с максимальным a[i][k] в самый верх
        for (int j = 0; j < n; j++)
        {
            double temp = a[k][j];
            a[k][j] = a[index][j];
            a[index][j] = temp;
        }

        //Также переносим соответствующий этой строке элемент в столбце решений наверх
        double temp = y[k];
        y[k] = y[index];
        y[index] = temp;

        // Нормализация уравнений
        for (int i = k; i < n; i++)
        {
            double temp = a[i][k];
            if (abs(temp) < eps) continue; //Для нулевого коэффициента пропустить
            for (int j = 0; j < n; j++)
                a[i][j] = a[i][j] / temp; //Делим всю строку на максимальный элемент
            y[i] = y[i] / temp;
            if (i == k)  continue; //Уравнение не вычитать само из себя
            for (int j = 0; j < n; j++)
                a[i][j] = a[i][j] - a[k][j]; //Вычитаем верхнюю строку из всех нижних
            y[i] = y[i] - y[k];
        }
    }
    //Обратная подстановка (имеем верхнетреугольную матрицу, начинаем искать x(i) с нижней строки, двигаясь наверх
    for (k = n - 1; k >= 0; k--)
    {
        x.insert(x.begin(), y[k]);
        for (int i = 0; i < k; i++)
            y[i] = y[i] - a[i][k] * y[k];
    }
    return x;
}

vector<double> GetSolution(const vector<double>& points) { 
    int n = points.size();
    
    double** A = new double* [n];// выделяем место под матрицу

    //Заполняем матрицу по схеме
    for (int i = 0; i < n; i++) {
        A[i] = new double[n];
        for (int j = 0; j < n; j++) {
            A[i][j] = pow(points[j], i);
        }
    }

    //Здесь лежат решения - для производной первого порядка = 1, остальные = 0
    double* y = new double[n];
    for (int i = 0; i < n; i++) {
        y[i] = 0;
    };
    y[1] = 1;

    //Метод Гаусса решения системы алгебраических уравн.
    vector<double> x = GaussSolver(A, y, n);

    delete[] y;

    for (int i = 0; i < n; i++) {
        delete[] A[i];
    };
    delete[] A;

    return (x);
}