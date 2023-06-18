#include "adminregister.h"

#include "loginpage.h"


AdminRegister::AdminRegister(QWidget *parent)
    : QWidget{parent}
{
    setGeometry(0, 0, 1371, 932);
    setFixedSize(size());

    //create the background image
    QLabel* registerimage = new QLabel(this);
    QPixmap image("K:\\C++\\GUI Qt\\NewsGUI\\Admin register.png");
    QPixmap scaledImage = image.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    registerimage->setPixmap(scaledImage);
    registerimage->move(0, 0);


    QPushButton*  RegBtn = new QPushButton("Register",this);
    RegBtn->setGeometry(680,643,269,50);
RegBtn->setStyleSheet("QPushButton {\
                        font-size:20px;\
                        font-family:Inter;\
                        border-radius: 20px;\
                        background-color: #153E69;\
                        color: #DFE1E7;\
                        padding:10px;\
                      }\
                      QPushButton:hover {\
                        background-color: #D9D9D9;\
                        color: #2F455C;\
                        transition: background-color 16s ease-in-out;\
                      }");

    //setup the back button that brings the user back to the login page
    QPushButton*  BackBtn = new QPushButton("Back",this);
    BackBtn->setGeometry(377,643,269,50); // use LoginBtn instead of RegBtn here
BackBtn->setStyleSheet("QPushButton {\
                        font-size:20px;\
                        font-family:Inter;\
                        border-radius: 20px;\
                        background-color: #153E69;\
                        color: #DFE1E7;\
                        padding:10px;\
                      }\
                      QPushButton:hover {\
                        background-color: #D9D9D9;\
                        color: #2F455C;\
                        transition: background-color 16s ease-in-out;\
                      }");
    connect(BackBtn, &QPushButton::clicked, this, &AdminRegister::onbackBtnClicked);




// Set up username line edit
    QLineEdit *usernameLineEdit = new QLineEdit(this);
    usernameLineEdit->setGeometry(568, 474, 382, 50);
usernameLineEdit->setStyleSheet("QLineEdit {\
                                  font-size: 20px;\
                                  font-family: Inter;\
                                  border-radius: 20px;\
                                  background-color: #D9D9D9;\
                                  padding: 10px;\
                                }");


// Set up password line edit
    QLineEdit *passwordLineEdit = new QLineEdit(this);
    passwordLineEdit->setGeometry(568, 550, 382, 50);
passwordLineEdit->setStyleSheet("QLineEdit {\
                                  font-size: 20px;\
                                  font-family: Inter;\
                                  border-radius: 20px;\
                                  background-color: #D9D9D9;\
                                  padding: 10px;\
                                }");
}

void AdminRegister :: onbackBtnClicked()
{
    this->hide();
}
