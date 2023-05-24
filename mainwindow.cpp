#include <QFileDialog>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QThread>
#include <Stack>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Model* model, QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_b_loadFile_clicked()
{
    QFileDialog fileDialog(this);
    QString filename =  QFileDialog::getOpenFileName(
              this,
              "Open Model",
              QDir::currentPath(),
              "All files (*.*) ;; AHP model files (*.ahp)");

    if( !filename.isNull() )
    {
        QMessageBox* msgBox = new QMessageBox();
        if( Storage::getInstance().loadFromFile(filename.toStdString(),
                                                *model)){
            msgBox->setText("The document has been loaded.");

        }else{
            msgBox->setText("The document has not been loaded.");
        }

        model->getHierarchy()->calculateLocalPriorities(model->getHierarchy()->getRoot());
        model->getHierarchy()->calculateGlobalPriorities(model->getHierarchy()->getRoot());
        model->calculateGlobalPrioritiesForAlternatives();

        loadTree();
        loadAlternatives();
        msgBox->exec();
    }

}

void MainWindow::loadTree()
{
    auto tree = ui->trw_hierarchy;

    ui->trw_hierarchy->setColumnCount(1);

    ui->trw_hierarchy->setHeaderLabel(QString("Nodes"));

    std::stack<Node*> nodes({model->getHierarchy()->getRoot()});
    QTreeWidgetItem* rootItem = new QTreeWidgetItem(ui->trw_hierarchy);
    rootItem->setData(0, Qt::UserRole, QVariant(nodes.top()->getId()));

    rootItem->setText(0, QString::fromStdString(model->getHierarchy()->getRoot()->getName()) + QString::fromStdString("; Global: ") + QString::number(model->getHierarchy()->getRoot()->getGlobalPriority()) + QString::fromStdString(")"));
    tree->addTopLevelItem(rootItem);

    std::stack<QTreeWidgetItem*> items;
    items.push(rootItem);

    while(nodes.empty() == false){
        Node* currentNode = nodes.top();
        nodes.pop();

        QTreeWidgetItem* parentItem = items.top();
        items.pop();

        for(auto& node: currentNode->getChildren()){
            QTreeWidgetItem* childItem = new QTreeWidgetItem();
            childItem->setText(0,QString::fromStdString( node.second->getName()) + QString::fromStdString(" (Local: ") + QString::number(node.second->getLocalPriority()) + QString::fromStdString("; Global: ") + QString::number(node.second->getGlobalPriority()) + QString::fromStdString(")"));
            parentItem->addChild(childItem);

            childItem->setData(0, Qt::UserRole, QVariant(node.second->getId()));

            nodes.push(node.second);
            items.push(childItem);
        }
    }
}

void MainWindow::loadAlternatives()
{
    auto listWidget = ui->lw_list;

    auto& alternatives = model->getAlternatives();

    for(auto& alternativesPair: alternatives){
        new QListWidgetItem(QString::fromStdString((alternativesPair.second.getName())) + QString::fromStdString(" (Global: ") + QString::number(alternativesPair.second.getGlobalPriority()) + QString::fromStdString(")"), listWidget);
    }
}

void MainWindow::loadGrid(ID_t nodeId)
{
    Node* node = model->getHierarchy()->getNodeByID(nodeId);

    auto matrix =  node->getJudgments().getJudgmentsMatrix(1);

    auto gridWidget = ui->tw_table;

    gridWidget->clear();
    gridWidget->setRowCount(matrix.nRows());
    gridWidget->setColumnCount(matrix.nCols());



    for(int rowIndex = 0; rowIndex < matrix.nRows(); rowIndex++){
        for(int colIndex = 0; colIndex < matrix.nCols(); colIndex++){
            QTableWidgetItem* item = new QTableWidgetItem();
            item->setData(Qt::DisplayRole,QVariant(matrix(rowIndex, colIndex)));

            gridWidget->setItem(rowIndex,colIndex, item);


        }
    }
}

Model *MainWindow::getModel() const
{
    return model;
}

void MainWindow::setModel(Model *newModel)
{
    model = newModel;
}

void MainWindow::on_trw_hierarchy_itemClicked(QTreeWidgetItem *item, int column)
{
    ID_t nodeId  = *((ID_t*)(item->data(0, Qt::UserRole).data()));


    qDebug() << nodeId << "\n";
    loadGrid(nodeId);
}







