#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);

private slots:

    void onClicked();

private:
    QWidget * CentralWidget;
    QVBoxLayout * VLayout;

    QWidget * TitleBar;
    QLabel * Icon;
    QLabel * Title;
    QPushButton * Minimize;
    QPushButton * Maximize;
    QPushButton * Close;
    QHBoxLayout * TitleBarLayout;

    int XPos;
    int YPos;

};
#endif // MAINWINDOW_H
