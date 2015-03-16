#include "morphing.h"
#include "ui_morphing.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QtCore/qmath.h>
#include <QFileDialog>
#include <QMouseEvent>
#include <QDebug>
#include <QVector2D>

using namespace cv;
morphing::morphing(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::morphing)
{
    ui->setupUi(this);
    ui->img_source->installEventFilter( this );
    ui->img_dest->installEventFilter( this );
    flag=false;
    morphed = Mat::zeros(700, 700, CV_64F);
    source = Mat::zeros(700, 700, CV_64F);
    destinition = Mat::zeros(700, 700, CV_64F);
    //matorginal=imread(filename, CV_LOAD_IMAGE_COLOR);
    //ui->img_dest->setPixmap(QPixmap::fromImage(matorginal));
}


morphing::~morphing()
{
    delete ui;
}

void morphing::on_btn_browse_clicked()
{
    filename = QFileDialog::getOpenFileName(this,
               tr("Open Image"), "/home/nima/Morphing/pics/", tr("Image Files (*.png *.jpg *.bmp)"));
     qDebug()<<"Load Image From"<<filename;
     source=imread(filename.toStdString(), CV_LOAD_IMAGE_COLOR);
     proccessImage();
}

bool morphing::eventFilter(QObject *someOb, QEvent *ev)
{
if(someOb == ui->img_source && ev->type() == QEvent::MouseButtonPress)
{

    QMouseEvent *me = static_cast<QMouseEvent *>(ev);
    QPoint coordinates = me->pos();
    qDebug()<<"Press On "<<coordinates.x()<<coordinates.y();

    if (!flag){
        old_coordinates.setX(coordinates.x());
        old_coordinates.setY(coordinates.y());
        flag=true;
    }
    else{
        cv::line(source,cv::Point(old_coordinates.x(),old_coordinates.y()),cv::Point(coordinates.x(),coordinates.y()), cv::Scalar(0,0,255), 2);
        lines_source<<QLine(old_coordinates,coordinates);
        flag=false;
    }


    proccessImage();

    //do stuff
    return true;
}


else if(someOb == ui->img_dest && ev->type() == QEvent::MouseButtonPress)
{

    QMouseEvent *me = static_cast<QMouseEvent *>(ev);
    QPoint coordinates = me->pos();
    qDebug()<<"Press On dest image"<<coordinates.x()<<coordinates.y();

    if (!flag){
        old_coordinates.setX(coordinates.x());
        old_coordinates.setY(coordinates.y());
        flag=true;
    }
    else{
        cv::line(destinition,cv::Point(old_coordinates.x(),old_coordinates.y()),cv::Point(coordinates.x(),coordinates.y()), cv::Scalar(0,255,0), 2);
        lines_destination<<QLine(old_coordinates,coordinates);
        flag=false;
    }


    proccessImage();

    //do stuff
    return true;
}


else return false;
}

void morphing::proccessImage(){
    QImage QimageSource((uchar*)source.data,source.cols,source.rows,source.step,QImage::Format_RGB888);;
    ui->img_source->setPixmap(QPixmap::fromImage(QimageSource));

    QImage QimageDestination((uchar*)destinition.data,destinition.cols,destinition.rows,destinition.step,QImage::Format_RGB888);;
    ui->img_dest->setPixmap(QPixmap::fromImage(QimageDestination));

    QImage QimageMorphed((uchar*)morphed.data,morphed.cols,morphed.rows,morphed.step,QImage::Format_RGB888);;
    ui->img_result->setPixmap(QPixmap::fromImage(QimageMorphed));

}


