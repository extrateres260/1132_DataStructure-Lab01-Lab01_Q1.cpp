#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);  // Initialize QApplication object

    // Apply global stylesheet for the entire application
    qApp->setStyleSheet(R"(
        QMainWindow {
            background-color: #000000;
        }
        QLineEdit {
            font-size: 24px;
            padding: 10px;
            color: #E0E0E0;
            background-color: #1a1a1a;
            border-radius: 5px;
        }
        QPushButton {
            font-size: 18px;
            padding: 15px;
            background-color: #FF0000;
            border: 2px solid #333333;
            border-radius: 10px;
        }
        QPushButton:hover {
            background-color: #1a1a1a;
        }
        QPushButton:pressed {
            background-color: #1a1a1a;
        }
    )");

    MainWindow w;  // Create the MainWindow object
    w.show();  // Show the main window

    return app.exec();  // Start the event loop
}
