#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "meshviewport.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(new MeshViewport(this));
    setWindowTitle("mesh-editor");
    resize(1200, 800);
}

MainWindow::~MainWindow()
{
    delete ui;
}