void morphing::on_btn_process_clicked()
{

    float distance;
    QPoint Di;
    float weight;
    float u;
    float v;
    float weightsum;
    QPoint x_P;

  for(int i=0;i<500;i++){
        for(int j=0;j<500;j++){
            QPoint DSUM(0,0);
            weightsum=0;
            x.setX(i);
            x.setY(j);
                for(int k=0;k<lines_source.count();k++){

                    //p=lines_source.at(k).p1();
                    //q=lines_source.at(k).p2();
                    //u=(QPoint::dotProduct(x-p,q-p))/(qPow(p.x()-q.x(),2)+qPow(p.y()-q.y(),2));
                    //v=(QPoint::dotProduct(x-p,perpendicular(q-p)))/(qSqrt(qPow(p.x()-q.x(),2)+qPow(p.y()-q.y(),2)));
                    u=getU(lines_source.at(k),x);
                    v=getV(lines_source.at(k),x);
                    //p_P=lines_destination.at(k).p1();
                    //q_P=lines_destination.at(k).p2();
                    //x_P= p_P + (u*(q_P-p_P))+((v*perpendicular(q_P-p_P))/(qSqrt(qPow(p_P.x()-q_P.x(),2)+qPow(p_P.y()-q_P.y(),2))));
                    x_P=getXp(u,v,lines_destination.at(k),x);
                    Di.setX(x_P.x()-x.x());
                    Di.setY(x_P.y()-x.y());
                    distance=point2LineD(x,lines_source.at(k));
                    weight=qPow(qPow(lineLength(lines_source.at(k)),0.5) / (1+distance),1);
                    DSUM.setX(DSUM.x()+(Di.x()*weight));
                    DSUM.setY(DSUM.y()+(Di.y()*weight));
                    weightsum += weight;
                }

            x_P.setX(x.x() + (DSUM.x()/weightsum));
            x_P.setY(x.y() + (DSUM.y()/weightsum));
            morphed.at<cv::Vec3b>(i,j)=source.at<cv::Vec3b>(x_P.x(),x_P.y());
            /*qDebug()<<"X="<<x;
            qDebug()<<"P="<<p<<", Q="<<q;
            qDebug()<<"P_Prime="<<p_P<<", Q_Prime="<<q_P;
            qDebug()<<"prependeciular q-p"<< perpendicular(q-p);
            qDebug()<<"u="<<u<<", v="<<v;
            qDebug()<<"prependeciular q-p"<< perpendicular(q_P-p_P);*/
            qDebug()<<x <<"-->"<<x_P;
        }
    }
    proccessImage();

}


QPoint morphing::perpendicular(QPoint a){
   float x1;
   float x2;
   QPoint x;
   if((a.x()==0 && a.y()!=0)||(a.x()!=0 && a.y()!=0)){
       x1=qSqrt((qPow(a.y(),4)+(qPow(a.x(),2)*qPow(a.y(),2)))/(qPow(a.x(),2)+qPow(a.y(),2)));
       x2=(-1*a.x()*x1)/(a.y());
       qDebug()<<"a1 = 0";
   }
   else if(a.y()==0 && a.x()!=0){
       x2=qSqrt((qPow(a.x(),4)+(qPow(a.x(),2)*qPow(a.y(),2)))/(qPow(a.x(),2)+qPow(a.y(),2)));
       x1=(-1*a.y()*x2)/(a.x());
       qDebug()<<"a2 = 0";

   }
   else if (a.y()==0 && a.x()==0){
      x1=0;
      x2=0;
   }
   x.setX(x1);
   x.setY(x2);
   return x;
}

void morphing::on_btn_browse_2_clicked()
{

    filename = QFileDialog::getOpenFileName(this,
               tr("Open Image"), "/home/nima/Morphing/pics", tr("Image Files (*.png *.jpg *.bmp)"));
     qDebug()<<"Load Image From"<<filename;
     destinition=imread(filename.toStdString(), CV_LOAD_IMAGE_COLOR);
     proccessImage();

}


void morphing::on_pushButton_2_clicked()
{
    float distance;
    QPoint Di;
    float weight;
    float u;
    float v;
    float weightsum;
    QPoint x_P;
    QPoint DSUM(0,0);
    weightsum=0;
    QPoint x(5,5);
    lines_source<<QLine(QPoint(1,1),QPoint(1,9))<<QLine(QPoint(9,2),QPoint(9,8));
    lines_destination<<QLine(QPoint(1,1),QPoint(1,9))<<QLine(QPoint(3,2),QPoint(9,2));
    //for(int k=0;k<lines_source.count();k++){
    int k=1;
    qDebug()<<lines_destination.at(k);
    u=getU(lines_source.at(k),x);
    v=getV(lines_source.at(k),x);
    qDebug()<<"u="<<u<<"v="<<v;
    x_P= getXp(u,v,lines_destination.at(k),x);
    qDebug()<<x_P;
    Di.setX(x_P.x()-x.x());
    Di.setY(x_P.y()-x.y());
    qDebug()<<"x prime "<<x_P<<"Di="<<Di;
    distance=point2LineD(x,lines_destination.at(k));
    weight=qPow(qPow(lineLength(lines_destination.at(k)),1) / (1+distance),1);
    qDebug()<<weight;
    DSUM.setX(DSUM.x()+(Di.x()*weight));
    DSUM.setY(DSUM.y()+(Di.y()*weight));
    weightsum += weight;
    qDebug()<<"DSUM-"<<DSUM<<" weightsum="<< weightsum;
   qDebug()<<"---------------------------------------------------------------";
    //}

    x_P.setX(x.x() + (DSUM.x()/weightsum));
    x_P.setY(x.y() + (DSUM.y()/weightsum));
    qDebug()<<"xp"<<x.x() + (DSUM.x()/weightsum)<<x.y() + (DSUM.y()/weightsum);
}




