#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H


class CustomTitleBar : public QWidget
{
    Q_OBJECT
public :
    explicit CustomTitleBar(QWidget * parent = nullptr);

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
protected slots:
    void onClicked();

private:
    QHBoxLayout * m_Layout;
    QWidget * m_Widget;
    QPushButton * m_minimize;
    QPushButton * m_maximize;
    QPushButton * m_close;

    QPoint m_start;
    bool m_leftButtonPressed;
};
