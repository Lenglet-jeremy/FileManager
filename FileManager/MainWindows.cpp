#include "MainWindows.h"
#include <QVBoxLayout>
#include <QMenuBar>
#include <QPushButton>
#include <QMouseEvent>

/*TODO
 *Implement aero snap based on https://github.com/dfct/TrueFramelessWindow
 *See if we can resizing menus
 *Change th e colors menus
*/

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent){
    //Here we set all global windows property
    setWindowFlag(Qt::FramelessWindowHint);
    setGeometry(500, 300, 500, 300);
    setStyleSheet("background-color : #222222");

    CustomTitleBar * _TitleBar = new CustomTitleBar(this);

    QMenuBar * MenuBar = new QMenuBar(this);
    MenuBar->setGeometry(0, 30, 500, 26);

    QMenu * File_menu = new QMenu("File",this);
    QMenu * Edition_menu = new QMenu("Edition",this);
    QMenu * Tools_menu = new QMenu("Tools",this);
    QMenu * Settings_menu = new QMenu("Settings",this);


    MenuBar->addMenu(File_menu);
    MenuBar->addMenu(Edition_menu);
    MenuBar->addMenu(Tools_menu);
    MenuBar->addMenu(Settings_menu);

    QWidget * Body = new QWidget(this);
    Body->setGeometry(0, 54, 500,300-54);
    Body->setWindowFlag(Qt::FramelessWindowHint);
    Body->setStyleSheet("background-color : #333333");

    QVBoxLayout * VLayout = new QVBoxLayout;
    VLayout->addWidget(_TitleBar);
    VLayout->addWidget(MenuBar);
    VLayout->addWidget(Body);


    //setCentralWidget(Widget);

}

MainWindow::~MainWindow()
{

}


CustomTitleBar::CustomTitleBar(QWidget * parent):QWidget(parent){

    resize(500,36);
    m_Widget = new QWidget(this);
    m_Widget->resize(500,36);
    m_Widget->setWindowFlag(Qt::FramelessWindowHint);
    m_Widget->setStyleSheet("background-color : #000000");

    m_minimize = new QPushButton(m_Widget);
    m_minimize->resize(28,20);
    m_minimize->setStyleSheet("background-color : #111111");

    m_maximize = new QPushButton(m_Widget);
    m_maximize->resize(28,20);
    m_maximize->setStyleSheet("background-color : #111111");

    m_close = new QPushButton(m_Widget);
    m_close->resize(28,20);
    m_close->setStyleSheet("background-color : #111111");


    m_Layout = new QHBoxLayout(m_Widget);
    m_Layout->addWidget(m_minimize);
    m_Layout->addStretch(1);
    m_Layout->addWidget(m_minimize);
    m_Layout->addWidget(m_maximize);
    m_Layout->addWidget(m_close);
    setLayout(m_Layout);

    connect(m_minimize, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(m_maximize, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(m_close, SIGNAL(clicked(bool)), this, SLOT(onClicked()));

}

void CustomTitleBar::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
        m_leftButtonPressed = true;
        m_start = event->globalPos();
    }
}

void CustomTitleBar::mouseMoveEvent(QMouseEvent *event){
    if(m_leftButtonPressed){
        parentWidget()->move(parentWidget()->geometry().topLeft() + event->globalPos() - m_start);
        m_start = event->globalPos();
    }
}

void CustomTitleBar::mouseReleaseEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
        m_leftButtonPressed = false;
    }
}

void CustomTitleBar::onClicked()
{
    QPushButton *pButton = qobject_cast<QPushButton *>(sender());
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        if (pButton == m_minimize)
        {
            pWindow->showMinimized();
        }
        else if (pButton == m_maximize)
        {
            pWindow->isMaximized() ? pWindow->showNormal() : pWindow->showMaximized();

        }
        else if (pButton == m_close)
        {
            pWindow->close();
        }
    }
}

