#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMenuBar>
#include <QStatusBar>
#include <QList>
#include <QTimer>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setTitleBar();
    void setMenuBar();
    void setStatusBar();
    void resizeWindow();


protected:
    virtual bool eventFilter(QObject *obj, QEvent *event);
    virtual void mousePressEvent(QMouseEvent * event);
    virtual void mouseMoveEvent(QMouseEvent * event);
    virtual void mouseReleaseEvent(QMouseEvent * event);


private slots:

    void onClicked();

private:

    int XPos;
    int YPos;

    int windowWidth;
    int windowHeight;

    int globalXPosCursor;
    int globalYPosCursor;

    int startTopBorder;
    int startRightBorder;
    int startBottomBorder;
    int startLeftBorder;

    int startXPosWindow;
    int startYPosWindow;
    int startWidthWindow;
    int startHeightWindow;

    int currentTopBorder;
    int currentRightBorder;
    int currentBottomBorder;
    int currentLeftBorder;

    bool LeftButtonPressed;
    bool RightButtonPressed;

    QTimer * resizeTimer;

    QWidget * CentralWidget;
    QVBoxLayout * VLayout;

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

};
#endif // MAINWINDOW_H
