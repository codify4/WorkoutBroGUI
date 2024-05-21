#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget::setWindowTitle("Workout Bro");

    // QPixmap pic("C:/Users/User/Desktop/Progaming/GUI_apps/WorkoutTracker/images/WorkoutBroLogo.png");
    // ui->imgLabel->setPixmap(pic);
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
    }
}

void MainWindow::on_listWorkouts_itemDoubleClicked(QListWidgetItem *item)
{
    delete ui->listWorkouts->takeItem(ui->listWorkouts->row(item));
}

