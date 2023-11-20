#include "MainWindow.h"

#include <QMouseEvent>
#include <QSizeGrip>
#include <iostream>
#include <QMenuBar>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent){
    setWindowFlag(Qt::FramelessWindowHint);
    setMinimumSize(500,300);

    XPos = 0;
    YPos = 0;

    onTopLeft = false;
    onTopRight = false;
    onBottomLeft = false;
    onBottomRight = false;
    onTop = false;
    onRight = false;
    onBottom = false;
    onLeft = false;

    isPressed = false;

    CentralWidget = new QWidget(this);
    CentralWidget->setStyleSheet("Background-color : #000000");
    CentralWidget->setMouseTracking(true);
    CentralWidget->installEventFilter(this);
    setCentralWidget(CentralWidget);


    setTitleBar();
    setMenuBar();
    setStatusBar();

    VLayout = new QVBoxLayout(CentralWidget);
    VLayout->addWidget(TitleBar);
    VLayout->setSpacing(0);
    VLayout->addWidget(MenuBar);
    VLayout->addStretch();
    VLayout->setContentsMargins(0, 0, 0, 0);
    VLayout->addWidget(StatusBar);

    connect(Minimize, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(Maximize, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(Close, SIGNAL(clicked(bool)), this, SLOT(onClicked()));


}

MainWindow::~MainWindow(){
}

void MainWindow::setTitleBar(){
    Icon = new QLabel();
    Icon->setMouseTracking(true);
    Icon->installEventFilter(this);
    Icon->setPixmap(QPixmap(":/Ressources/Images/Diamond.png"));
    Icon->setContentsMargins(5, 0, 0, 0);


    Title = new QLabel;
    Title->setMouseTracking(true);
    Title->installEventFilter(this);
    Title->setText("FileManager");
    Title->setStyleSheet("Color : #FFFFFF");

    Minimize = new QPushButton;
    Minimize->setMouseTracking(true);
    Minimize->installEventFilter(this);
    Minimize->resize(27,27);
    Minimize->setIcon(QIcon(":/Ressources/Images/Minimize-white.png"));
    Minimize->setFlat(1);

    Maximize = new QPushButton;
    Maximize->setMouseTracking(true);
    Maximize->installEventFilter(this);
    Maximize->resize(27,27);
    Maximize->setIcon(QIcon(":/Ressources/Images/Maximize-white.png"));
    Maximize->setFlat(1);

    Close = new QPushButton;
    Close->setMouseTracking(true);
    Close->installEventFilter(this);
    Close->resize(27,27);
    Close->setIcon(QIcon(":/Ressources/Images/Close-white.png"));
    Close->setFlat(1);


    TitleBar = new QWidget(CentralWidget);
    TitleBar->setMouseTracking(true);
    TitleBar->installEventFilter(this);
    TitleBar->setStyleSheet("Background-color : #101010");
    //TitleBar->setFixedHeight(30);

    TitleBarLayout = new QHBoxLayout(TitleBar);
    TitleBarLayout->addWidget(Icon);
    TitleBarLayout->addStretch();
    TitleBarLayout->addWidget(Title);
    TitleBarLayout->addStretch();
    TitleBarLayout->addWidget(Minimize);
    TitleBarLayout->addWidget(Maximize);
    TitleBarLayout->addWidget(Close);
    TitleBarLayout->setContentsMargins(0, 0, 0, 0);
}

void MainWindow::setMenuBar(){
    MenuBar = new QMenuBar(CentralWidget);
    MenuBar->setMouseTracking(true);
    MenuBar->installEventFilter(this);
    MenuBar->setStyleSheet("Background-color : #181818");
    //MenuBar->setFixedHeight(23);

    FileMenu = new QMenu("File");
    NewAction = new QMenu("New...");
    NewTerminal = new QAction("Terminal");
    NewWindow = new QAction("Window");
    LoadAction = new QMenu("Load...");
    SaveAction = new QMenu("Save...");
    Save = new QAction("Save");
    SaveAs = new QAction("Save As");

    FileMenu->addMenu(NewAction);
    NewAction->addAction(NewTerminal);
    NewAction->addAction(NewWindow);
    FileMenu->addMenu(LoadAction);
    FileMenu->addMenu(SaveAction);
    SaveAction->addAction(Save);
    SaveAction->addAction(SaveAs);

    MenuBar->addMenu(FileMenu);
}

void MainWindow::setStatusBar(){
    StatusBar = new QStatusBar(CentralWidget);
    StatusBar->setStyleSheet("Background-color : #111111");
    StatusBar->setMouseTracking(true);
    StatusBar->installEventFilter(this);
    StatusBar->setFixedHeight(25);

    SizeGrip = new QSizeGrip(StatusBar);
    SizeGrip->setCursor(Qt::SizeFDiagCursor);

    StatusBar->addPermanentWidget(SizeGrip, 0);
}

void MainWindow::mousePressEvent(QMouseEvent * Event){
    if (Event->button() == Qt::LeftButton) {
        XPos = Event->pos().x();
        YPos = Event->pos().y();

        isPressed = true;

        startTopBorder = geometry().y();
        startRightBorder = geometry().x() + geometry().width();
        startBottomBorder = geometry().y() + geometry().height();
        startLeftBorder = geometry().x();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent * Event){

    if (onTopLeft && isPressed){
        setGeometry(globalX, globalY, startRightBorder - globalX, startBottomBorder - globalY);
    }
    else if (onTopRight && isPressed){
        setGeometry(startLeftBorder, globalY, globalX - startLeftBorder, startBottomBorder - globalY);
    }
    else if (onBottomLeft && isPressed){
        setGeometry(globalX, startTopBorder, startRightBorder - globalX, globalY - startTopBorder);
    }


    else if (onTop && isPressed){
        setGeometry(startLeftBorder, globalY, width(), startBottomBorder - globalY);
    }
    else if (onRight && isPressed){
        setGeometry(startLeftBorder, startTopBorder, globalX - startLeftBorder, height());
    }
    else if (onBottom && isPressed){
        setGeometry(startLeftBorder, startTopBorder, width(), globalY - startTopBorder);
    }
    else if (onLeft && isPressed){
        setGeometry(globalX, startTopBorder, startRightBorder - globalX, height());
    }

    else if(YPos <=30 && isPressed){
        move(Event->globalPosition().x()-XPos,Event->globalPosition().y()-YPos);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent * Event){
    isPressed = false;
}

bool MainWindow::eventFilter(QObject *Object, QEvent *Event){


    if (Event->type() == QEvent::MouseMove) {
        QMouseEvent *pMouse = dynamic_cast<QMouseEvent *>(Event);
        if (pMouse){
            currentTopBorder = geometry().y();
            currentRightBorder = geometry().x() + geometry().width();
            currentBottomBorder = geometry().y() + geometry().height();
            currentLeftBorder = geometry().x();

            globalX = pMouse->globalPosition().x();
            globalY = pMouse->globalPosition().y();
        }

        if(globalY > currentTopBorder - 50 && globalY < currentTopBorder + 50 &&
           globalX > currentLeftBorder - 50 && globalX < currentLeftBorder + 50){
            onTopLeft = true;
            setCursor(Qt::SizeFDiagCursor);
        }
        else if(globalY > currentTopBorder - 50 && globalY < currentTopBorder + 50 &&
                globalX > currentRightBorder - 50 && globalX < currentRightBorder + 50){
            onTopRight = true;
            setCursor(Qt::SizeBDiagCursor);
        }
        else if(globalY > currentBottomBorder - 50 && globalY < currentBottomBorder + 50 &&
                globalX > currentLeftBorder - 50 && globalX < currentLeftBorder + 50){
            onBottomLeft = true;
            setCursor(Qt::SizeBDiagCursor);
        }

        else if(globalY > currentTopBorder - 50 && globalY < currentTopBorder + 50){
            onTop = true;
            setCursor(Qt::SizeVerCursor);
        }
        else if(globalX > currentRightBorder - 50 && globalX < currentRightBorder + 50){
            onRight = true;
            setCursor(Qt::SizeHorCursor);
        }
        else if(globalY > currentBottomBorder - 50 && globalY < currentBottomBorder + 50){
            onBottom = true;
            setCursor(Qt::SizeVerCursor);
        }
        else if(globalX > currentLeftBorder - 50 && globalX < currentLeftBorder + 50){
            onLeft = true;
            setCursor(Qt::SizeHorCursor);
        }

        else{
            unsetCursor();
            onTopLeft = false;
            onTopRight = false;
            onBottomLeft = false;
            onBottomRight = false;
            onTop = false;
            onRight = false;
            onBottom = false;
            onLeft = false;
        }
    }

    //https://doc.qt.io/qt-5/qobject.html#installEventFilter
    //The eventFilter() function must return true if the event should be filtered,
    //(i.e. stopped); otherwise it must return false.
    return QWidget::eventFilter(Object, Event);
}

void MainWindow::resizeEvent(QResizeEvent * Event){
    Q_UNUSED(Event);
}

void MainWindow::onClicked(){
    QPushButton *pButton = qobject_cast<QPushButton *>(sender());
    QWidget *pWindow = this->window();
    if (pWindow->isWindow() &&
        cursor() != Qt::SizeVerCursor && cursor() != Qt::SizeHorCursor &&
        cursor() != Qt::SizeBDiagCursor && cursor() != Qt::SizeFDiagCursor){
        if (pButton == Minimize){
            pWindow->showMinimized();
        }
        else if (pButton == Maximize){
            if(pWindow->isMaximized()){
                pWindow->showNormal();
                Maximize->setIcon(QIcon(":/Ressources/Images/Maximize-white.png"));
            }
            else{
                pWindow->showMaximized();
                Maximize->setIcon(QIcon(":/Ressources/Images/Restore-down-white.png"));
            }
        }
        else if (pButton == Close){
            pWindow->close();
        }
    }
}