float morphing::point2LineD(QPoint x,QLine pq) {
  float c,d,e;
  QPoint u,v,w;

  /* get the vector representation of the line */
  v.setX(pq.p2().x() - pq.p1().x());
  v.setY(pq.p2().y() - pq.p1().y());

  /* get the point in relation to the vector */
  w.setX(x.x() - pq.p1().x());
  w.setY(x.y() - pq.p1().y());
  c = w.x()*v.x() + w.y()*v.y();
  if(c <= 0) {
    return qSqrt(qPow(x.x()-pq.p1().x(),2) + pow(x.y()-pq.p1().y(),2));
  }

  d = qPow(v.x(),2) + pow(v.y(),2);
  if(d <= c) {
    return qSqrt(qPow(x.x()-pq.p2().x(),2) + pow(x.y()-pq.p2().y(),2));
  }

  e = c/d;
  u.setX(pq.p1().x() + e*v.x());
  u.setY(pq.p1().y() + e*v.y());
  return qSqrt(qPow(x.x()-u.x(),2) + qPow(x.y()-u.y(),2));
}


float morphing::lineLength(QLine n){
  return length(n.p1(),n.p2());
}

float morphing::length(QPoint p,QPoint q) {
  return qSqrt(slength(p,q));
}

float morphing::slength(QPoint p, QPoint q) {
  return qPow(q.x()-p.x(),2) + qPow(q.y()-p.y(),2);
}


float morphing::getU(QLine pq, QPoint x) {
  return ((x.x()-pq.p1().x())*(pq.p2().x()-pq.p1().x()) +
      (x.y()-pq.p1().y())*(pq.p2().y()-pq.p1().y())) / slength(pq.p1(),pq.p2());

}

float morphing::getV(QLine pq, QPoint x) {
  QPoint perp;
  //perp=perpendicularr(pq);
  perp=perpendicular(QPoint(pq.p2().x()-pq.p1().x(),pq.p2().y() - pq.p1().y()));
  return ((x.x()-pq.p1().x())*perp.x() + (x.y()-pq.p1().y())*perp.y()) / (lineLength(pq));
}


QPoint morphing::perpendicularr(QLine pq) {
  QPoint perp;
  float m = - (pq.p2().x() - pq.p1().x()) /(float) (pq.p2().y() - pq.p1().y()),
          len = lineLength(pq);
  perp.setY(m*len/sqrt(1+pow(m,2)));
  perp.setX(sqrt(pow(len,2)-pow(perp.y(),2)));
  qDebug()<<"perper"<<perp;
  return perp;




}

QPoint morphing::getXp(float u, float v, QLine pqp, QPoint x) {
  float len = lineLength(pqp);
  QPoint perp;
  QPoint xp;

  perp=perpendicular(QPoint(pqp.p2().x()-pqp.p1().x(),pqp.p2().y() - pqp.p1().y()));
  //perp=perpendicularr(pqp);
  qDebug()<<"qp-pp"<<QPoint(pqp.p2().x()-pqp.p1().x(),pqp.p2().y() - pqp.p1().y());
  qDebug()<<"perp"<<perp;
  qDebug()<<"len"<<len;
  qDebug()<<"len"<<len<<pqp.p1().x()<<pqp.p2().x()-pqp.p1().x()<<u*(pqp.p2().x()-pqp.p1().x())<<(v*(perp.x()))<<(v*(perp.x())) / len;
  xp.setX(pqp.p1().x() + u*(pqp.p2().x()-pqp.p1().x()) + (v*(perp.x())) / len);
  xp.setY(pqp.p1().y() + u*(pqp.p2().y()-pqp.p1().y()) + (v*(perp.y())) / len);
  return xp;
}


void morphing::on_pushButton_clicked()
{

    float u;
    float v;
    QPoint x_P;
    p=lines_source.at(0).p1();
    q=lines_source.at(0).p2();
    p_P=lines_destination.at(0).p1();
    q_P=lines_destination.at(0).p2();

  for(int i=0;i<500;i++){
        for(int j=0;j<500;j++){
            x.setX(i);
            x.setY(j);
            u=getU(lines_source.at(0),x);
            v=getV(lines_source.at(0),x);
            x_P=getXp(u,v,lines_destination.at(0),x);
            qDebug()<<"X="<<x;
            qDebug()<<"P="<<p<<", Q="<<q;
            qDebug()<<"P_Prime="<<p_P<<", Q_Prime="<<q_P;
            qDebug()<<"u="<<u<<", v="<<v;
            qDebug()<<x <<"-->"<<x_P;
            morphed.at<cv::Vec3b>(i,j)=destinition.at<cv::Vec3b>(x_P.x(),x_P.y());
        }
    }
    proccessImage();


}
