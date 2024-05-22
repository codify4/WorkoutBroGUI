#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QStandardPaths>

#include <QFile>
#include <QTextStream>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget::setWindowTitle("Workout Bro");

    loadItemsFromFile();
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
        QString workoutDetails = name.toUpper() + ": " + sets + " sets - " + reps + " reps - " + weight + "kg";
        ui->listWorkouts->addItem(workoutDetails);

        //clear inputs
        ui->name->clear();
        ui->sets->clear();
        ui->reps->clear();
        ui->weight->clear();

        appendItemToFile(workoutDetails);
    }
}

void MainWindow::on_listWorkouts_itemDoubleClicked(QListWidgetItem *item)
{
    delete ui->listWorkouts->takeItem(ui->listWorkouts->row(item));

    // Delete item from file
    QString itemName = item->text();
    deleteItemFromFile(itemName);
}

void MainWindow::loadItemsFromFile() {
    // Get the application's directory
    QString dataFilePath = getFilePath("storage/Excercises.txt");

    QFile file(dataFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open file for reading:" << file.errorString();
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString item = in.readLine();
        ui->listWorkouts->addItem(item);
    }

    file.close();
    qDebug() << "Successfully read from file.";
}

void MainWindow::appendItemToFile(const QString &item) {
    // Get the application's directory
    QString dataFilePath = getFilePath("storage/Excercises.txt");


    QFile file(dataFilePath);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Could not open file for appending:" << file.errorString();
        return;
    }

    QTextStream out(&file);
    out << item << '\n';

    file.close();
    qDebug() << "Successfully appended to file.";
}

void MainWindow::deleteItemFromFile(const QString &itemName) {
    // Get the application's directory
    QString dataFilePath = getFilePath("storage/Excercises.txt");


    QFile inputFile(dataFilePath);
    if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open file for reading:" << inputFile.errorString();
        return;
    }

    QStringList lines;
    QTextStream in(&inputFile);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line != itemName) {
            lines.append(line);
        }
    }
    inputFile.close();

    QFile outputFile(dataFilePath);
    if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        qDebug() << "Could not open file for writing:" << outputFile.errorString();
        return;
    }

    QTextStream out(&outputFile);
    for (const QString &line : lines) {
        out << line << '\n';
    }
    outputFile.close();
    qDebug() << "Successfully deleted item from file.";
}

QString MainWindow::getFilePath(const QString &fileName) {
    QString appDir = QCoreApplication::applicationDirPath();
    QString dataFilePath = QDir(appDir).filePath(fileName);
    return dataFilePath;
}
