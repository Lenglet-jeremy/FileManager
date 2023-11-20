#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSizeGrip>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setTitleBar();
    void setMenuBar();
    void setStatusBar();

protected :
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    bool eventFilter(QObject *object, QEvent *event) override;
    void resizeEvent(QResizeEvent * Event) override;

private slots:

    void onClicked();

private:

    int XPos;
    int YPos;

    int globalX;
    int globalY;

    int startTopBorder;
    int startRightBorder;
    int startBottomBorder;
    int startLeftBorder;

    int currentTopBorder;
    int currentRightBorder;
    int currentBottomBorder;
    int currentLeftBorder;

    bool onTopLeft;
    bool onTopRight;
    bool onBottomLeft;
    bool onBottomRight;
    bool onTop;
    bool onRight;
    bool onBottom;
    bool onLeft;

    bool isPressed;

    QWidget * TitleBar;
    QLabel * Icon;
    QLabel * Title;
    QPushButton * Minimize;
    QPushButton * Maximize;
    QPushButton * Close;
    QHBoxLayout * TitleBarLayout;

    QMenuBar * MenuBar;
    QMenu * FileMenu;
    QMenu * NewAction;
    QAction * NewTerminal;
    QAction * NewWindow;
    QMenu * LoadAction;
    QMenu * SaveAction;
    QAction * Save;
    QAction * SaveAs;

    QStatusBar * StatusBar;
    QSizeGrip * SizeGrip;


    QWidget * CentralWidget;


    QVBoxLayout * VLayout;
};
#endif // MAINWINDOW_H
