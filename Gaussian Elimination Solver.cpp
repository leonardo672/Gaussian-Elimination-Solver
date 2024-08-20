#include <iostream>
using namespace std;
// Вывод системы уравнений
void System_Equation_Out(double** a, double* y, int n)
{
for (int rows = 0; rows < n; rows++)
{
for (int colmns = 0; colmns < n; colmns++)
{
cout << a[rows][colmns] << "*x" << colmns;
if (colmns < n - 1) // условие для печати + до предпоследнего шага
cout << " + ";
}
cout << " = " << y[rows] << endl; // = is after the equation then value of y
}
return;
}
double *Gaussian_Elimination(double** a, double* y, int n)
{
double* x, max;
int k, index;
const double eps = 0.00001;  // точность
x = new double[n];
k = 0;
while (k < n)
{
// Поиск строки с максимальным a[rows][k]
max = abs(a[k][k]); // инициализация для max, равного = abs(a[k][k])
index = k;
for (int rows = k + 1; rows < n; rows++)
{
if (abs(a[rows][k]) > max)
{
max = abs(a[rows][k]);
index = rows;
}
}
// Перестановка строк
if (max < eps)
{
// нет ненулевых диагональных элементов
cout << "Решение получить невозможно из-за нулевого столбца ";
cout << index << " матрицы A" << endl;
return 0;
}
for (int colmns = 0; colmns < n; colmns++)
{
double temp = a[k][colmns];
a[k][colmns] = a[index][colmns];
a[index][colmns] = temp;
}
double temp = y[k];
y[k] = y[index];
y[index] = temp;
// Нормализация уравнений
for (int rows = k; rows < n; rows++)
{
double temp = a[rows][k];
if (abs(temp) < eps) continue; // для нулевого коэффициента пропустить
for (int colmns = 0; colmns < n; colmns++)    // ratio = Это дробное отношение для получения значений коэффициентов x, y, z, образующих строки матрицы
a[rows][colmns] = a[rows][colmns] / temp; // X - Левая часть уравнения - ratio - соотношение = Для процесса деления между элементом первого уравнения и элементом второго уравнения
y[rows] = y[rows] / temp;           // Y - Правая часть уравнения ratio - соотношение = Для процесса деления между элементом первого уравнения и элементом второго уравнения
if (rows == k)  continue; // уравнение не вычитать само из себя
for (int colmns = 0; colmns < n; colmns++)
a[rows][colmns] = a[rows][colmns] - a[k][colmns];
y[rows] = y[rows] - y[k];
}
k++;  // для вычисления члена в матрице
}
// обратная подстановка
for (k = n - 1; k >= 0; k--)
{
x[k] = y[k];
for (int rows = 0; rows < k; rows++)
y[rows] = y[rows] - a[rows][k] * x[k];
}
return x;
}
int main()
{
double** a, * y, * x;
int n;
system("chcp 1251"); // Windows-1251 is an 8-bit character encoding, designed to cover languages that use the Cyrillic script such as Russian, Ukrainian,
// Belarusian, Bulgarian, Serbian Cyrillic, Macedonian and other languages.
system("cls");
cout << "Введите количество уравнений: ";
cin >> n;
a = new double* [n]; // dynamic memory
y = new double[n];   // dynamic memory
for (int rows = 0; rows < n; rows++)
{
a[rows] = new double[n];   // dynamic memory
for (int colmns = 0; colmns < n; colmns++)
{
cout << "a[" << rows << "][" << colmns << "]= ";
cin >> a[rows][colmns];
}
}
for (int rows = 0; rows < n; rows++)
{
cout << "y[" << rows << "]= ";
cin >> y[rows];
}
System_Equation_Out(a, y, n);
x = Gaussian_Elimination(a, y, n);
for (int rows = 0; rows < n; rows++)
cout << "x[" << rows << "]=" << x[rows] << endl;
cin.get(); cin.get(); // cin.get(string_name, size);
// get () используется для доступа к массиву символов.
// Он включает символы пробела. Как правило, cin с оператором извлечения (>>) завершается при обнаружении пробела.
return 0;
}
