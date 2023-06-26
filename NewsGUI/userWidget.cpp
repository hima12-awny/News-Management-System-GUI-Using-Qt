#include "userWidget.h"
#include "loginpage.h"

#include "ui_widget.h"


UserWidget::UserWidget(
    QString             user,
    loadAndStoreFiles*& tools, 
    QWidget*            parent)

    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    tool        = tools;
    username    = user;
    usernameSTD = username.toUtf8().constData();

    prefrenceCategory = tool->users[usernameSTD].prefrenceCategory;
    spam = tool->users[usernameSTD].spam;

    setGeometry(0, 0, 1371, 932);
    setFixedSize(size());
    this->parent = parent;
    parent->setWindowTitle("Hello Dear");
    
    QLabel* mainBgLbl = new QLabel(this);
    QPixmap mainBg("K:\\C++\\GUI Qt\\NewsGUI\\UserFram.png");

    QPixmap scaledImage_mainBg = mainBg.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    mainBgLbl->setPixmap(scaledImage_mainBg);
    mainBgLbl->move(0, 0);

    QLabel* userNameLbl = new QLabel(this);
    userNameLbl->setText("Hi, "+ username);
    userNameLbl->setObjectName("userNameLbl");
    userNameLbl->setStyleSheet(" #userNameLbl{ font-size: 45px; color:#DFE1E7; }");
    userNameLbl->move(27,279);

    logout_user = new QPushButton("Logout", this);
    logout_user->setFixedSize(244, 55);
    logout_user->move(40, size().height() - 100);
    logout_user->setStyleSheet(
        "QPushButton{font-size:26px;font-family:Inter ;border-radius: 25px; background-color: #D9D9D9; }\
         QPushButton::hover{background-color: #245B96;color:#fff;}"
    );
    connect(logout_user, &QPushButton::clicked, this, &UserWidget::saveAndClose);

    displayBy = new QComboBox(this);
    displayBy->addItem("Latest News");
    displayBy->addItem("Prefrances");
    displayBy->addItem("Category");
    displayBy->addItem("Highest Rate");
    displayBy->move(1072, 44);
    displayBy->setFixedSize(241, 31);
    displayBy->setStyleSheet(
        "QComboBox{font-size:20px;font-family:Inter; border-radius: 12px; background-color: #D9D9D9; }"
    );

    connect(displayBy, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &UserWidget::printDis);

    displayByCat = new QComboBox(this);
    displayByCat->addItem("all");

    for (auto cat : tool->categorys) {
        if (cat.second.empty()) continue;
        displayByCat->addItem(cat.first.c_str());
    }

    displayByCat->move(477, 45);
    displayByCat->setFixedSize(241, 31);
    displayByCat->setStyleSheet(
        "QComboBox{ font-size:20px;font-family:Inter; border-radius: 12px; background-color: #D9D9D9; }"
    );
    displayByCat->setDisabled(true);
    connect(displayByCat, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &UserWidget::displayByCategory);


    mainGroup = new QGroupBox(this);
    mainGroup->setGeometry(326, 92, 1035, 825); 
    mainGroup->setObjectName("mainGroup");
    mainGroup->setStyleSheet("#mainGroup {border-radius: 12px; background-color: transparent; }");

    mainGroupLayout = new QHBoxLayout(mainGroup);

    ////////////////////////////////////////////////////////////////////
    contianer = new QScrollArea(this);
    contianer->setGeometry(326, 92, 1035, 825);
    contianer->setStyleSheet("QScrollArea{background-color: transparent; border: none;}");

    scrollWidget = new QWidget(contianer);
    scrollWidget->setObjectName("scrollWidget");
    scrollWidget->setStyleSheet("#scrollWidget{background-color: transparent;  border:none; }");
    
    scrollLayout = new QVBoxLayout(scrollWidget);

    contianer->setWidgetResizable(true);
    contianer->setWidget(scrollWidget);
    ////////////////////////////////////////////////////////////////////
    printLatest();

    mainGroupLayout->addWidget(contianer);
}

