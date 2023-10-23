#include "MainWindow.h"

#include <QPushButton>
#include <QMouseEvent>
#include <QApplication>
#include <QWindow>
#include <iostream>

//Implement Aero snap
//Implement borders resizing
//Unified Icons format of title bar, use website https://icons8.com/icons

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent){
    setWindowFlag(Qt::FramelessWindowHint);
    setStyleSheet("Background-color : #000000");
    resize(500,300);

    CentralWidget = new QWidget(this);
    setCentralWidget(CentralWidget);

    VLayout = new QVBoxLayout(CentralWidget);
    CentralWidget->setLayout(VLayout);

    Icon = new QLabel;
    Icon->setPixmap(QPixmap(":/Ressources/Images/Diamond.png"));
    Icon->setContentsMargins(5, 0, 0, 0);

    Title = new QLabel;
    Title->setText("FileManager");
    Title->setStyleSheet("Color : #FFFFFF");

    Minimize = new QPushButton;
    Minimize->resize(27,27);
    Minimize->setIcon(QIcon(":/Ressources/Images/Minimize-white.png"));
    //Minimize->setFlat(1);

    Maximize = new QPushButton;
    Maximize->resize(27,27);
    Maximize->setIcon(QIcon(":/Ressources/Images/Maximize-white.png"));
    //Maximize->setFlat(1);

    Close = new QPushButton;
    Close->resize(27,27);
    Close->setIcon(QIcon(":/Ressources/Images/Close-white.png"));
    //Close->setFlat(1);


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
    TitleBarLayout->setSpacing(5);

    VLayout->addWidget(TitleBar);
    VLayout->addStretch();
    VLayout->setContentsMargins(0, 0, 0, 0);


    connect(Minimize, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(Maximize, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(Close, SIGNAL(clicked(bool)), this, SLOT(onClicked()));

}

MainWindow::~MainWindow(){

}

void MainWindow::mousePressEvent(QMouseEvent *event){
    XPos = event->position().rx();
    YPos = event->position().ry();
    std::cout << YPos << std::endl;

}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
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
