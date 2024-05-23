#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QStandardPaths>

#include <QFile>
#include <QTextStream>
#include <QDebug>

// te gjitha funktionet e MainWindow jane metoda ne klasen MainWindow ne file-in "MainWindow.h"

// funkstioni kryesor i dritares kryesore (mainwindow)
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget::setWindowTitle("Workout Bro");

    loadItemsFromFile(); // bejm call funktionin qe merr info nga storge file
}

// delete ui per refresh, kur mbyllim app-in
MainWindow::~MainWindow()
{
    delete ui;
}

// event listener kur shtypim butonin "Add"
void MainWindow::on_btnAdd_clicked()
{
    //bejm assign widgets te ui ne variabla
    QString name =  ui->name->text();
    QString sets = ui->sets->text();
    QString reps = ui->reps->text();
    QString weight = ui->weight->text();

    // kontrollojme nese input fields kane info
    if(!name.isEmpty() && !sets.isEmpty() && !reps.isEmpty() && !weight.isEmpty())
    {
        // venosim values te inputeve ne 1 string per ti paraqitur me pas
        QString workoutDetails = name.toUpper() + ": " + sets + " sets - " + reps + " reps - " + weight + "kg";
        ui->listWorkouts->addItem(workoutDetails); // sintakse e librarise QT | shton stringun e workoutDetails ne widget-in "listWorkouts"

        //clear inputs
        ui->name->clear();
        ui->sets->clear();
        ui->reps->clear();
        ui->weight->clear();

        appendItemToFile(workoutDetails); // bejm call funksionin per te shtuar te file si storage
    }
}

// event listener: nese bejme double click nje item ne workoutList do te na fshihet
void MainWindow::on_listWorkouts_itemDoubleClicked(QListWidgetItem *item)
{
    delete ui->listWorkouts->takeItem(ui->listWorkouts->row(item));

    // Delete item from file
    QString itemName = item->text();
    deleteItemFromFile(itemName); // bejm call funksionin qe fshin te dhena nga storage file
}

// funksioni qe merr te dhenat nga storage file
void MainWindow::loadItemsFromFile() {
    // marrim relative path te storage file
    QString dataFilePath = getFilePath("storage/Excercises.txt");

    // error handeling nese nuk gjejme storage file
    QFile file(dataFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open file for reading:" << file.errorString();
        return;
    }

    // lexojme line by line ne storage file dhe i vendosim ne widget-in "listWorkouts"
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString item = in.readLine();
        ui->listWorkouts->addItem(item);
    }

    file.close(); // mbyllim storage file
    qDebug() << "Successfully read from file.";
}

// funksioni qe shton ne storage file te dhena qe merren nga useri
void MainWindow::appendItemToFile(const QString &item) {
    // marrim relative path te storage file
    QString dataFilePath = getFilePath("storage/Excercises.txt");

    // error handeling nese nuk gjejme storage file
    QFile file(dataFilePath);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Could not open file for appending:" << file.errorString();
        return;
    }

    // fusim ne file input qe marrim nga user
    QTextStream out(&file);
    out << item << '\n';

    file.close();
    qDebug() << "Successfully appended to file.";
}


// funksioni qe fshin te dhena nga storage file
void MainWindow::deleteItemFromFile(const QString &itemName) {
    // marrim relative path te storage file
    QString dataFilePath = getFilePath("storage/Excercises.txt");

    // error handeling nese nuk gjejme storage file
    QFile inputFile(dataFilePath);
    if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open file for reading:" << inputFile.errorString();
        return;
    }

    // kontrrollojme line by line per ate qe do useri te fshije
    QStringList lines;
    QTextStream in(&inputFile);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line != itemName) {
            lines.append(line);
        }
    }
    inputFile.close();

    // bejm update ui kur fshijme dicka nga storage file
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

// funkstion per te marre relative file path per storage file
QString MainWindow::getFilePath(const QString &fileName) {
    QString appDir = QCoreApplication::applicationDirPath();
    QString dataFilePath = QDir(appDir).filePath(fileName);
    return dataFilePath;
}
