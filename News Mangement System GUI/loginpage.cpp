
#include "loginpage.h"
#include "registerpage.h"

LoginPage::LoginPage(
    loadAndStoreFiles* tools, 
    QWidget*           parent) 

    :QWidget{parent}, 
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    tool = tools;
    tool->loadNews();
    tool->loadUsers();
    
    setGeometry(0, 0, 1371, 932);
    setFixedSize(size());

    QLabel* imageLabel = new QLabel(this);
    QPixmap image("K:\\C++\\GUI Qt\\NewsGUI\\User login.png");

    QPixmap scaledImage = image.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    imageLabel->setPixmap(scaledImage);
    imageLabel->move(0, 0);

    QPushButton*  RegBtn = new QPushButton("Register",this);
    RegBtn->setGeometry(696,644,269,50);
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
    connect(RegBtn, &QPushButton::clicked, this, &LoginPage::registerUser);

    QPushButton*  LoginBtn = new QPushButton("Login",this);
    LoginBtn->setGeometry(392,644,269,50); // use LoginBtn instead of RegBtn here
    LoginBtn->setStyleSheet("QPushButton {\
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

    connect(LoginBtn, &QPushButton::clicked, this, &LoginPage::login);


    // Set up username line edit
    username = new QLineEdit(this);
    username->setGeometry(583, 470, 382, 50);
    username->setStyleSheet("QLineEdit {\
                                  font-size: 20px;\
                                  font-family: Inter;\
                                  border-radius: 20px;\
                                  background-color: #D9D9D9;\
                                  padding: 10px;\
                                }");
    username->setFocus();

    // Set up password line edit
    password = new QLineEdit(this);
    password->setEchoMode(QLineEdit::Password);
    password->setGeometry(583, 550, 382, 50);
    password->setStyleSheet(
        "QLineEdit {\
            font-size: 20px;\
            font-family: Inter;\
            border-radius: 20px;\
            background-color: #D9D9D9;\
            padding: 10px;\
        }");

    QPushButton* exitBtn = new QPushButton("Exit", this);
    exitBtn->setGeometry(25, 847, 269, 50); // use LoginBtn instead of RegBtn here
    exitBtn->setStyleSheet("QPushButton {\
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

    connect(exitBtn, &QPushButton::clicked, this, &LoginPage::savaAndClose);
}

void LoginPage::savaAndClose() {

    tool->saveAndClose(tool->users, tool->news);
    this->close();

}

void LoginPage::registerUser()
{
    RegisterPage *newWidget = new RegisterPage(tool,this);
    newWidget->show();
}

void LoginPage::login() {

    string usernameSTD = username->text().toUtf8().constData();
    string passwordSTD = password->text().toUtf8().constData();

    if (usernameSTD.empty() || passwordSTD.empty()) {
        QMessageBox::critical(this, "Error", "enter the required credentials.");
    }
    else if (tool->users[usernameSTD].username.empty()) {

        QMessageBox::warning(this, "Error", "User Doesn't Exist");
    }
    else if (tool->users[usernameSTD].pass != passwordSTD) {
        QMessageBox::warning(this, "Error", "Incorrect Password.");
    }
    else {

        if (tool->users[usernameSTD].role == "user") {
            user = new UserWidget(username->text(), tool, this);
            user->show();
        }
        else {
            admin = new adminWidget(username->text(), tool, this);
            admin->show();
        }
    }
}

LoginPage::~LoginPage()
{
    delete ui;
}
