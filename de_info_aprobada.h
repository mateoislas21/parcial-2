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
    double integrar( double lim_inf, double lim_sup);
    void revalue_arch();
    void rang_x(double x_min,double x_max);
    QColor color();
    void plot();
    double interrpolacion_en_y(double x_der, double x_izq, double y_der,double y_izq,double x_eval);
public slots:
    void plotear ();
    void consumo();
    void evaluar();
    private:
    Ui::de_info_aprobada *ui;
    QVector <double>x;
    QVector <double>y;
    QVector <double>t;
    QVector <double>bat;
    QVector <QString> Funciones;
    int Cant_x , N_funcions;
    double xmin,xmax,xd;
    double y_rms,x_rms;
};
#endif // DE_INFO_APROBADA_H
