#include "GUI/aboutprogdialog.h"
#include<QtWidgets>

AboutProgDialog::AboutProgDialog(QWidget *parent): QDialog(parent, Qt::WindowTitleHint)
{
    programDescriptionLbl = new QLabel(tr("This program is designed for drawing functions' plots and for investigating functions' behaviour depending on "
                                        "its' parameters' values.\nIs developed as a course work for OOP in C++"));
    linkToGithubLbl = new QLabel(tr(R"(<a href="https://github.com/SyrtcevVadim/Plotter">Link to Github-repository</a>)"));
    linkToGithubLbl->setOpenExternalLinks(true);
    licenseLbl = new QLabel(tr("Developer: Syrtcev Vadim Igorevich\nE-mail: syrtcevvi@gmail.com\n"
                            "Application free for copying and use"));
    imageLbl = new QLabel(tr("Here should be an application's icon"));

    closeBtn = new QPushButton(tr("Close"));
    connect(closeBtn, SIGNAL(clicked()), SLOT(accept()));

    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->addWidget(imageLbl, 0,0);
    mainLayout->addWidget(programDescriptionLbl, 0, 1);
    mainLayout->addWidget(linkToGithubLbl, 1, 1);
    mainLayout->addWidget(licenseLbl, 2,1);
    mainLayout->addWidget(closeBtn, 3,1);
    setLayout(mainLayout);
}