void UserWidget::makeInsideNews(int id) {

    NewsArticle article = tool->news[id];

    insideNews = new QWidget(this);
    insideNews->setGeometry(0, 0, 1371, 932);

    QLabel* insideNewsBgLbl = new QLabel(insideNews);
    QPixmap insideNewsBg("K:\\C++\\GUI Qt\\NewsGUI\\insideNewsFram.png");

    QPixmap scaledImage_insideNewsBg = insideNewsBg.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    insideNewsBgLbl->setPixmap(scaledImage_insideNewsBg);
    insideNewsBgLbl->move(0, 0);

    // username
    QLabel* userNameLbl = new QLabel(insideNews);
    userNameLbl->setText("Hi, " + username);
    userNameLbl->setObjectName("userNameLbl");
    userNameLbl->setStyleSheet("#userNameLbl{font-size: 45px; color:#DFE1E7;}");
    userNameLbl->move(27, 279);

    // title
    QLabel* title = new QLabel(insideNews);
    title->setGeometry(355,33, 900, 240);

    title->setText(article.title.c_str());
    title->setObjectName("newsTitle");
    title->setStyleSheet("#newsTitle{ color:#fff; font-size:45px; }");
    title->setMaximumHeight(200);
    title->setWordWrap(1);
    title->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);


    // prob
    string newsPropStr = "Author: " + article.author +        
                         " - Date: " + article.date     +       
                         " - Category: " + article.category +   
                         " - Spam: " + to_string(article.spam) + 
                         " - Rate: " + article.printRate();


    int ln = 130;

    QLabel* probs = new QLabel(insideNews);
    probs->setGeometry(355, 112 + ln, 587+50+200+100, 50);
    probs->setText(newsPropStr.c_str());
    probs->setObjectName("probs");
    probs->setStyleSheet("#probs{color:#fff; font-size:20px;}");


    // description
    QTextEdit* description = new QTextEdit(insideNews);
    description->setText(article.description.c_str());
    description->setGeometry(356, 152 + ln , 980, 469 - ln);
    description->setReadOnly(true);
    description->setObjectName("description");
    description->setStyleSheet("#description {background-color: transparent; font-size: 20px; color:#fff; border:none; }");

    // all comments
    QTextEdit* comments = new QTextEdit(insideNews);
    comments->setText(article.getcomment().c_str());
    comments->setReadOnly(true);
    comments->setGeometry(397, 683, 931, 125);
    comments->setObjectName("comments");
    comments->setStyleSheet("#comments {background-color: transparent; font-size: 20px; color:#fff; border:none; }");

    // commments input
    QLineEdit* comment_input = new QLineEdit(insideNews);
    comment_input->setGeometry(397, 820, 737,60);
    comment_input->setObjectName("comment_input");
    comment_input->setStyleSheet("#comment_input{ font-size:25px; border-radius:10px; padding:10px; }");


    // addComment btn
    QPushButton* addCommentBtn = new QPushButton("Add Comment", insideNews);
    addCommentBtn->setObjectName("addCommentBtn");
    addCommentBtn->setGeometry(1143, 820, 185, 60);
    addCommentBtn->setStyleSheet(
        "#addCommentBtn{\
            font-size:20px;\
            font-family:Inter; \
            border-radius: 10px;\
            background-color: #D9D9D9; \
        }\
         \
         #addCommentBtn::hover{\
            background-color: #245B96; \
            color:#fff;\
        }");

    connect(addCommentBtn, &QPushButton::clicked, this, [=]() {

        QString Qcomment  = comment_input->text();
        string commentSTD = Qcomment.toUtf8().constData();

        tool->news[id].comments.push_back({ usernameSTD ,commentSTD });
        comments->append(username + ": " + Qcomment);
        comment_input->clear();
        comment_input->setFocus();
        }
    );

    // rate btn
    QPushButton* rateBtn = new QPushButton("rate", insideNews);
    rateBtn->setObjectName("rate");
    rateBtn->setGeometry(1109, 641, 104, 38);
    rateBtn->setStyleSheet(
        "#rate{font-size: 15px; border-radius: 10px; background-color: #D9D9D9; padding:10px; color:#153F6A; }\
         #rate::hover{background-color: #245B96; color:#fff;}"
    );
    connect(rateBtn, &QPushButton::clicked, this, [=]() {

        bool ok;
        double value = QInputDialog::getDouble(this, tr("Enter Rate [1:5]"),
            tr("Value "), 1, 1, 5, 2, &ok);

        if (ok) {

            if (value >= 2.5) prefrenceCategory.insert(tool->news[id].category);

            tool->news[id].rates.push_back(value);

            int fs = probs->text().indexOf("Rate: ") + 6;
            QString res = probs->text().left(fs);

            probs->setText(res + tool->news[id].printRate().c_str());

            rateBtn->setDisabled(false);
        }
        }
    );


    // spam btn
    QPushButton* spamBtn = new QPushButton("spam", insideNews);
    spamBtn->setObjectName("spam");
    spamBtn->setGeometry(1224, 641, 104, 35+5);
    spamBtn->setStyleSheet(
        "#spam{ font-size:15px; font-family:Inter; border-radius: 10px; background-color: #D9D9D9; padding:10px; color:153F6A; }\
         #spam::hover{background-color: #245B96; color:#fff;}"
    );

    connect(spamBtn, &QPushButton::clicked, this, [=]() {

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Confirmation", "Are You Sure about Spamming this News?", QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            // User clicked 'Yes', do something here
            tool->news[id].spam++;
            spam.insert(id);

            QMessageBox::information(this, "OK", "so, this News Will not appears to you again.");
            backTomain();
        }

    });


    // back btn
    QPushButton* back = new QPushButton("Back", insideNews);
    back->setFixedSize(244, 55);
    back->move(40, size().height() - 100);
    back->setStyleSheet(
        "QPushButton{\
            font-size:26px;\
            font-family:Inter;\
            border-radius: 25px;\
            background-color: #D9D9D9;\
         }\
           \
         QPushButton::hover{\
            background-color: #245B96;\
            color:#fff;\
        }"
    );

    connect(back, &QPushButton::clicked, this, &UserWidget::backTomain);
    insideNews->show();
}

