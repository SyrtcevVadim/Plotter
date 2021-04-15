#ifndef ABOUTPROGDIALOG_H
#define ABOUTPROGDIALOG_H
#include<QtWidgets>

class AboutProgDialog: public QDialog
{
    Q_OBJECT

private:
    /// Stores brief program description
    QLabel *programDescriptionLbl;
    /// Stores link to the repository of this program
    QLabel *linkToGithubLbl;
    /// Stores license information about this program
    QLabel *licenseLbl;
    /// Stores the icon of this program
    QLabel *imageLbl;

public:
    QPushButton *closeBtn;
    AboutProgDialog(QWidget *parent = nullptr);
};

#endif // ABOUTPROGDIALOG_H
