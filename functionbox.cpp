#include "functionbox.h"

FunctionBox::FunctionBox(QWidget *parent) : QWidget(parent)
{
    resize(270,120);
    // Инициализируем все внутренние виджеты
    functionName = new QLabel("y=");
    functionBody = new QLineEdit();

    aLbl = new QLabel("a");
    bLbl = new QLabel("b");
    cLbl = new QLabel("c");
    dLbl = new QLabel("d");

    aParamBox = new QLineEdit();

    bParamBox = new QLineEdit();

    cParamBox = new QLineEdit();

    dParamBox = new QLineEdit();


    xLbl = new QLabel("<=X<=");

    minimumVarValueBox = new QLineEdit();
    maximumVarValueBox = new QLineEdit();

    errorLabel = new QLabel("Error:");
    errorText = new QLabel("everything is good!");

    QVBoxLayout *vBox = new QVBoxLayout(this);

    // Первая строчка виджетов
    QHBoxLayout *firstLine = new QHBoxLayout();
    // Добавляем первую строчку виджетов
    firstLine->addWidget(functionName);
    firstLine->addWidget(functionBody);

    vBox->addLayout(firstLine);


    QHBoxLayout *errorLine = new QHBoxLayout();
    errorLine ->addWidget(errorLabel);
    errorLine ->addWidget(errorText);

    vBox->addLayout(errorLine);

    QHBoxLayout *secondLine = new QHBoxLayout();
    secondLine->addWidget(aLbl);
    secondLine->addWidget(aParamBox);

    secondLine ->addWidget(bLbl);
    secondLine ->addWidget(bParamBox);

    secondLine->addWidget(minimumVarValueBox);
    secondLine->addWidget(xLbl);
    secondLine->addWidget(maximumVarValueBox);

    vBox->addLayout(secondLine);

    // Третья строчка виджетов
    QHBoxLayout *thirdLine = new QHBoxLayout();
    thirdLine->addWidget(cLbl);
    thirdLine->addWidget(cParamBox);
    thirdLine->addWidget(dLbl);
    thirdLine ->addWidget(dParamBox);

    vBox->addLayout(thirdLine);

    setLayout(vBox);

}
