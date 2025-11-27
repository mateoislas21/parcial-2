#include "de_info_aprobada.h"
#include "ui_de_info_aprobada.h"
#include"time.h"
de_info_aprobada::de_info_aprobada(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::de_info_aprobada)
{
    ui->setupUi(this);
    ui->widget_bat->setInteraction(QCP::iRangeDrag,true);
    ui->widget_bat->setInteraction(QCP::iRangeZoom,true);
    ui->widget_cord_x->setInteraction(QCP::iRangeDrag,true);
    ui->widget_cord_x->setInteraction(QCP::iRangeZoom,true);
    ui->widget_cord_y->setInteraction(QCP::iRangeDrag,true);
    ui->widget_cord_y->setInteraction(QCP::iRangeZoom,true);
    //
    ui->widget_bat->addGraph();
    ui->widget_bat->legend->setVisible(true);
    ui->widget_bat->legend->setBorderPen(QPen(Qt::black));
    ui->widget_bat->graph(0)->setName("consumo de bateria");
    ui->widget_bat->legend->setBrush(QBrush(QColor(255,255,255,200)));
    //
    ui->widget_cord_x->addGraph();
    ui->widget_cord_x->legend->setVisible(true);
    ui->widget_cord_x->legend->setBorderPen(QPen(Qt::black));
    ui->widget_cord_x->graph(0)->setName("coordenadas x");
    ui->widget_cord_x->legend->setBrush(QBrush(QColor(255,255,255,200)));
    //
    ui->widget_cord_y->addGraph();
    ui->widget_cord_y->legend->setVisible(true);
    ui->widget_cord_y->legend->setBorderPen(QPen(Qt::black));
    ui->widget_cord_y->graph(0)->setName("coordenadas y");
    ui->widget_cord_y->legend->setBrush(QBrush(QColor(255,255,255,200)));


    connect(ui->butt_plotear,SIGNAL(clicked(bool)),this,SLOT(plotear()));
    connect(ui->butt_consumo,SIGNAL(clicked(bool)),this,SLOT(consumo()));
    connect(ui->butt_evaluar,SIGNAL(clicked()),this,SLOT(evaluar()));
    ui->butt_consumo->setEnabled(false);
    ui->butt_evaluar->setEnabled(false);
}

de_info_aprobada::~de_info_aprobada()
{
    delete ui;
}

double de_info_aprobada::interrpolacion_en_y(double x_der, double x_izq, double y_der,double y_izq, double x_eval)
{
    double m = (y_der - y_izq)/(x_der - x_izq);
    double  x_media = x_eval;
    double y_res = m*(x_media - x_izq) + y_izq;
    return y_res;
}
double de_info_aprobada::integrar( double lim_inf, double lim_sup)
{
    double area = 0.0;
    QVector<double> y_integral;
    QVector<double> x_integral;
    if(ui->widget_bat->graphCount() == 2){
        ui->widget_bat->removeGraph(1);
    }
    for (int i = 1; i < Cant_x; ++i) {
        if(t[i-1] >= lim_inf && t[i] <= lim_sup){
            area = area + ((bat[i-1] + bat[i])*xd)/2.00;
            y_integral.append(bat[i-1]);
            x_integral.append(t[i-1]);
        }
    }
    if(t[Cant_x -1] <= lim_sup){
        area =  area + ((bat[Cant_x-2] + bat[Cant_x -1])*xd)/2.00;
        y_integral.append(bat[Cant_x-1]);
        x_integral.append(t[Cant_x-1]);
    }
    ui->widget_bat->addGraph();
    ui->widget_bat->graph(1)->setName("consumo");
    ui->widget_bat->graph(1)->setData(x_integral,y_integral);
    ui->widget_bat->graph(1)->setBrush(QBrush(Qt :: cyan));
    ui->widget_bat->replot();



    return area;
}
void de_info_aprobada::rang_x(double x_min,double x_max)
{
    xmin = x_min;
    xmax = x_max;
    xd = (xmax-xmin)/(double)Cant_x;
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

void de_info_aprobada::plot()
{
    QPen rlb;
    rlb.setColor(Qt:: darkCyan);
    ui->widget_bat->graph(0)->setData(t,bat);
    ui->widget_bat->graph(0)->setPen(rlb);
    ui->widget_bat->rescaleAxes();
    ui->widget_bat->replot();
    //
     rlb.setColor(Qt::blue);
    ui->widget_cord_x->graph(0)->setData(t,x);
    ui->widget_cord_x->graph(0)->setPen(rlb);
    ui->widget_cord_x->rescaleAxes();
    ui->widget_cord_x->replot();
    //
     rlb.setColor(Qt :: red);
    ui->widget_cord_y->graph(0)->setData(t,y);
    ui->widget_cord_y->graph(0)->setPen(rlb);
    ui->widget_cord_y->rescaleAxes();
    ui->widget_cord_y->replot();
}


void de_info_aprobada::revalue_arch()
{

    FILE *f = fopen("C:\\Users\\mateo\\OneDrive\\Documentos\\parcial_2\\registro_dron.dat","rb");
    if(f == nullptr){
        qDebug()  << "error";
    }
    fseek(f,0,SEEK_END);
    Cant_x = ftell(f)/sizeof(float);
    Cant_x =  Cant_x /4.00;
    t.resize(Cant_x);
    x.resize(Cant_x);
    y.resize(Cant_x);
    bat.resize(Cant_x);
    fseek(f,0,SEEK_SET);
    for (int i = 0; i < Cant_x; i++) {
        float aux;
        fread(&aux,sizeof(float),1,f);  // tiempo
        x[i] = (double)aux;
        fread(&aux,sizeof(float),1,f); // tension
        y[i] = (double)aux;
        fread(&aux,sizeof(float),1,f); // corriente
        t[i] = (double)aux;
        fread(&aux,sizeof(float),1,f); // corriente
        bat[i] = (double)aux;
    }
    fclose(f);
    rang_x(t[0],t[Cant_x-1]);
}
void de_info_aprobada::plotear()
{
    revalue_arch();
    ui->butt_consumo->setEnabled(true);
    ui->butt_evaluar->setEnabled(true);
    ui->tmax_value->setMaximum(t[Cant_x-1]);
    ui->time_value->setMaximum(t[Cant_x-1]);
    plot();
}

void de_info_aprobada::consumo()
{
    double t_min = ui->t_min_value->value();
    double t_max = ui->tmax_value->value();
    double energia = integrar(t_min,t_max);
    ui->energia_value->setValue(energia);
}

void de_info_aprobada::evaluar()
{
    double time =  ui->time_value->value();
    int b = 0;
    for(int i = 0; i < Cant_x; i++){
        if(time  == t[i]){
            ui->bat_value->setValue(bat[i]);
            ui->x_value->setValue(x[i]);
            ui->y_value->setValue(y[i]);
            b=1;
        }
    }
    if(b == 0){
    for(int i = 0; i < Cant_x - 1; i++){
        if( t[i] <= time && time <= t[i+1]){
            double aux = 0;
            aux  = interrpolacion_en_y(t[i+1],t[i],bat[i+1],bat[i],time);
            ui->bat_value->setValue(aux);
            aux  = interrpolacion_en_y(t[i+1],t[i],x[i+1],x[i],time);
            ui->x_value->setValue(aux);
            aux  = interrpolacion_en_y(t[i+1],t[i],y[i+1],y[i],time);
            ui->y_value->setValue(aux);
        }
    }
    }
}







