#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

protected:
    virtual void timerEvent(QTimerEvent *event);

private:
    void updateStyle(QWidget* widget);

signals:

public slots:

private:
    int m_timer_id;

    QLabel *label_robot_ico;
    QLabel *label_comm_ico;
    QLabel *label_label_ico1;
    QLabel *label_label_ico2;
};

#endif // MAINWINDOW_H
