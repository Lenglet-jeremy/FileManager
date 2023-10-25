#include "MainWindow.h"

#include <QPushButton>
#include <QMouseEvent>
#include <QApplication>
#include <QWindow>
#include <iostream>

//Implement Aero snap
//Implement borders resizing
//Use CSS file to disign MainWindow and aspecially Qmenus

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent){
    setWindowFlag(Qt::FramelessWindowHint);
    setStyleSheet("Background-color : #000000");
    resize(500,300);

    CentralWidget = new QWidget(this);
    setCentralWidget(CentralWidget);

    VLayout = new QVBoxLayout(CentralWidget);
    CentralWidget->setLayout(VLayout);

    XPos = 0;
    YPos = 0;

    windowWidth = size().width();
    windowHeight = size().height();

    primaryScreenWidth = qApp->primaryScreen()->size().width();
    primaryScreenHeight = qApp->primaryScreen()->size().height();

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
    Icon->setPixmap(QPixmap(":/Ressources/Images/Diamond.png"));
    Icon->setContentsMargins(5, 0, 0, 0);

    Title = new QLabel;
    Title->setText("FileManager");
    Title->setStyleSheet("Color : #FFFFFF");

    Minimize = new QPushButton;
    Minimize->resize(27,27);
    Minimize->setIcon(QIcon(":/Ressources/Images/Minimize-white.png"));
    Minimize->setFlat(1);

    Maximize = new QPushButton;
    Maximize->resize(27,27);
    Maximize->setIcon(QIcon(":/Ressources/Images/Maximize-white.png"));
    Maximize->setFlat(1);

    Close = new QPushButton;
    Close->resize(27,27);
    Close->setIcon(QIcon(":/Ressources/Images/Close-white.png"));
    Close->setFlat(1);


    TitleBar = new QWidget;
    TitleBar->setStyleSheet("Background-color : #101010");
    TitleBar->setFixedHeight(30);

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
    MenuBar = new QMenuBar();
    MenuBar->setStyleSheet("Background-color : #181818");
    MenuBar->setFixedHeight(21);

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
    StatusBar = new QStatusBar();
    StatusBar->setStyleSheet("Background-color : #181818");
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    XPos = event->position().rx();
    YPos = event->position().ry();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    if(YPos <=30){
        move(event->globalPosition().rx()-XPos,event->globalPosition().ry()-YPos);
    }
    std::cout << "=================" << std::endl;
    std::cout << XPos << std::endl;
    std::cout << YPos << std::endl;
    std::cout << event->globalPosition().rx() << std::endl;
    std::cout << event->globalPosition().ry() << std::endl;
    std::cout << event->globalPosition().rx()-XPos << std::endl;
    std::cout << event->globalPosition().ry()-YPos << std::endl;
    std::cout << "=================" << std::endl;
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
