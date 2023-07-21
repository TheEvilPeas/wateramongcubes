#include "inputvalidator.h"
#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QIntValidator>
#include <vector>
#include <QGridLayout>
#include <QScrollArea>
#include <vector>
#include <queue>

// В классе ErrorWindow
class ErrorWindow : public QDialog {
public:
    ErrorWindow(const QString& errorMessage) {
        QLabel* errorLabel = new QLabel(errorMessage);
        QVBoxLayout* layout = new QVBoxLayout;
        layout->addWidget(errorLabel);
        setLayout(layout);
    }
};

void InputValidator::showErrorWindow(const QString& errorMessage) {
    ErrorWindow errorWindow(errorMessage);
    errorWindow.exec();
}

void InputValidator::setValidator(QLineEdit *lineEdit, int min, int max) {
    QIntValidator* validator = new QIntValidator(min, max, lineEdit);
    lineEdit->setValidator(validator);

    QObject::connect(lineEdit, &QLineEdit::editingFinished, [=]() {
            QString text = lineEdit->text();
            int pos = 0;
            if (validator->validate(text, pos) != QValidator::Acceptable) {
                showErrorWindow("Ошибка: введено недопустимое значение");
            }
    });
}

