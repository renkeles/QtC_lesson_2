#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    parseText = new ParseText();
    if (!parseText) close();

    model = new QStandardItemModel(this);

    ui->listView_icon->setModel(model);

    model->appendRow(new QStandardItem(QIcon(":/icons/images/c++.png"), "C++"));
    model->appendRow(new QStandardItem(QIcon(":/icons/images/python.png"), "Python"));
    model->appendRow(new QStandardItem(QIcon(":/icons/images/java.png"), "Java"));
    model->appendRow(new QStandardItem(QIcon(":/icons/images/c-sharp.png"), "C#"));
    model->appendRow(new QStandardItem(QIcon(":/icons/images/php.png"), "PHP"));
    model->appendRow(new QStandardItem(QIcon(":/icons/images/js.png"), "JavaScript"));
}

MainWindow::~MainWindow()
{
    if (parseText) {
    delete parseText;
    parseText = nullptr;
    }

    delete ui;
}


void MainWindow::on_plainTextEdit_textChanged()
{
    QString str = ui->plainTextEdit->toPlainText();
    if (parseText->change(str))
    {
    ui->plainTextEdit->setPlainText(parseText->getText());
    }
}


void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(arg1) ui->listView_icon->setViewMode(QListView::IconMode);
    else ui->listView_icon->setViewMode(QListView::ListMode);
}


void MainWindow::on_pushButton_clicked()
{
    QModelIndexList selected = ui->listView_icon->selectionModel()->selectedIndexes();
    if(!selected.isEmpty())
    {
        model->removeRow(selected.first().row());
    }
}


void MainWindow::on_pushButton_up_clicked()
{
    QModelIndexList selected = ui->listView_icon->selectionModel()->selectedIndexes();
    if(selected.first().row() != 0)
    {
      model->insertRow(selected.first().row() - 1, model->takeRow(selected.first().row()));
    }
}


void MainWindow::on_pushButton_down_clicked()
{
    QModelIndexList selected = ui->listView_icon->selectionModel()->selectedIndexes();
    if(selected.first().row() != model->rowCount() - 1)
    {
        model->insertRow(selected.first().row() + 1, model->takeRow(selected.first().row()));
    }
}


void MainWindow::on_pushButton_add_clicked()
{
    QString str = ui->lineEdit_add->text();
    if(!str.isEmpty())
    {
        model->insertRow(0, new QStandardItem(QIcon(":/icons/images/default.png"), str));
    }
}

