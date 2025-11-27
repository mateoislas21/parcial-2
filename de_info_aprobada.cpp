#include "de_info_aprobada.h"
#include "ui_de_info_aprobada.h"
#include "muParser.h"
de_info_aprobada::de_info_aprobada(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::de_info_aprobada)
{
    ui->setupUi(this);
    N_funcions = -1;
    ui->widget->setInteraction(QCP::iRangeDrag,true);
    ui->widget->setInteraction(QCP::iRangeZoom,true);
    Funciones.resize(5);
    Funciones[0] =  "C:\\Users\\mateo\\OneDrive\\Documentos\\parcial 2024\\vi_1.dat";
    Funciones[1] =  "C:\\Users\\mateo\\OneDrive\\Documentos\\parcial 2024\\vi_2.dat";
    Funciones[2] =  "C:\\Users\\mateo\\OneDrive\\Documentos\\parcial 2024\\vi_3.dat";
    Funciones[3] = "C:\\Users\\mateo\\OneDrive\\Documentos\\parcial 2024\\vi_4.dat";
    Funciones[4] = "C:\\Users\\mateo\\OneDrive\\Documentos\\parcial 2024\\vi_5.dat";
}

de_info_aprobada::~de_info_aprobada()
{
    delete ui;
}

double de_info_aprobada::interrpolacion_en_y(int pizq, int pder)
{
    double m = (y[pder] - y[pizq])/(x[pder] - x[pizq]);
    double  x_media = (x[pder] + x[pizq])/2.00;
    double y_res = m*(x_media - x[pizq]) + y[pizq];
    return y_res;
}

double de_info_aprobada::interrpolacion_en_y(double x_der, double x_izq, double y_der,double y_izq)
{
    double m = (y_der - y_izq)/(x_der - x_izq);
    double  x_media = (x_der + x_izq)/2.00;
    double y_res = m*(x_media - x_izq) + y_izq;
    return y_res;
}

double de_info_aprobada::f(double x,int n)
{
    mu::Parser fx;
    fx.DefineVar(L"x",&x);
    fx.SetExpr(Funciones[n].toStdWString());
    return fx.Eval();
}
double de_info_aprobada::derivada_point(int punto, int n)
{
    if(punto < Cant_x){
        return(f(x[punto] + xd,n) - f(x[punto],n))/xd;}
    else{
        return (f(xmax+xd+xd,n)- f(xmax+ xd,n))/xd;
    }
}
double de_info_aprobada::integrar(int n , double lim_inf, double lim_sup)
{
    double area = 0.0;
    //QVector<double> x_integral,y_integral;
    //int d = 1;
    revalue(n);
    for (int i = 1; i < Cant_x; ++i) {

        if(x[i-1] >= lim_inf && x[i-1] <= lim_sup){
            area = area + ((y[i-1] + y[i])*xd)/2.00;
            // y_integral.resize(d);
            // x_integral.resize(d);
            // y_integral[d-1] = y[i-1]; x_integral[d-1] = x[i-1];
            // d++;
        }
    }
    if(x[Cant_x -1] <= lim_sup){
        area =  area + ((y[Cant_x-2] + y[Cant_x -1])*xd)/2.00;
        //y_integral.resize(d);
        //x_integral.resize(d);
        //y_integral[d-1] = y[Cant_x -1]; x_integral[d-1] = x[Cant_x-1];
    }
    return area;
}
void de_info_aprobada::revalue(int n)
{
    mu::Parser fx;
    fx.DefineVar(L"x",x.data());
    fx.SetExpr(Funciones[n].toStdWString());
    fx.Eval(y.data(), Cant_x);
}
void de_info_aprobada::rang_x(double x_min,double x_max)
{
    xmin = x_min;
    xmax = x_max;
    xd = (xmax-xmin)/(double)Cant_x;
    for(int i = 0; i< Cant_x; i++){
        x[i] = xmin + (double)i*xd;
    }
}

QColor de_info_aprobada::color()
{
    srand(time(0));
    QColor rgb;
    double r,g,b;
    r = rand()%256; g = rand()%256; b = rand()%256;
    rgb.setRgb(r,g,b);
    return rgb;
}

void de_info_aprobada::plot(int n)
{
    QPen rlb;
    rlb.setColor(color());
    revalue(n);
    ui->widget->graph(n)->setData(x,y);
    ui->widget->graph(n)->setPen(rlb);
    ui->widget->replot();
}

void de_info_aprobada::max_min()
{
    for(int i = 1; i< Cant_x-1 ; i++){
        if(y[i-1] < y[i] &&  y[i] > y[i+1]){
            //maximos

        }
        if(y[i-1] > y[i] &&  y[i] < y[i+1]){
            //minimos

        }
    }
}
void de_info_aprobada::revalue_arch(int n)
{

    FILE *f = fopen(Funciones[n].toUtf8().constData(),"rb");
    if(f == nullptr){
        qDebug()  << "error";
    }
    fseek(f,0,SEEK_END);
    Cant_x = ftell(f)/sizeof(double);
    Cant_x =  Cant_x /3.00;
    t.resize(Cant_x);
    x.resize(Cant_x);
    y.resize(Cant_x);
    fseek(f,0,SEEK_SET);
    for (int i = 0; i < Cant_x; i++) {
        double aux;
        fread(&aux,sizeof(double),1,f);  // tiempo
        t[i] = aux;
        fread(&aux,sizeof(double),1,f); // tension
        x[i] = aux;
        fread(&aux,sizeof(double),1,f); // corriente
        y[i] = aux;
    }
    fclose(f);
    rang_x(t[0],t[Cant_x-1]);
}
