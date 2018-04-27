#include "mainwindow.h"
#include <QUiLoader>
#include <QFile>
#include <QTimer>
#include <QTimerEvent>
#include <QLabel>
#include <QVariant>
#include <QStyle>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QUiLoader loader;
    QFile file(":/commstatus.ui");
    file.open(QFile::ReadOnly);
    QWidget *myWidget = loader.load(&file, this);
    file.close();

    if (myWidget)
    {
        this->resize(400,60);
        myWidget->move(40,15);

        label_robot_ico = myWidget->findChild<QLabel*>("label_robot_ico");
        label_comm_ico = myWidget->findChild<QLabel*>("label_comm_ico");
        label_label_ico1 = myWidget->findChild<QLabel*>("label_label_ico1");
        label_label_ico2 = myWidget->findChild<QLabel*>("label_label_ico2");
    }

    m_timer_id = startTimer(1000);
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == m_timer_id)
    {
        const char status[5]={0,1,2,11,12};
        static quint8 i=0;
        static quint8 j=2;
        label_label_ico1->setProperty("labelStatusProperty", status[i]);
        label_label_ico2->setProperty("labelStatusProperty", status[j]);
        qDebug()<<i<<j;
        if (++i>=5) i=0;
        if (++j>=5) j=0;

        updateStyle(label_label_ico1);
        updateStyle(label_label_ico2);

        static bool status1 = false;
        label_robot_ico->setProperty("robotStatusProperty", status1);
        qDebug()<<status1;
        status1 = !status1;

        updateStyle(label_robot_ico);

        const int status2[3]={0,2,1};
        static quint8 n=0;
        label_comm_ico->setProperty("signalStrength", status2[n]);
        qDebug()<<n;
        if (++n>=3) n=0;

        updateStyle(label_comm_ico);
    }
}

void MainWindow::updateStyle(QWidget *widget)
{
    widget->style()->unpolish(widget);
    widget->style()->polish(widget);
    widget->update();
}
