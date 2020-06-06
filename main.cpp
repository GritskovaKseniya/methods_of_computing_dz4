#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>

using namespace std; 

// задаем функцию из условия
double function(double x){
    double a = 1 - pow(x, 4.0);
    double y = pow(a, 1.0 / 3.0);
    return y;
}

int spline(double x0, double y0, double x1, double y1, double x2, double y2){
    // тут еще нужен цикл с условием: выполнять его, пока не найдем нужные коэффициенты
    double coeff_L[4];
    double coeff_R[4];
    double coeff[8];
    double N = 1000;
    for(int i = 0; i < 4; i++){
        coeff_L[i] = (double)(rand())/RAND_MAX * N;
        coeff_R[i] = (double)(rand())/RAND_MAX * N;
    }

    double a1 = coeff_L[0]; double b1 = coeff_L[1]; 
    double c1 = coeff_L[2]; double d1 = coeff_L[3];

    double a2 = coeff_R[0]; double b2 = coeff_R[1]; 
    double c2 = coeff_R[2]; double d2 = coeff_R[3];

    if((  ( (a1*pow(x0, 3.0) + b1*pow(x0, 2.0) + c1*x0 + d1 == y0) &&
            (a1*pow(x1, 3.0) + b1*pow(x1, 3.0) + c1*x1 + d1 == y1) )
        && ( (a2*pow(x1, 3.0) + b2*pow(x1, 2.0) + c2*x0 + d2 == y1) &&
            (a2*pow(x2, 3.0) + b2*pow(x2, 3.0) + c2*x2 + d2 == y2) ) ) == true ){
        
        double der_yL = 3*(x1, 2.0)*a1 + 2*b1*x1 + c1; //вычисляем первые производные 
        double der_yR = 3*(x1, 2.0)*a2 + 2*b2*x1 + c2;
        
        if(der_yL == der_yR){
            
            double der2_yL = 6*a1*x1 + 2*b1; //вычисляем вторые производные
            double der2_yR = 6*a2*x1 +2*b2;;
            if(der2_yL == der2_yR){
                ofstream f3out;
                f3out.open("coeff.txt"); // окрываем файл для записи значений х
                if (f3out.is_open()){
                    for(int i = 0; i < 4; i++){
                        f3out << coeff_L[i] << " " << coeff_R[i] << endl;
                        return 0;
                    }
                }
                f3out.close();
            }
        }
    }
}

int main(){
    //массив точек х и у
    double dots_x[3];
    double dots_y[3];
    int i = 0;
    ofstream f2out; // поток для записи
    f2out.open("x_value.txt"); // окрываем файл для записи значений х
    if (f2out.is_open()){
        for(double k = 0; k <= 0.9; k = k+0.45){
            dots_x[i] = k;
            f2out << dots_x[i] << endl; 
            i++;
        }
    }
    f2out.close();
    
    ofstream fout; // поток для записи
    fout.open("y_value.txt"); // окрываем файл для записи значений у
    if (fout.is_open()){
        for(int i = 0; i < 3; i++){
            double m = function(dots_x[i]);
            dots_y[i] = m;
            fout << dots_y[i] << endl;
        }
    }
    fout.close();

    //формируем вектора нужных коэффициентов
    spline(dots_x[0], dots_y[0], dots_x[1], dots_y[1], dots_x[2], dots_y[2]);

    //создаем выборку точек из [0;0,45] и (0.45,0.9] 
    // узнаем в какой сплайн попадает точка
    // подставляем ее в формулу с подходящими коэффициентами
    // полученный х и у записываем в файл  
    return 0;
}