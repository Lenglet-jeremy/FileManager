#include "MainWindow.h"

#include <QApplication>
#include <QTreeView>
#include <QFileSystemModel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    //==============================================================

    QTreeView treeView;
    treeView.setWindowTitle("Folder Tree");

    QFileSystemModel fileSystemModel;
    fileSystemModel.setRootPath("C:/Users/JL/Documents");

    treeView.setModel(&fileSystemModel);
    treeView.setRootIndex(fileSystemModel.index("/"));

    // Personnalisez le QTreeView selon vos besoins
    treeView.setSortingEnabled(true); // Activer le tri, par exemple

    // ...

    treeView.show();
    //===============================================================
    w.show();
    return a.exec();
}
