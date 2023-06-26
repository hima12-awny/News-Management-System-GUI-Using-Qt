#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include "loadandstore.h"
#include "userWidget.h"
#include "adminwidget.h"

#include "./ui_widget.h"

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class LoginPage : public QWidget

{
    Q_OBJECT

public:
    LoginPage(
        loadAndStoreFiles* tool, 
        QWidget*           parent = nullptr);

    ~LoginPage();

    void login();
    void registerUser();
    void savaAndClose();

    UserWidget*  user  = NULL;
    adminWidget* admin = NULL;
    

private:

    Ui::Widget *ui;

    QLineEdit* username;
    QLineEdit* password;
    loadAndStoreFiles* tool;
};

#endif // LOGINPAGE_H