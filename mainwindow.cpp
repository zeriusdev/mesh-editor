#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(central);
    QLabel *label = new QLabel("mesh-editor", central);
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
    setCentralWidget(central);
    setWindowTitle("mesh-editor");
    resize(1200, 800);
}

MainWindow::~MainWindow()
{
    delete ui;
}
