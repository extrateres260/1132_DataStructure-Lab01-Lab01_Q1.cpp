#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void onEqualClicked();
    void removeLastCharacter();


private:
    QLineEdit *display;
    QPushButton *backspaceButton;

};

#endif // MAINWINDOW_H
