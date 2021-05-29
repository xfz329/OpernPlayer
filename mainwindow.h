#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>
#include <QPainter>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_action_open_triggered();

    void on_action_delete_triggered();

    void on_action_lineSegment_triggered();

private:
    Ui::MainWindow *ui;
    void paintEvent ( QPaintEvent * );
    void mousePressEvent(QMouseEvent *event);
    QSize wSize;
    int num;
    QList<QImage*> imageList;
    QList<bool>  imageReady;
    bool imagechanged;
    QImage *vimage;
    void FormVImage();
    void ShowVImage();
    void AdjustVImage(int n);
    int  selectMode;
    int     start,end;
    bool selectPoint;
};

#endif // MAINWINDOW_H
