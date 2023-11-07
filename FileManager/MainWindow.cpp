#include "MainWindow.h"

#include <QPushButton>
#include <QMouseEvent>
#include <QApplication>
#include <QWindow>
#include <iostream>

#include <QApplication>

//Implement Aero snap
//Implement borders resizing
//Use CSS file to disign MainWindow and especially Qmenus
//See how to implement the high frequency border resizing

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent){
    setWindowFlag(Qt::FramelessWindowHint);
    setStyleSheet("Background-color : #000000");
    resize(500,300);
    setMinimumSize(300,200);


    CentralWidget = new QWidget(this);
    setCentralWidget(CentralWidget);
    CentralWidget->setMouseTracking(true);
    CentralWidget->installEventFilter(this);
    VLayout = new QVBoxLayout(CentralWidget);
    CentralWidget->setLayout(VLayout);

    resizeTimer = new QTimer(this);
    resizeTimer->setInterval(10);
    connect(resizeTimer, &QTimer::timeout, this, &MainWindow::resizeWindow);

    XPos = 0;
    YPos = 0;

    windowWidth = size().width();
    windowHeight = size().height();

    LeftButtonPressed = false;
    RightButtonPressed = false;

    /*
    qDebug() << "*** Qt screens ***";
    const auto screens = qApp->screens();
    for (int ii = 0; ii < qApp->screens().count(); ++ii) {
        qDebug() << ii + 1 << qApp->screens()[ii]->geometry();
        qDebug() << ii + 1 << screens[ii]->geometry();
    }
    */

    setTitleBar();
    setMenuBar();
    setStatusBar();


    VLayout->addWidget(TitleBar);
    VLayout->setSpacing(0);
    VLayout->addWidget(MenuBar);
    VLayout->addStretch();
    VLayout->addWidget(StatusBar);
    VLayout->setContentsMargins(0, 0, 0, 0);


    connect(Minimize, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(Maximize, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(Close, SIGNAL(clicked(bool)), this, SLOT(onClicked()));


}

MainWindow::~MainWindow(){

}

void MainWindow::setTitleBar(){
    Icon = new QLabel;
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
    StatusBar->setMouseTracking(true);
    StatusBar->installEventFilter(this);
    StatusBar->setStyleSheet("Background-color : #181818");
}

void MainWindow::resizeWindow() {
    if (width() > minimumWidth() && height() > minimumHeight()){
        setGeometry(globalXPosCursor, globalYPosCursor, startRightBorder - globalXPosCursor, startBottomBorder - globalYPosCursor);
    }

}

bool MainWindow::eventFilter(QObject *obj, QEvent *event){

    // check mouse move event when mouse is moved on any object
    if (event->type() == QEvent::MouseMove) {
        QMouseEvent *pMouse = dynamic_cast<QMouseEvent *>(event);

        if (pMouse) {

            currentTopBorder = geometry().y();
            currentRightBorder = geometry().x() + geometry().width();
            currentBottomBorder = geometry().y() + geometry().height();
            currentLeftBorder = geometry().x();

            globalXPosCursor = pMouse->globalPosition().rx();
            globalYPosCursor = pMouse->globalPosition().ry();
        }


        if (globalYPosCursor > currentTopBorder && globalYPosCursor < currentTopBorder + 10 &&
            globalXPosCursor > currentLeftBorder && globalXPosCursor < currentLeftBorder + 10) { // Changer le curseur lorsque le pointeur est proche de la bordure
            setCursor(Qt::SizeFDiagCursor);
        }
        else if (globalYPosCursor > currentTopBorder && globalYPosCursor < currentTopBorder + 10 &&
                 globalXPosCursor > currentRightBorder - 10 && globalXPosCursor <= currentRightBorder) { // Changer le curseur lorsque le pointeur est proche de la bordure
            setCursor(Qt::SizeBDiagCursor);
        }
        else if (globalYPosCursor > currentBottomBorder - 10 && globalYPosCursor <= currentBottomBorder &&
                 globalXPosCursor > currentLeftBorder && globalXPosCursor < currentLeftBorder + 10) { // Changer le curseur lorsque le pointeur est proche de la bordure
            setCursor(Qt::SizeBDiagCursor);
        }
        else if (globalYPosCursor > currentBottomBorder - 10 && globalYPosCursor <= currentBottomBorder &&
                 globalXPosCursor > currentRightBorder - 10 && globalXPosCursor <= currentRightBorder) { // Changer le curseur lorsque le pointeur est proche de la bordure
            setCursor(Qt::SizeFDiagCursor);
        }

        else if (globalYPosCursor >= currentTopBorder && globalYPosCursor <= currentTopBorder + 0){
            setCursor(Qt::SizeVerCursor);
        }
        else if (globalXPosCursor > currentRightBorder - 10 && globalXPosCursor <= currentRightBorder) { // Changer le curseur lorsque le pointeur est proche de la bordure
            setCursor(Qt::SizeHorCursor);
        }
        else if (globalYPosCursor > currentBottomBorder - 10 && globalYPosCursor <= currentBottomBorder) { // Changer le curseur lorsque le pointeur est proche de la bordure
            setCursor(Qt::SizeVerCursor);
        }
        else if (globalXPosCursor > currentLeftBorder && globalXPosCursor < currentLeftBorder + 10) { // Changer le curseur lorsque le pointeur est proche de la bordure
            setCursor(Qt::SizeHorCursor);
        }

        else {
            unsetCursor(); // Rétablir le curseur par défaut
        }

        /*
        std::cout << "=====Window position=====" << std::endl;
        std::cout << geometry().x() << std::endl;
        std::cout << geometry().y() << std::endl;
        std::cout << "=====Cursor position on Window=====" << std::endl;
        std::cout << XPos << std::endl;
        std::cout << YPos << std::endl;
        std::cout << "=====Cursor position=====" << std::endl;
        std::cout << event->globalPosition().rx() << std::endl;
        std::cout << event->globalPosition().ry() << std::endl;
        std::cout << "=====Window position=====" << std::endl;
        std::cout << event->globalPosition().rx()-XPos << std::endl;
        std::cout << event->globalPosition().ry()-YPos << std::endl;
        std::cout << "=================" << std::endl;
        */
    }
    //https://doc.qt.io/qt-5/qobject.html#installEventFilter
    //The eventFilter() function must return true if the event should be filtered,
    //(i.e. stopped); otherwise it must return false.
    return QWidget::eventFilter(obj, event);
}

void MainWindow::mousePressEvent(QMouseEvent * event){
    if (Qt::LeftButton){
        LeftButtonPressed = true;
        XPos = event->position().rx();
        YPos = event->position().ry();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent * event){

    if(XPos > Icon->width() &&
       XPos < TitleBar->width() - Minimize->width() - Maximize->width() - Close->width() &&
       YPos <=30){
        move(event->globalPosition().rx()-XPos,event->globalPosition().ry()-YPos);
    }

    startTopBorder = geometry().y();
    startRightBorder = geometry().x() + geometry().width();
    startBottomBorder = geometry().y() + geometry().height();
    startLeftBorder = geometry().x();

    startXPosWindow = event->globalPosition().rx()-XPos;
    startYPosWindow = event->globalPosition().ry()-YPos;
    startWidthWindow = width();
    startHeightWindow = height();

    globalXPosCursor = event->globalPosition().rx();
    globalYPosCursor = event->globalPosition().ry();

    if (globalYPosCursor > startTopBorder && globalYPosCursor < startTopBorder + 10 &&
        globalXPosCursor > startLeftBorder && globalXPosCursor < startLeftBorder + 10) {
        if (!resizeTimer->isActive()) {
            resizeTimer->start();
        }
    }

}

void MainWindow::onClicked(){
    QPushButton *pButton = qobject_cast<QPushButton *>(sender());
    QWidget *pWindow = this->window();
    if (pWindow->isWindow())
    {
        if (pButton == Minimize)
        {
            pWindow->showMinimized();
        }
        else if (pButton == Maximize)
        {
            if(pWindow->isMaximized()){
                pWindow->showNormal();
                Maximize->setIcon(QIcon(":/Ressources/Images/Maximize-white.png"));
            }

            else{
                pWindow->showMaximized();
                Maximize->setIcon(QIcon(":/Ressources/Images/Restore-down-white.png"));
            }
        }
        else if (pButton == Close)
        {
            pWindow->close();
        }
    }
}void MainWindow::mouseReleaseEvent(QMouseEvent * event){
    LeftButtonPressed = false;
    RightButtonPressed = false;
    resizeTimer->stop();
}
