#ifndef MORPHING_H
#define MORPHING_H
#include <QMainWindow>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace Ui {
class morphing;
}

class morphing : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit morphing(QWidget *parent = 0);
    ~morphing();
    
private slots:
    void on_btn_browse_clicked();
    bool eventFilter(QObject *someOb, QEvent *ev);
    void proccessImage();
    void on_btn_process_clicked();
    QPoint perpendicular(QPoint p);
    void on_btn_browse_2_clicked();


    void on_pushButton_2_clicked();
    float point2LineD(QPoint x,QLine pq);
    float lineLength(QLine n);
    float length(QPoint p,QPoint q);
    float slength(QPoint p, QPoint q);
    float getU(QLine pq, QPoint  x);
    float getV(QLine pq, QPoint  x);
    QPoint perpendicularr(QLine pq, QPoint perp);
    QPoint getXp(float u, float v, QLine pqp, QPoint x, QPoint xp);

private:
    Ui::morphing *ui;
    cv::Mat source;
    cv::Mat destinition;
    cv::Mat morphed;
    QString filename;
    bool flag;
    QPoint old_coordinates;
    QList<QLine> lines_source;
    QList<QLine> lines_destination;


    QPoint p_P;
    QPoint q_P;

    QPoint x;
    QPoint q;
    QPoint p;

};


#endif // MORPHING_H


