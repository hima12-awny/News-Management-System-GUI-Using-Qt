
#ifndef ADMINREGISTER_H
#define ADMINREGISTER_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

class AdminRegister : public QWidget
{
    Q_OBJECT
public:
    explicit AdminRegister(QWidget *parent = nullptr);
    void onbackBtnClicked();



};

#endif // ADMINREGISTER_H
