#include "mainwindow.h"

#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    // Krijojme nje instance te applikacionit
    QApplication a(argc, argv);
    MainWindow w; // hapim nje window

    a.setWindowIcon(QIcon(":/images/2.png")); // vendosim icon e app-it

    a.setDesktopFileName("Workout Bro"); // vendosim titulltin e window/dritares

    // bejm style komponentet e GUI-t
    a.setStyle(QStyleFactory::create("Fusion"));

    a.setStyleSheet(R"(
        QWidget {
            background-color: #2E2E2E;
            color: #FFFFFF;
        }
        QLabel {
            color: #FFFFFF;
        }
        QLineEdit {
            background-color: #4E4E4E;
            color: #FFFFFF;
            border: 1px solid #5E5E5E;
        }
        QPushButton {
            background-color: #4E4E4E;
            color: #FFFFFF;
            border: 1px solid #5E5E5E;
        }
        QPushButton:hover {
            background-color: #5E5E5E;
        }
        QPushButton:pressed {
            background-color: #3E3E3E;
        }
        QListWidget {
            background-color: #4E4E4E;
            color: #FFFFFF;
            border: 1px solid #5E5E5E;
        }
    )");

    // nisim app-in
    w.show();
    return a.exec();
}
