#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtXml>
#include <QTextStream>
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setModel(Model *model)
{
    this->model = model;
}


void MainWindow::on_pushButton_clicked()
{
    QFileDialog fileDialog(this);

    if (fileDialog.exec())
        auto fileNames = fileDialog.selectedFiles();
}

