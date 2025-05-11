#include "mainwindow.h"
#include "expression_evaluator.h"

#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QString>
#include <QByteArray>
#include <QFont>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Set window title and size
    setWindowTitle("Stylish Qt Calculator");
    setFixedSize(400, 500);

    // Set up the central widget and layout
    QWidget *central = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(central);

    // Create display
    display = new QLineEdit();
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setStyleSheet("font-size: 24px; padding: 10px; color: white; background-color: #1E1E1E;");
    mainLayout->addWidget(display);

    // Create grid layout for buttons
    QGridLayout *grid = new QGridLayout();

    // Create backspace button and place it in top-right
    backspaceButton = new QPushButton("⌫", this);
    backspaceButton->setStyleSheet("font-size: 18px; background-color: #FF0000; border: 2px solid #cc5500; border-radius: 10px;");
    grid->addWidget(backspaceButton, 0, 3);  // Row 0, Col 3
    connect(backspaceButton, &QPushButton::clicked, this, &MainWindow::removeLastCharacter);

    // Calculator button texts
    QString buttons[] = {
        "7", "8", "9", "/",
        "4", "5", "6", "*",
        "1", "2", "3", "+",
        "0", "(", ")", "-",
        ".", "^", "%", "="
    };

    // Add buttons to the grid (start from row 1 to leave row 0 for backspace)
    int row = 1, col = 0;
    for (const QString &text : buttons) {
        QPushButton *btn = new QPushButton(text);
        btn->setStyleSheet("font-size: 20px; padding: 15px; background-color: #333333; border: 2px solid #333333; border-radius: 10px;");
        grid->addWidget(btn, row, col);

        if (text == "=") {
            connect(btn, &QPushButton::clicked, this, &MainWindow::onEqualClicked);
        } else {
            connect(btn, &QPushButton::clicked, this, [=]() {
                display->insert(text);
            });
        }

        if (++col == 4) {
            col = 0;
            ++row;
        }
    }

    // Add grid layout to main layout
    mainLayout->addLayout(grid);
    setCentralWidget(central);
}

void MainWindow::onEqualClicked() {
    QByteArray inputBytes = display->text().toLatin1();
    char infix[100], postfix[100];

    strncpy(infix, inputBytes.data(), sizeof(infix));
    infix[sizeof(infix) - 1] = '\0';

    InfixToPostfix(infix, postfix);
    double result = calculator(postfix);

   display->setText(QString::number(result, 'g', 15));
}

void MainWindow::removeLastCharacter() {
    QString text = display->text();
    if (!text.isEmpty()) {
        text.chop(1);
        display->setText(text);
    }
}
