#include "MainWindow.h"

#include <QMouseEvent>
#include <QSizeGrip>
#include <QMenuBar>
#include <QStatusBar>
#include <QApplication>

#include <iostream>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent){
    setWindowFlag(Qt::FramelessWindowHint);
    setMinimumSize(800,500);

    varInitialize();
    setTitleBar();
    setMenuBar();
    setToolBar();
    setFolderTree();
    setBody();
    setStatusBar();
    setMainWindowLayout();


    connect(Minimize, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(Maximize, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(Close, SIGNAL(clicked(bool)), this, SLOT(onClicked()));


}

MainWindow::~MainWindow(){

}

void MainWindow::varInitialize(){
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

    topLeftGrabbed = false;
    topRightGrabbed = false;
    bottomLeftGrabbed = false;
    bottomRightGrabbed = false;
    topGrabbed = false;
    rightGrabbed = false;
    bottomGrabbed = false;
    leftGrabbed = false;

    isPressed = false;

    CentralWidget = new QWidget(this);
    CentralWidget->setStyleSheet("Background-color : #000000");
    CentralWidget->setMouseTracking(true);
    CentralWidget->installEventFilter(this);
    setCentralWidget(CentralWidget);
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
    //MenuBar->setFixedHeight(35);

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

void MainWindow::setToolBar(){
    ToolBar = new QToolBar(CentralWidget);
    ToolBar->setStyleSheet("Background-color : #111111");
    ToolBar->setFixedHeight(25);
    ToolBar->setMouseTracking(true);
    ToolBar->installEventFilter(this);

    Copy = new QAction("Copy");

    ToolBar->addAction(Copy);

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

void MainWindow::setFolderTree(){

    FolderTree = new QWidget(CentralWidget);
    FolderTree->setStyleSheet("Border: 1px Solid #FFFFFF");

    QLabel * Download = new QLabel("Download");
    Download->setStyleSheet("Color : #FFFFFF");
    Download->setFixedHeight(20);
    std::cout << Download->geometry().x() << std::endl;

    QLabel * Documents = new QLabel("Documents");
    Documents->setStyleSheet("Color : #FFFFFF");
    Documents->setFixedHeight(20);

    QLabel * Images = new QLabel("Images");
    Images->setStyleSheet("Color : #FFFFFF");
    Images->setFixedHeight(20);

    QLabel * Music = new QLabel("Music");
    Music->setStyleSheet("Color : #FFFFFF");
    Music->setFixedHeight(20);

    QLabel * Videos = new QLabel("Videos");
    Videos->setStyleSheet("Color : #FFFFFF");
    Videos->setFixedHeight(20);


    QLabel * ThisPC = new QLabel("ThisPC");
    ThisPC->setStyleSheet("Color : #FFFFFF");
    ThisPC->setFixedHeight(20);

    FolderTreeLayout = new QVBoxLayout(FolderTree);
    FolderTreeLayout->addWidget(Download);
    FolderTreeLayout->addWidget(Documents);
    FolderTreeLayout->addWidget(Images);
    FolderTreeLayout->addWidget(Music);
    FolderTreeLayout->addWidget(Videos);
    FolderTreeLayout->addSpacing(20);
    FolderTreeLayout->addWidget(ThisPC);
    FolderTreeLayout->addStretch(1);
}

void MainWindow::setBody(){
    Body = new QWidget(CentralWidget);
}

void MainWindow::setMainWindowLayout(){

    CentralLayout = new QHBoxLayout();
    CentralLayout->addWidget(FolderTree);
    CentralLayout->addWidget(Body,1);

    MainWindowLayout = new QVBoxLayout(CentralWidget);
    MainWindowLayout->addWidget(TitleBar);
    MainWindowLayout->setSpacing(0);
    MainWindowLayout->addWidget(MenuBar);
    MainWindowLayout->addWidget(ToolBar);
    MainWindowLayout->addLayout(CentralLayout,1);
    MainWindowLayout->setContentsMargins(0, 0, 0, 0);
    MainWindowLayout->addWidget(StatusBar);

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

        if(globalY > currentTopBorder - 5 && globalY < currentTopBorder + 5 &&
            globalX > currentLeftBorder - 5 && globalX < currentLeftBorder + 5){
            onTopLeft = true;
            setCursor(Qt::SizeFDiagCursor);
        }
        else if(globalY > currentTopBorder - 5 && globalY < currentTopBorder + 5 &&
                globalX > currentRightBorder - 5 && globalX < currentRightBorder + 5){
            Close->setAttribute(Qt::WA_TransparentForMouseEvents);
            onTopRight = true;
            setCursor(Qt::SizeBDiagCursor);
        }
        else if(globalY > currentBottomBorder - 5 && globalY < currentBottomBorder + 5 &&
                globalX > currentLeftBorder - 5 && globalX < currentLeftBorder + 5){
            onBottomLeft = true;
            setCursor(Qt::SizeBDiagCursor);
        }

        else if(globalY > currentTopBorder - 5 && globalY < currentTopBorder + 5){
            onTop = true;
            setCursor(Qt::SizeVerCursor);
        }
        else if(globalX > currentRightBorder - 5 && globalX < currentRightBorder + 5){
            onRight = true;
            setCursor(Qt::SizeHorCursor);
        }
        else if(globalY > currentBottomBorder - 5 && globalY < currentBottomBorder + 5){
            onBottom = true;
            setCursor(Qt::SizeVerCursor);
        }
        else if(globalX > currentLeftBorder - 5 && globalX < currentLeftBorder + 5){
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

void MainWindow::mousePressEvent(QMouseEvent * Event){
    if (Event->button() == Qt::LeftButton) {
        XPos = Event->pos().x();
        YPos = Event->pos().y();

        isPressed = true;

        startTopBorder = geometry().y();
        startRightBorder = geometry().x() + geometry().width();
        startBottomBorder = geometry().y() + geometry().height();
        startLeftBorder = geometry().x();

        if (onTopLeft){
            topLeftGrabbed = true;
        }
        else if (onTopRight){
            topRightGrabbed = true;
        }
        else if (onBottomLeft){
            bottomLeftGrabbed = true;
        }


        else if (onTop){
            topGrabbed = true;
        }
        else if (onRight){
            rightGrabbed = true;
        }
        else if (onBottom){
            bottomGrabbed = true;
        }
        else if (onLeft){
            leftGrabbed = true;
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent * Event){
    // Complete this function implement
    //to avoid "shaking"
    if (topLeftGrabbed){
        setGeometry(globalX, globalY, startRightBorder - globalX, startBottomBorder - globalY);
        if (width() == minimumWidth())
            setGeometry(startLeftBorder, globalY, width(), startBottomBorder - globalY);
        if (height() == minimumHeight())
            setGeometry(globalX, startTopBorder, startRightBorder - globalX, height());
        if (width() == minimumWidth() && height() == minimumHeight())
            setGeometry(startLeftBorder, startTopBorder, width(), height());

    }

    else if (topRightGrabbed){
        setGeometry(startLeftBorder, globalY, globalX - startLeftBorder, startBottomBorder - globalY);
        if (width() == minimumWidth())
            setGeometry(startLeftBorder, globalY, width(), startBottomBorder - globalY);
        if (height() == minimumHeight())
            setGeometry(startLeftBorder, globalY, globalX - startLeftBorder, height());
        if (width() == minimumWidth() && height() == minimumHeight())
            setGeometry(startLeftBorder, startTopBorder, width(), height());
    }

    else if (bottomLeftGrabbed){
        setGeometry(globalX, startTopBorder, startRightBorder - globalX, globalY - startTopBorder);
        if (width() == minimumWidth())
            setGeometry(startLeftBorder, startTopBorder, width(), globalY - startTopBorder);
        if (height() == minimumHeight())
            setGeometry(globalX, startTopBorder, startRightBorder - globalX, height());
        if (width() == minimumWidth() && height() == minimumHeight())
            setGeometry(startLeftBorder, startTopBorder, width(), height());
    }


    else if (topGrabbed){
        if (height() == minimumHeight() && globalY > startTopBorder)
            return;
        setGeometry(startLeftBorder, globalY, width(), startBottomBorder - globalY);
    }

    else if (rightGrabbed){
        setGeometry(startLeftBorder, startTopBorder, globalX - startLeftBorder, height());
        if (width() == minimumWidth())
            setGeometry(startLeftBorder, startTopBorder, width(), height());
    }

    else if (bottomGrabbed){
        setGeometry(startLeftBorder, startTopBorder, width(), globalY - startTopBorder);
        if (height() == minimumHeight())
            setGeometry(startLeftBorder, startTopBorder, width(), height());
    }

    else if (leftGrabbed){
        if (width() == minimumWidth() && globalX > startLeftBorder)
            return;
        setGeometry(globalX, startTopBorder, startRightBorder - globalX, height());
    }

    else if(YPos <=30 && isPressed){
        move(Event->globalPosition().x()-XPos,Event->globalPosition().y()-YPos);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent * Event){
    Q_UNUSED(Event)
    isPressed = false;


    Close->setAttribute(Qt::WA_TransparentForMouseEvents, false);

    topLeftGrabbed = false;
    topRightGrabbed = false;
    bottomLeftGrabbed = false;
    bottomRightGrabbed = false;
    topGrabbed = false;
    rightGrabbed = false;
    bottomGrabbed = false;
    leftGrabbed = false;

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
