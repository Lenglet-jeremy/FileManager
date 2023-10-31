#include "MainWindow.h"

#include <QPushButton>
#include <QMouseEvent>
#include <QApplication>
#include <QWindow>
#include <iostream>

//Implement Aero snap
//Implement borders resizing
//Use CSS file to disign MainWindow and especially Qmenus

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent){
    setWindowFlag(Qt::FramelessWindowHint);
    setStyleSheet("Background-color : #000000");
    resize(500,300);

    CentralWidget = new QWidget(this);
    setCentralWidget(CentralWidget);
    CentralWidget->resize(500,300);
    CentralWidget->setMouseTracking(true);
    CentralWidget->installEventFilter(this);
    VLayout = new QVBoxLayout(CentralWidget);
    CentralWidget->setLayout(VLayout);

    XPos = 0;
    YPos = 0;

    windowWidth = size().width();
    windowHeight = size().height();

    primaryScreenWidth = qApp->primaryScreen()->size().width();
    primaryScreenHeight = qApp->primaryScreen()->size().height();
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

bool MainWindow::eventFilter(QObject *obj, QEvent *event){

    // check mouse move event when mouse is moved on any object
    if (event->type() == QEvent::MouseMove) {
        QMouseEvent *pMouse = dynamic_cast<QMouseEvent *>(event);

        if (pMouse) {

            topBorder = geometry().y();
            rightBorder = geometry().x() + geometry().width();
            bottomBorder = geometry().y() + geometry().height();
            leftBorder = geometry().x();

            globalXPosCursor = pMouse->globalPosition().rx();
            globalYPosCursor = pMouse->globalPosition().ry();
        }


        if (globalYPosCursor > topBorder && globalYPosCursor < topBorder + 10 &&
            globalXPosCursor > leftBorder && globalXPosCursor < leftBorder + 10) { // Changer le curseur lorsque le pointeur est proche de la bordure
            setCursor(Qt::SizeFDiagCursor);
        }
        else if (globalYPosCursor > topBorder && globalYPosCursor < topBorder + 10 &&
                 globalXPosCursor > rightBorder - 10 && globalXPosCursor <= rightBorder) { // Changer le curseur lorsque le pointeur est proche de la bordure
            setCursor(Qt::SizeBDiagCursor);
        }
        else if (globalYPosCursor > bottomBorder - 10 && globalYPosCursor <= bottomBorder &&
                 globalXPosCursor > leftBorder && globalXPosCursor < leftBorder + 10) { // Changer le curseur lorsque le pointeur est proche de la bordure
            setCursor(Qt::SizeBDiagCursor);
        }
        else if (globalYPosCursor > bottomBorder - 10 && globalYPosCursor <= bottomBorder &&
                 globalXPosCursor > rightBorder - 10 && globalXPosCursor <= rightBorder) { // Changer le curseur lorsque le pointeur est proche de la bordure
            setCursor(Qt::SizeFDiagCursor);
        }

        else if (globalYPosCursor > topBorder && globalYPosCursor < topBorder + 10){
            setCursor(Qt::SizeVerCursor);
        }
        else if (globalXPosCursor > rightBorder - 10 && globalXPosCursor <= rightBorder) { // Changer le curseur lorsque le pointeur est proche de la bordure
            setCursor(Qt::SizeHorCursor);
        }
        else if (globalYPosCursor > bottomBorder - 10 && globalYPosCursor <= bottomBorder) { // Changer le curseur lorsque le pointeur est proche de la bordure
            setCursor(Qt::SizeVerCursor);
        }
        else if (globalXPosCursor > leftBorder && globalXPosCursor < leftBorder + 10) { // Changer le curseur lorsque le pointeur est proche de la bordure
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
    XPos = event->position().rx();
    YPos = event->position().ry();

    globalXPosCursor = event->globalPosition().rx();
    globalYPosCursor = event->globalPosition().ry();
}

void MainWindow::mouseMoveEvent(QMouseEvent * event){
    if(YPos <=30){
        move(event->globalPosition().rx()-XPos,event->globalPosition().ry()-YPos);
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
}
