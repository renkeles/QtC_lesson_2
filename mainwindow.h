#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "parsetext.h"
#include <QStandardItemModel>




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_plainTextEdit_textChanged();

    void on_checkBox_stateChanged(int arg1);

    void on_pushButton_clicked();

    void on_pushButton_up_clicked();

    void on_pushButton_down_clicked();

    void on_pushButton_add_clicked();

    void on_pushButton_color_clicked();

private:
    Ui::MainWindow *ui;
    ParseText *parseText;
    QStandardItemModel *model;
    QStandardItemModel *table_model;

};
#endif // MAINWINDOW_H
