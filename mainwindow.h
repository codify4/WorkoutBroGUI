#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qlistwidget.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAdd_clicked();
    void on_listWorkouts_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;

    void loadItemsFromFile();
    void appendItemToFile(const QString &item);
    void deleteItemFromFile(const QString &itemName);
    QString getFilePath(const QString &fileName);
};
#endif // MAINWINDOW_H
