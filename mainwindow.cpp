#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    num=0;
    imageList.clear();
    imageReady.clear();
    qDebug()<<"init"<<ui->label->size();
    wSize=ui->label->size();
    ui->verticalScrollBar->setRange(-100,-5);
    ui->verticalScrollBar->setValue(-50);
    connect(ui->verticalScrollBar,&QAbstractSlider::valueChanged,this,&MainWindow::AdjustVImage);
    selectMode=0;
    selectPoint=false;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_open_triggered()
{
//    QString filename="C:\\Users\\Silence\\Desktop\\1.png";
    QString filename=QFileDialog::getOpenFileName(this,
                                          tr("选择图像"),
                                          "",
                                          tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
    if(filename.isEmpty())
    {
         return;
    }
    else
    {
        QImage* img=new QImage;

        if(! ( img->load(filename) ) ) //加载图像
        {
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr("打开图像失败!"));
            delete img;
            return;
        }

        imageList.append(img);
        FormVImage();

//        p->setScaledContents(true);
    }
}

void MainWindow::FormVImage()
{
    QSize sz=ui->label->size();
    int height=0;
    int width=sz.width();
    for(int i=0;i<imageList.size();i++){
        height+=imageList.at(i)->scaledToWidth(sz.width()).height();
    }
    vimage =new QImage(width,height,QImage::Format_RGB32);
    int th=0;
    QImage img;
    for(int i=0;i<imageList.size();i++){
        img=imageList.at(i)->scaledToWidth(sz.width());
        for(int j=0;j<width;j++){
            for(int k=0;k<img.height();k++){
                vimage->setPixel(j,th+k,img.pixel(j,k));
            }
        }
        th+=img.height();
    }
    qDebug()<<"vimage height is "<<vimage->height();
    int max=vimage->height()-sz.height()+1;
    max=max>1?max:1;
    ui->verticalScrollBar->setRange(0,max);
    if(ui->verticalScrollBar->value()==0){
        AdjustVImage(0);
    }
    else{
        ui->verticalScrollBar->setValue(max-1);
    }
//    ShowVImage();


}
void MainWindow::ShowVImage()
{
    QSize sz=ui->label->size();
    qDebug()<<" show repaint"<<sz;
    QImage img=vimage->scaledToWidth(sz.width());
    int height =img.height();
    if(height >sz.height()){
        img=img.copy(0,height-sz.height(),sz.width(),sz.height());
    }
    ui->label->setPixmap(QPixmap::fromImage(img));
}
void MainWindow::AdjustVImage(int n)
{
    if(n<ui->verticalScrollBar->maximum()){
        qDebug()<<n;
        QSize sz=ui->label->size();
        qDebug()<<" show repaint"<<sz;
        QImage img=vimage->scaledToWidth(sz.width());
        int height =img.height();
        if(height >sz.height()){
            img=img.copy(0,n,sz.width(),sz.height());
        }
        ui->label->setPixmap(QPixmap::fromImage(img));
    }

}

void MainWindow::on_action_delete_triggered()
{

}
void MainWindow::paintEvent ( QPaintEvent * ){
    qDebug()<<"repaint"<<ui->label->size();
    if(wSize !=ui->label->size()){
        FormVImage();
        wSize=ui->label->size();
    }
}



void MainWindow::on_action_lineSegment_triggered()
{
//    selectMode=(selectMode+1)%3;
    selectPoint=true;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
//    //获得相对于屏幕的坐标
//        QPoint sPoint1 = event->globalPos();
//        qDebug() << "相对于屏幕坐标1:" << "(" << sPoint1.rx() << "," << sPoint1.ry() << ")";

        //获得相对于屏幕的坐标
        QPoint sPoint2 = QCursor::pos();
        qDebug() << "相对于屏幕坐标2:" << "(" << sPoint2.rx() << "," << sPoint2.ry() << ")";

        //获得相对于窗口的坐标
        QPoint windowPoint = this->mapFromGlobal(sPoint2);
        qDebug() << "相对于窗口坐标:" << "(" << windowPoint.rx() << "," << windowPoint.ry() << ")";

        //获得相对于控件的坐标
        QPoint widgetPoint = ui->label->mapFromGlobal(sPoint2);
        qDebug() << "相对于控件坐标:" << "(" << widgetPoint.rx() << "," << widgetPoint.ry() << ")";
        if(selectPoint){
            if(selectMode==0)
                start=windowPoint.ry();
            if(selectMode==1){
                selectPoint=false;
                end=windowPoint.ry();
            }
            selectMode++;
        }

}

