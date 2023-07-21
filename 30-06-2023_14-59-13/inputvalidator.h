#ifndef INPUTVALIDATOR_H
#define INPUTVALIDATOR_H


#include <QLineEdit>
#include <QIntValidator>

class InputValidator {
public:
    static void setValidator(QLineEdit *lineEdit, int min, int max);
    static void showErrorWindow(const QString& errorMessage);
};
#endif // INPUTVALIDATOR_H
