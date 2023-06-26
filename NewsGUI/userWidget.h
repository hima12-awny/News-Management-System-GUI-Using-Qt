#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QMessageBox>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QLayout>
#include <QScrollArea>
#include <QTextEdit>
#include <QLineEdit>
#include <QInputDialog>

#include <string>
#include "loadandstore.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class UserWidget : public QWidget

{
    Q_OBJECT

public:
    UserWidget(
        QString             user, 
        loadAndStoreFiles*& tool, 
        QWidget*            parent = nullptr);

    ~UserWidget();

    void clearWid();
    void printDis();
    void printNews(NewsArticle acrticl);
    void printAllNews();
    void displayByCategory();

    bool contain(set<int>ids, int id);
    void saveAndClose();
    void makeInsideNews(int id);
    void backTomain();

    void printLatest();

private:
    QWidget* parent;
    Ui::Widget*ui;

    QWidget*     insideNews;
    QWidget*     scrollWidget;

    QPushButton* logout_user;

    QComboBox*   displayBy;
    QComboBox*   displayByCat;

    QScrollArea* contianer;
    QVBoxLayout* scrollLayout;

    QGroupBox*   mainGroup;
    QHBoxLayout* mainGroupLayout;

    QString      username;
    string       usernameSTD;

    set<int>     spam;
    set<string>  prefrenceCategory;

    loadAndStoreFiles* tool;
};

#endif // WIDGET_H