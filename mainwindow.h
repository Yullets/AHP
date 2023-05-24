#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Model.h"
#include <QMainWindow>
#include <QTreeWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui{
class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Model* model,
                        QWidget *parent = nullptr);
    ~MainWindow();

    Model *getModel() const;
    void setModel(Model *newModel);

private slots:
//    void on_trw_hierarchy_itemClicked(QTreeWidgetItem *item, int column);

    void on_b_loadFile_clicked();

    void on_trw_hierarchy_itemClicked(QTreeWidgetItem *item, int column);

private:
    Ui::MainWindow *ui;
    Model* model;

    void loadTree();
    void loadAlternatives();
    void loadGrid(ID_t nodeId);
};


#endif // MAINWINDOW_H
