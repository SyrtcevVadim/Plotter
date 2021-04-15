#ifndef ABOUTPROGDIALOG_H
#define ABOUTPROGDIALOG_H
#include<QtWidgets>

class AboutProgDialog: public QDialog
{
    Q_OBJECT
public:
    QLabel *programDescriptionLbl;
    QLabel *linkToGithubLbl;
    QLabel *licenseLbl;
    QLabel *imageLbl;
    QPushButton *closeBtn;
    AboutProgDialog(QWidget *parent = nullptr);
};

#endif // ABOUTPROGDIALOG_H
