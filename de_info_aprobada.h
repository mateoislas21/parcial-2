#ifndef DE_INFO_APROBADA_H
#define DE_INFO_APROBADA_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class de_info_aprobada;
}
QT_END_NAMESPACE

class de_info_aprobada : public QMainWindow
{
    Q_OBJECT
public:
    de_info_aprobada(QWidget *parent = nullptr);
    ~de_info_aprobada();
    double interrpolacion_en_y (int pizq,int pder);
    double f(double x, int n);
    double derivada_point(int punto, int n);
    double integrar(int  n , double lim_inf, double lim_sup);
    void revalue(int n);
    void revalue_arch(int n);
    void rang_x(double x_min,double x_max);
    QColor color();
    void plot(int n);
    void max_min();
    double interrpolacion_en_y(double x_der, double x_izq, double y_der,double y_izq);
public slots:

private:
    Ui::de_info_aprobada *ui;
    QVector <double>x;
    QVector <double>y;
    QVector <double> t;
    QVector <QString> Funciones;
    int Cant_x , N_funcions;
    double xmin,xmax,xd;
};
#endif // DE_INFO_APROBADA_H
