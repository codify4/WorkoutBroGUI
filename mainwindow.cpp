#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::on_btnAdd_clicked()
{
    QString txtTitle =  ui->name->text();
    QString txtDuration = ui->reps->text();

    if(!txtTitle.isEmpty() && !txtDuration.isEmpty()){
        QString workoutDetails = txtTitle + " - " + txtDuration + " Minutes.";
        ui->listWorkouts->addItem(workoutDetails);

        //clear inputs
        ui->name->clear();
        ui->reps->clear();
    }
}

