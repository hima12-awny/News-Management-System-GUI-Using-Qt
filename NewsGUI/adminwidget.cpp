
#include <ctime>
#include <string>
#include <iostream>

#include "adminwidget.h"
#include "./ui_widget.h"
#include "loginpage.h"

#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include  <QInputDialog>
#include <QGroupBox>
#include <QTextEdit>
#include <QColorDialog>
#include <QScrollArea>
#include <QVBoxLayout>

adminWidget::adminWidget(

    QString             name,
    loadAndStoreFiles*& tools,
    QWidget*            parent)

    : QWidget(parent)
    , ui(new Ui::Widget)

{
    username = name;
    tool     = tools;

    setGeometry(0, 0, 1371, 932);
    setFixedSize(1371, 932);
    this->parent = parent;
    parent->setWindowTitle("Admin");


    //create the background image
    QLabel* adminImage = new QLabel(this);
    QPixmap image("K:\\C++\\GUI Qt\\NewsGUI\\imgs\\AdminFrame.png");

    QPixmap scaledImage = image.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    adminImage->setPixmap(scaledImage);
    adminImage->move(0, 0);


    QLabel* userNameLbl = new QLabel(this);
    userNameLbl->setText("Hi, " + username);
    userNameLbl->setObjectName("userNameLbl");
    userNameLbl->setStyleSheet(" #userNameLbl{ font-size: 45px; color:#DFE1E7; }");
    userNameLbl->move(27, 279);


    QPushButton* addnews = new QPushButton("Add News", this);
    addnews->setGeometry(65, 570, 173, 52);
    addnews->setStyleSheet("QPushButton {\
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


    QPushButton* addadmin = new QPushButton("Add Admin", this);
    addadmin->setGeometry(65, 630, 173, 52);
    addadmin->setStyleSheet("QPushButton {\
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

    connect(addadmin, &QPushButton::clicked, this, &adminWidget::makeAdminReg);

    QPushButton* logout = new QPushButton("Log Out", this);
    logout->setGeometry(65, 690, 173, 52);
    logout->setStyleSheet("QPushButton {\
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

    ////////////////////////////////////////////////////////////////////

    mainGroup = new QGroupBox(this);
    mainGroup->setGeometry(326, 10, 1035, 905);
    mainGroup->setObjectName("mainGroup");
    mainGroup->setStyleSheet("#mainGroup {border-radius: 12px; background-color: transparent; }");

    mainGroupLayout = new QHBoxLayout(mainGroup);

    //////////////////////////////////////////////////////////////////////

    contianer = new QScrollArea(this);
    contianer->setGeometry(326, 10, 1035, 905);
    contianer->setStyleSheet("QScrollArea{background-color:#A5B3C1; border: none;}");


    scrollWidget = new QWidget(contianer);
    scrollWidget->setObjectName("scrollWidget");
    scrollWidget->setStyleSheet("#scrollWidget{background-color: transparent;  border:none; }");


    scrollLayout = new QVBoxLayout(scrollWidget);

    contianer->setWidgetResizable(true);
    contianer->setWidget(scrollWidget);

    ////////////////////////////////////////////////////////////////////

    printAllNews();

    mainGroupLayout->addWidget(contianer);

    connect(logout, &QPushButton::clicked, this, [=](){ this->close(); parent->setWindowTitle("Login");  });

    connect(addnews, &QPushButton::clicked, this, [=]() {

        adminWidget::makeAddOrUpdateFrame(generate_id());

        });
}

void adminWidget::makeAdminReg() {

    QWidget* adminReg = new QWidget(this);

    adminReg->setGeometry(0, 0, 1371, 932);
    parent->setWindowTitle("Admin Regester");


    //create the background image
    QLabel* registerimage = new QLabel(adminReg);
    QPixmap image("K:\\C++\\GUI Qt\\NewsGUI\\imgs\\AdminRegister.png");
    QPixmap scaledImage = image.scaled( size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    registerimage->setPixmap(scaledImage);
    registerimage->move(0, 0);


    QPushButton* RegBtn = new QPushButton("Register", adminReg);
    RegBtn->setGeometry(680, 643, 269, 50);
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
    QPushButton* BackBtn = new QPushButton("Back", adminReg);
    BackBtn->setGeometry(377, 643, 269, 50); // use LoginBtn instead of RegBtn here
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
    connect(BackBtn, &QPushButton::clicked, this, [=]() {
        adminReg->hide();
        parent->setWindowTitle("Admin");
        printAllNews();
        });

    // Set up username line edit
    QLineEdit* usernameLineEdit = new QLineEdit(adminReg);
    usernameLineEdit->setGeometry(568, 474, 382, 50);
    usernameLineEdit->setStyleSheet("QLineEdit {\
                                  font-size: 20px;\
                                  font-family: Inter;\
                                  border-radius: 20px;\
                                  background-color: #D9D9D9;\
                                  padding: 10px;\
                                }");


    // Set up password line edit
    QLineEdit* passwordLineEdit = new QLineEdit(adminReg);
    passwordLineEdit->setGeometry(568, 550, 382, 50);
    passwordLineEdit->setStyleSheet("QLineEdit {\
                                  font-size: 20px;\
                                  font-family: Inter;\
                                  border-radius: 20px;\
                                  background-color: #D9D9D9;\
                                  padding: 10px;\
                                }");

    connect(RegBtn, &QPushButton::clicked, this, [=]() {

        string name = usernameLineEdit->text().toUtf8().constData();
        string pass = passwordLineEdit->text().toUtf8().constData();

        if (name.empty() || pass.empty()) {
            QMessageBox::critical(this, "Error", "enter the required credentials.");
        } 
        else if (!tool->users[name].username.empty()) {

            QMessageBox::warning(this, "Error", "Admin Already Exists");
        }
        else {

            QMessageBox::information(this, "Congratulations", "Admin Added successfully.");
            tool->users[name] = { name, pass, "admin", {}, {""} };
            parent->setWindowTitle("Admin");
            adminReg->hide();
        }

        });

    adminReg->show();
}

void adminWidget::makeAddOrUpdateFrame(int id) {

    NewsArticle article = tool->news[id];

    insideAddOrUpdate = new QWidget(this);
    insideAddOrUpdate->setGeometry(0, 0, 1371, 932);

    //create the background image
    QLabel* adminImage = new QLabel(insideAddOrUpdate);
    QPixmap image("K:\\C++\\GUI Qt\\NewsGUI\\imgs\\AdminFrame.png");

    QPixmap scaledImage = image.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    adminImage->setPixmap(scaledImage);
    adminImage->move(0, 0);

    QLabel* userNameLbl = new QLabel(insideAddOrUpdate);
    userNameLbl->setText("Hi, " + username);
    userNameLbl->setObjectName("userNameLbl");
    userNameLbl->setStyleSheet(" #userNameLbl{ font-size: 45px; color:#DFE1E7; }");
    userNameLbl->move(27, 279);
    
    /////////////////////////////////////////

    QLineEdit* title = new QLineEdit(insideAddOrUpdate);
               title->setGeometry(629, 79, 698, 63);
               title->setStyleSheet("QLineEdit {\
                                        font-size: 20px;\
                                        font-family: Inter;\
                                        border-radius: 20px;\
                                        background-color: #D9D9D9;\
                                        padding: 10px;\
                                       }");
               title->setText(article.title.c_str());


    QLineEdit* cat = new QLineEdit(insideAddOrUpdate);
    cat->setGeometry(629, 177, 698, 63);
    cat->setStyleSheet("QLineEdit {\
                                  font-size: 20px;\
                                  font-family: Inter;\
                                  border-radius: 20px;\
                                  background-color: #D9D9D9;\
                                  padding: 10px;\
                                }");
    cat->setText(article.category.c_str());



    QLineEdit* author = new QLineEdit(insideAddOrUpdate);
    author->setGeometry(629, 293, 698, 63);
    author->setStyleSheet("QLineEdit {\
                                  font-size: 20px;\
                                  font-family: Inter;\
                                  border-radius: 20px;\
                                  background-color: #D9D9D9;\
                                  padding: 10px;\
                                }");
    author->setText(article.author.c_str());


    QTextEdit* description = new QTextEdit(insideAddOrUpdate);
    description->setGeometry(629, 419, 698, 399);
    description->setAlignment(Qt::AlignTop);
    description->setLineWrapMode(QTextEdit::LineWrapMode::WidgetWidth);
    description->setStyleSheet("QTextEdit {\
                                  font-size: 20px;\
                                  font-family: Inter;\
                                  border-radius: 20px;\
                                  background-color: #D9D9D9;\
                                  padding: 10px;\
                                }");

    description->setText(article.description.c_str());


    ////////////////////////////////////////

    QPushButton* back = new QPushButton("Back", insideAddOrUpdate);
    back->setGeometry(40, 836, 244, 52);
    back->setStyleSheet("QPushButton {\
                        font-size:20px;\
                        font-family:Inter;\
                        border-radius: 10px;\
                        background-color: #D9D9D9;\
                        padding:10px;\
                      }\
                      QPushButton:hover {\
                        background-color: #245B96;\
                        color:#fff;\
                        transition: background-color 16s ease-in-out;\
                      }");

    connect(back, &QPushButton::clicked, this, [=]() {

        insideAddOrUpdate->hide();
        printAllNews();

        });


    QPushButton* confirmBtn = new QPushButton("Confirm", insideAddOrUpdate);
    confirmBtn->setGeometry(1083, 827, 244, 52);
    confirmBtn->setStyleSheet("QPushButton {\
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

    connect(confirmBtn, &QPushButton::clicked, this, [=]() 
        {
            string catSTD         = cat->        text().toUtf8().constData();
            string titleSTD       = title->      text().toUtf8().constData();
            string authorSTD      = author->     text().toUtf8().constData();
            string descriptionSTD = description->toPlainText().toUtf8().constData();

            if (catSTD.empty() || titleSTD.empty() || authorSTD.empty() || descriptionSTD.empty()) {
                QMessageBox::critical(this, "Error", "enter all the required credentials.");
                return;
            }
            bool add = article.title.empty();

            bool updateCat = !article.category.empty() && article.category != catSTD;
        
            if (tool->categorys[catSTD].empty()) {

                QMessageBox::StandardButton reply = QMessageBox::question(insideAddOrUpdate,
                    "NOTE", "This category doesn't Exist. do you want to add this category?", QMessageBox::Yes | QMessageBox::No);

                if (reply == QMessageBox::No) return;
            
                QMessageBox::information(insideAddOrUpdate, "done", "category added successfully.");
            }

            if (add) {
                time_t now = std::time(nullptr);

                // Convert to local time
                tm localTime;
                localtime_s(&localTime, &now);

                // Extract date components
                int year  = localTime.tm_year + 1900;
                int month = localTime.tm_mon  + 1;
                int day   = localTime.tm_mday;

                // Print date
                string currDate = to_string(day) + "/" + to_string(month) + "/" + to_string(year);

                tool->news[id] = { id ,catSTD, titleSTD, authorSTD, descriptionSTD , currDate, {0.0}, {{" "," "}}, 0};
                QMessageBox::information(this, "done", "Added successfully.");
                insideAddOrUpdate->hide();
                tool->ids.push_back(id);
                printAllNews();
            }
            else {
                tool->news[id] = { id ,catSTD, titleSTD, authorSTD, descriptionSTD , article.date, article.rates, article.comments,article.spam };
                QMessageBox::information(this, "done", "Updated successfully.");
                insideAddOrUpdate->hide();
                printAllNews();
            }
        
            if (updateCat) {

                auto& category_vector = tool->categorys[article.category];
                auto it = std::remove(category_vector.begin(), category_vector.end(), id);
                category_vector.erase(it, category_vector.end());
             }
        
             tool->categorys[catSTD].push_back(id);

       }

    );

    insideAddOrUpdate->show();
}

int adminWidget::generate_id()
{
    // Function to generate a unique ID for the article
    int max_id = 0;
    for (int id : tool->ids) {

        if (id > max_id) {
            max_id = id;
        }
    }
    return ++max_id;
}

void adminWidget::printAllNews()
{
    QLayoutItem* child;
    while ((child = scrollLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    for (auto art : tool->news) {
        printnewsforadmin(art.second);
    }
}

void adminWidget::printnewsforadmin(NewsArticle article)
{
    if (article.title.empty()) return;

    int shifyRow = 4;
    QGroupBox* newsbox = new QGroupBox();
    QGridLayout* newsboxlayout = new QGridLayout(newsbox);
    newsbox->setObjectName("newsbox");
    newsbox->setStyleSheet("#newsbox{background-color: #1B4775; border-radius: 20px;}");
    newsbox->setFixedWidth(1035-70);

    QLabel* title = new QLabel(this);
    title->setObjectName("title");
    title->setStyleSheet("#title{font-size:50px; color:#fff;}");
    title->setText(article.title.c_str());
    title->setWordWrap(1);
    newsboxlayout->addWidget(title, 0, 0, 1+ shifyRow, 6);


    string newsPropStr = "Author: " + article.author       + " - " +
                         "Date: " + article.date           + " - " + 
                         "Rate: " + article.printRate()    + " - " +
                         "Category: " + article.category   + " - " + 
                         "Spam: " + to_string(article.spam);

    QLabel* newsProp = new QLabel(this);
    newsProp->setObjectName("newsProp");
    newsProp->setStyleSheet("#newsProp{color:#fff; font-size: 15px;}");
    newsProp->setText(((std::string)newsPropStr).c_str());
    newsboxlayout->addWidget(newsProp, 1+ shifyRow, 0, 1, 6);

    QTextEdit* description = new QTextEdit();
    description->setText(((std::string)article.description).c_str());
    description->setReadOnly(true);
    description->setObjectName("description");
    description->setFixedHeight(342);

    description->setStyleSheet("#description {background-color: transparent; font-size: 20px; color:#fff; border:none; }");
    newsboxlayout->addWidget(description, 2+ shifyRow, 0, 10, 6);

    QPushButton* deleteBtn = new QPushButton("Delete");
    deleteBtn->setObjectName("deleteBtn");
    deleteBtn->setFixedSize(100, 50);
    deleteBtn->setStyleSheet(
        "#deleteBtn{\
            font-size:20px;\
            font-family:Inter;\
            border-radius: 20px; \
            background-color: #D9D9D9;\
             padding:10px;\
         }\
            \
         #deleteBtn::hover{\
                background-color: #245B96; \
                color:#fff;\
         }"
    );

    newsboxlayout->addWidget(deleteBtn, 12+ shifyRow, 0);

    QPushButton* updateBtn = new QPushButton("Update");
    updateBtn->setObjectName("update");
    updateBtn->setFixedSize(100, 50);
    updateBtn->setStyleSheet(
        "#update{font-size:20px; font-family:Inter; border-radius: 20px; background-color: #D9D9D9; padding:10px; }\
         #update::hover{background-color: #245B96; color:#fff;}"
    );
    newsboxlayout->addWidget(updateBtn, 12+ shifyRow, 1);

    QLabel* commBg = new QLabel(this);
    commBg->setObjectName("commBg");
    commBg->setStyleSheet("#commBg{ background-color: #6684A3; border-radius:20px; }");
    commBg->setFixedHeight(200);
    newsboxlayout->addWidget(commBg, 13+ shifyRow, 0, 8, 6);

    QLabel* commentsLbl = new QLabel(this);
    commentsLbl->setObjectName("commentsLbl");
    commentsLbl->setText("  Comments");
    commentsLbl->setStyleSheet("#commentsLbl{ background-color: transparent; color:#fff; font-size:25px;  }");
    newsboxlayout->addWidget(commentsLbl, 13+ shifyRow, 0);

    // Create the text edit widget
    QTextEdit* comments = new QTextEdit();
    comments->setText(((std::string)article.getcomment()).c_str());
    comments->setReadOnly(true);
    comments->setFixedHeight(150);
    comments->setObjectName("comments");
    comments->setStyleSheet("#comments {background-color: transparent; font-size: 20px; color:#fff; border:none; }");
    newsboxlayout->addWidget(comments, 14+ shifyRow, 0, 8, 6);

    connect(updateBtn, &QPushButton::clicked, this, [=]() {
        makeAddOrUpdateFrame(article.id);
        });

    connect(deleteBtn, &QPushButton::clicked, this, [=]() {

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Confirmation", "Are You Sure about Deleting this News?", QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            tool->removeNewsArticle(article.id, tool->news, tool->ids, tool->categorys);
            delete newsGUI[article.id].box;
        }
     });

    newsGUI[article.id] = { deleteBtn,updateBtn,newsbox,article};

    newsboxlayout->setSpacing(10);
    scrollLayout->addWidget(newsbox);
}

adminWidget::~adminWidget() {
    delete ui;
}