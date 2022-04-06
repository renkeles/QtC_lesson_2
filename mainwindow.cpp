#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItemModel>
#include <QTableView>

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

    table_model = new QStandardItemModel(this);

    //table_model->setHeaderData(0, Qt::Horizontal, "NamePC");
    //table_model->setHeaderData(1, Qt::Horizontal, "IP");
    //table_model->setHeaderData(2, Qt::Horizontal, "MAC");

    QStringList headerLabels;
    headerLabels << "NamePC" << "IP" << "MAC";
    table_model->setHorizontalHeaderLabels(headerLabels);

    ui->tableView->setSelectionMode(QAbstractItemView::MultiSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    table_model->appendRow({new QStandardItem("PC1"), new QStandardItem("192.168.2.161"), new QStandardItem("F0:98:9D:00:00:00")});
    table_model->appendRow({new QStandardItem("PC2"), new QStandardItem("192.168.2.162"), new QStandardItem("F1:87:9B:00:00:00")});
    table_model->appendRow({new QStandardItem("PC3"), new QStandardItem("192.168.2.163"), new QStandardItem("F1:87:9A:00:00:00")});

    ui->tableView->setModel(table_model);
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


void MainWindow::on_pushButton_color_clicked()
{
    QModelIndexList selected = ui->tableView->selectionModel()->selectedIndexes();
    if(!selected.isEmpty())
    {
        int idx = selected.first().row();
        for(int i = 0; i < ui->tableView->model()->columnCount(); ++i)
        {
            ui->tableView->model()->setData(ui->tableView->model()->index(idx, i), QColor(Qt::green), Qt::BackgroundRole);
        }
    }

}

