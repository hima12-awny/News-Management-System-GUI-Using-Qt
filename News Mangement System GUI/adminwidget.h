
#ifndef ADMINWIDGET_H
#define ADMINWIDGET_H

#include <QGroupBox>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QWidget>
#include <QVBoxLayout>
#include <QMessageBox>

#include "loadandstore.h"
#include <QString>
#include <iostream>
#include <vector>
#include <unordered_map>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE


class adminWidget : public QWidget
{
    Q_OBJECT

public:

    adminWidget(
        QString             username, 
        loadAndStoreFiles*& tool,
        QWidget *           parent = nullptr);

    ~adminWidget();

    struct guiNews {
        QPushButton* deleteBtn;
        QPushButton* updateBtn;
        QGroupBox*   box;
        NewsArticle  acrticl;
    };

    QString                     username;
    loadAndStoreFiles*          tool;
    unordered_map<int, guiNews> newsGUI;

    QHBoxLayout* mainGroupLayout;
    QScrollArea* contianer;
    QWidget*     scrollWidget;
    QVBoxLayout* scrollLayout;
    QGroupBox*   mainGroup;
    QWidget*     insideAddOrUpdate;

    void printAllNews();
    void printnewsforadmin(NewsArticle article);

    void makeAddOrUpdateFrame(int id);
    void makeAdminReg();

    int generate_id();

private:
    Ui::Widget* ui;
};

#endif // ADMINWIDGET_H
