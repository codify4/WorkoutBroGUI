#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget::setWindowTitle("Workout Bro");

    QString content = readFromFile();
    ui->listWorkouts->addItem(content);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnAdd_clicked()
{
    QString name =  ui->name->text();
    QString sets = ui->sets->text();
    QString reps = ui->reps->text();
    QString weight = ui->weight->text();

    if(!name.isEmpty() && !sets.isEmpty() && !reps.isEmpty() && !weight.isEmpty())
    {
        QString workoutDetails = name + ": " + sets + " sets\n" + reps + " reps\n" + weight + "kg";
        ui->listWorkouts->addItem(workoutDetails);

        //clear inputs
        ui->name->clear();
        ui->sets->clear();
        ui->reps->clear();
        ui->weight->clear();

        QFile file("C:/Users/User/Desktop/Progaming/GUI_apps/Workout Bro/SavedWorkouts/Excercises.txt");
        if (!file.open(QIODevice::Append | QIODevice::Text)) {
            qDebug() << "Could not open file for writing:" << file.errorString();
            return;
        }

        QTextStream out(&file);
        out << workoutDetails << '\n';

        file.close();
        qDebug() << "Successfully wrote to file.";
    }
}

void MainWindow::on_listWorkouts_itemDoubleClicked(QListWidgetItem *item)
{
    delete ui->listWorkouts->takeItem(ui->listWorkouts->row(item));
}

QString MainWindow::readFromFile() {
    QFile file("C:/Users/User/Desktop/Progaming/GUI_apps/Workout Bro/SavedWorkouts/Excercises.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open file for reading:" << file.errorString();
        return "";
    }

    QTextStream in(&file);
    QString content = in.readAll();

    file.close();
    qDebug() << "Successfully read from file.";

    return content;
}
