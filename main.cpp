#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>

using namespace std; 

double function(double x){
    double a = 1 - x*x*x*x;
    double y = pow(a, 1.0 / 3.0);
    return y;
}

vector<double> spline(double x0, double y0, double x1, double y1){
    vector<double> coeff(4,0);
    double N = 1000;
    coeff[0] = (double)(rand())/RAND_MAX * N;
    coeff[1] = 2;
    coeff[2] = 3;
    coeff[3] = 4;
    double a = coeff[0]; double b = coeff[1]; 
    double c = coeff[2]; double d = coeff[3];

    if((a*(x0*x0*x0) + b*(x0*x0) + c*x0 + d == y0 &&
    a*(x1*x1*x1) + b*(x1*x1) + c*x1 + d == y1) == true ){
        double der_y0 = 3*(x0*x0) + 2*b*x0 + c; //вычисляем производные 
        double der_y1 = 3*(x1*x1) + 2*b*x1 + c;
        if(der_y0 == der_y1){
            return coeff;
        }
    }
}

/*
vector<double> spline2(double x1, double y1, double x2, double y2){
    vector<double> coeff(4,0);
    coeff[0] = 1;
    coeff[1] = 2;
    coeff[2] = 3;
    coeff[3] = 4;
    double a = coeff[0]; double b = coeff[1]; 
    double c = coeff[2]; double d = coeff[3];

    if((a*(x1*x1*x1) + b*(x1*x1) + c*x1 + d == y1 &&
    a*(x2*x2*x2) + b*(x2*x2) + c*x2 + d == y2) == true ){
        double der_y2 = 3*(x2*x2) + 2*b*x2 + c; //вычисляем производные 
        double der_y1 = 3*(x1*x1) + 2*b*x1 + c;
        if(der_y2 == der_y1){
            return coeff;
        }
    }
}*/

int main(){
    double dots_x[3];
    double dots_y[3];
    int i = 0;
    ofstream f2out; // поток для записи
    f2out.open("x_value.txt"); // окрываем файл для запи
    if (f2out.is_open()){
        for(double k = 0; k <= 0.9; k = k+0.45){
            dots_x[i] = k;
            f2out << dots_x[i] << endl;
            i++;
        }
    }
    f2out.close();
    
    ofstream fout; // поток для записи
    fout.open("y_value.txt"); // окрываем файл для записи
    if (fout.is_open()){
        for(int i = 0; i < 3; i++){
            double m = function(dots_x[i]);
            dots_y[i] = m;
            fout << dots_y[i] << endl;
        }
    }
    fout.close();

    vector<double> coeff_L = spline(dots_x[0], dots_y[0], dots_x[1], dots_y[1]);
    vector<double> coeff_R = spline(dots_x[1], dots_y[1], dots_x[2], dots_y[2]);


    return 0;
}