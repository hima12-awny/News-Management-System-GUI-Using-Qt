#ifndef REGISTERPAGE_H
#define REGISTERPAGE_H


#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include "./ui_widget.h"

#include "loadandstore.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE


class RegisterPage : public QWidget
{
    Q_OBJECT

public:
    RegisterPage(loadAndStoreFiles* tool, QWidget* parent = nullptr);

    ~RegisterPage();

    void onbackBtnClicked();
    void regest();

private:
    Ui::Widget* ui;
    loadAndStoreFiles* tool;
    QLineEdit* username;
    QLineEdit* password;
};

#endif // REGISTERPAGE_H
