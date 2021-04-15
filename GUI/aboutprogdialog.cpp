#include "GUI/aboutprogdialog.h"
#include<QtWidgets>

AboutProgDialog::AboutProgDialog(QWidget *parent): QDialog(parent, Qt::WindowTitleHint)
{
    programDescriptionLbl = new QLabel("Программа Izum предназначена для построения графиков функций и изучения их поведения в зависимости от"
                                        "значений параметров.\nРазработана в качестве курсовой работы за 2.5 месяца.");
    linkToGithubLbl = new QLabel(R"(<a href="https://github.com/SyrtcevVadim/Plotter">Ссылка на репозиторий проекта</a>)");
    linkToGithubLbl->setOpenExternalLinks(true);
    licenseLbl = new QLabel("Разработчик: Сырцев Вадим Игоревич\nПочта: syrtcevvi@gmail.com\n"
                            "Приложение свободно для копирования и использования");
    imageLbl = new QLabel("Здесь должна быть иконка приложения");

    closeBtn = new QPushButton("Закрыть");
    connect(closeBtn, SIGNAL(clicked()), SLOT(accept()));

    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->addWidget(imageLbl, 0,0);
    mainLayout->addWidget(programDescriptionLbl, 0, 1);
    mainLayout->addWidget(linkToGithubLbl, 1, 1);
    mainLayout->addWidget(licenseLbl, 2,1);
    mainLayout->addWidget(closeBtn, 3,1);
    setLayout(mainLayout);
}