void UserWidget::backTomain() {

    insideNews->hide();
    if (displayByCat->isEnabled()) displayByCategory();
    else printDis();
};

void UserWidget::saveAndClose() {

    for (auto id : spam) {
        tool->users[usernameSTD].spam.insert(id);
    }

    for (auto cat : prefrenceCategory) {
        tool->users[usernameSTD].prefrenceCategory.insert(cat);
    }

    parent->setWindowTitle("Login");
    this->close();
}

void UserWidget::printNews(NewsArticle article) {
   
    if (contain(spam, article.id)) return;

    QGroupBox* newsBox = new QGroupBox();
    QGridLayout* newsBoxLayout = new QGridLayout(newsBox);

    newsBox->setObjectName("newsBox");
    newsBox->setStyleSheet("#newsBox{ background-color: #1B4775; border-radius: 20px;}");
    newsBox->setFixedWidth(1035 - 70);
    newsBox->setFixedHeight(270);
    
    // prop
    QLabel* newstitle = new QLabel(this);
    newstitle->setObjectName("titleout");
    newstitle->setStyleSheet("#titleout{font-size:50px; color:#fff;}");

    if (article.title.length() > 116 + 2) {
        article.title = article.title.substr(0, 116 + 6) + "...";
    }

    newstitle->setText(article.title.c_str());
    newstitle->setMaximumHeight(200);
    newstitle->setWordWrap(1);
    newsBoxLayout->addWidget(newstitle, 0, 0, 8, 7);


    string newsPropStr = "Author: "   + article.author      + " - " +
                         "Date: "     + article.date        + " - " + 
                         "Rate: "     + article.printRate() + " - " +
                         "Category: " + article.category    + " - " + 
                         "Spam: "     + to_string(article.spam);

    // prop
    QLabel* newsProp = new QLabel(this);
    newsProp->setObjectName("newsProp");
    newsProp->setStyleSheet("#newsProp{color:#fff; font-size: 15px; height:50px; }");
    newsProp->setText(((std::string)newsPropStr).c_str());
    newsBoxLayout->addWidget(newsProp, 9, 0, 1, 6);


    QPushButton* readBtn = new QPushButton("read", this);
    readBtn->setObjectName("readBtn");
    readBtn->setFixedSize(90, 35);
    readBtn->setStyleSheet(

        "#readBtn {\
            padding:5px;\
            font-size:18px;\
            font-family:Inter;\
            border-radius: 10px;\
            background-color: #D9D9D9;\
            padding:10px;color:153F6A;\
        }"\
        \
        "#readBtn::hover{\
            background-color: #245B96;\
            color:#fff;\
        }"
    );
    newsBoxLayout->addWidget(readBtn, 10, 6, 1, 1);
    
    connect(readBtn, &QPushButton::clicked, this, [=]() {
        UserWidget::makeInsideNews(article.id);
      }
    );

    scrollLayout->setSpacing(10);
    scrollLayout->addWidget(newsBox);
}

void UserWidget::printAllNews() {

    clearWid();

    for (auto art :tool->news) {
        printNews(art.second);
    }
}

bool UserWidget::contain(set<int>ids, int id) {

    for (auto idd : ids) {
        if (id == idd) return true;
    }
    return false;
}

void UserWidget::clearWid() {

    // Remove all the child widgets from the scroll layout
    QLayoutItem* child;
    while ((child = UserWidget::scrollLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }
}

void UserWidget::displayByCategory() {

    clearWid();
    if (displayByCat->currentIndex() == 0) {
        printLatest();
        return;
    }
    vector<int> ids = tool->categorys[ displayByCat->currentText().toUtf8().constData() ];
    for (int id : ids) {
        printNews(tool->news[id]);
    }
}

void UserWidget::printLatest() {

    clearWid();
    stack<int> lastestNews = tool->getIdsStack(tool->ids);
    while (!lastestNews.empty()){
        printNews(tool->news[lastestNews.top()]);
        lastestNews.pop();
    }
}

void UserWidget::printDis() {
    // Create multiple QGroupBox for the frames based on the new selection
    // 
    // Show news based on latest
    if (displayBy->currentIndex() == 0) {
        clearWid();
        displayByCat->setDisabled(true);
        printLatest();
    }

    // Show news based on preferences
    else if (displayBy->currentIndex() == 1) {
        clearWid();
        displayByCat->setDisabled(true);
        vector<int> ids = tool->display_by_preferance(
            prefrenceCategory, 
            tool->categorys,
            tool->news,
           *tool);

        for (int id : ids) {
            printNews(tool->news[id]);
        }
    }

    // Show news based on category
    else if (displayBy->currentIndex() == 2) {
        displayByCat->setDisabled(false);
    }

    // Show news based on highest rate
    else if (displayBy->currentIndex() == 3) {
        clearWid();
        displayByCat->setDisabled(true);
        
        vector<int> ids = tool->getSortedIds_byRate(tool->news);

        for (auto id : ids){
            printNews(tool->news[id]);
        }
    }

    // Update the layout
    mainGroup->update();
}

UserWidget::~UserWidget()
{
    delete ui;
}
