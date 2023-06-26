
#include "registerpage.h"
#include "loginpage.h"

RegisterPage::RegisterPage(loadAndStoreFiles* tools, QWidget *parent) :QWidget{ parent }, ui(new Ui::Widget)
{
    setGeometry(0, 0, 1371, 932);
    setFixedSize(size());
    this->parent = parent;
    parent->setWindowTitle("Register");


    tool = tools;

    //create the background image
    QLabel* registerimage = new QLabel(this);
    QPixmap image("K:\\C++\\GUI Qt\\NewsGUI\\User register.png");

    QPixmap scaledImage = image.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    registerimage->setPixmap(scaledImage);
    registerimage->move(0, 0);


    QPushButton*  RegBtn = new QPushButton("Register",this);
    RegBtn->setGeometry(692,647,269,50);
    RegBtn->setStyleSheet("QPushButton {\
                        font-size:20px;\
                        font-family:Inter;\
                        border-radius: 20px;\
                        background-color: #D9D9D9;\
                        padding:10px;\
                      }\
                      QPushButton:hover {\
                        background-color: #245B96;\
                        color:#fff;\
                        transition: background-color 16s ease-in-out;\
                      }");


    connect(RegBtn, &QPushButton::clicked, this, &RegisterPage::regest);


    //setup the back button that brings the user back to the login page
    QPushButton*  BackBtn = new QPushButton("Back",this);
    BackBtn->setGeometry(388,647,269,50); // use LoginBtn instead of RegBtn here
    BackBtn->setStyleSheet("QPushButton {\
                        font-size:20px;\
                        font-family:Inter;\
                        border-radius: 20px;\
                        background-color: #D9D9D9;\
                        padding:10px;\
                      }\
                      QPushButton:hover {\
                        background-color: #245B96;\
                        color:#fff;\
                        transition: background-color 16s ease-in-out;\
                      }");

    connect(BackBtn, &QPushButton::clicked, this, &RegisterPage::onbackBtnClicked);


    // Set up username line edit
    username = new QLineEdit(this);
    username->setGeometry(580, 472, 382, 50);
    username->setStyleSheet("QLineEdit {\
                                  font-size: 20px;\
                                  font-family: Inter;\
                                  border-radius: 20px;\
                                  background-color: #D9D9D9;\
                                  padding: 10px;\
                                }");


    // Set up password line edit
    password = new QLineEdit(this);
    password->setGeometry(580, 550, 382, 50);
    password->setStyleSheet("QLineEdit {\
                                  font-size: 20px;\
                                  font-family: Inter;\
                                  border-radius: 20px;\
                                  background-color: #D9D9D9;\
                                  padding: 10px;\
                                }");
}

void RegisterPage::regest() {

    string usernameSTD = username->text().toUtf8().constData();
    string passwordSTD = password->text().toUtf8().constData();

    if (usernameSTD.empty() || passwordSTD.empty()) {
        QMessageBox::critical(this, "Error", "enter the required credentials.");
    }
    else if (!tool->users[usernameSTD].username.empty()) {

        QMessageBox::warning(this, "Error", "User Already Exists");
    }
    else {

        QMessageBox::information(this, "Congratulations", "User Added successfully.");

        tool->users[usernameSTD] = { usernameSTD, passwordSTD, "user", {}, {""} };

        onbackBtnClicked();
    }
}



void RegisterPage::onbackBtnClicked()
{
    this->hide();
    parent->setWindowTitle("Login");
}

RegisterPage::~RegisterPage()
{
    delete ui;
}

