#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSizeGrip>
#include <QTimer>
#include <QToolBar>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void varInitialize();
    void setTitleBar();
    void setMenuBar();
    void setToolBar();
    void setStatusBar();
    void setFolderTree();
    void setBody();
    void setMainWindowLayout();

protected :
    bool eventFilter(QObject *object, QEvent *event) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
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

    bool topLeftGrabbed;
    bool topRightGrabbed;
    bool bottomLeftGrabbed;
    bool bottomRightGrabbed;
    bool topGrabbed;
    bool rightGrabbed;
    bool bottomGrabbed;
    bool leftGrabbed;

    bool isPressed;

    QVBoxLayout * MainWindowLayout;

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

    QHBoxLayout * CentralLayout;
    QWidget * CentralWidget;

    QToolBar * ToolBar;
    QAction * Copy;

    QVBoxLayout * FolderTreeLayout;
    QWidget * FolderTree;

    QGridLayout * BodyLayout;
    QWidget * Body;

    QStatusBar * StatusBar;
    QSizeGrip * SizeGrip;

};
#endif // MAINWINDOW_H
