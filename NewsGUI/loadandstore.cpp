
#include "loadandstore.h"
#include<iostream>
using namespace std;

loadAndStoreFiles::loadAndStoreFiles() {};

void loadAndStoreFiles::saveAndClose(

    unordered_map<string, userData > users, 
    unordered_map<int, NewsArticle> news) {

    saveNews(news);
    saveUsers(users);
}

void loadAndStoreFiles::loadUsers() {
    ifstream file{ users_path };

    // this mean when file isnt open so the file path is invalid,
    // or anoter program run it.  
    if (!file.is_open()) {
        cerr << "can't open this file, try handle the file path\n";
    }

    else {

        // make data vector to hold {name, pass, role}
        // please remember their index
        vector<string> data;
        // to avoid take header with data.
        bool hdrFlag = 1;

        // read lines from file.
        for (string line; getline(file, line);) {

            if (hdrFlag) {
                hdrFlag = 0;
                continue;
            }

            // make line more functional
            istringstream row(line);

            // iterate over values in row sperated with ','
            // to add to <data>.
            for (string val; getline(row, val, ',');) {

                data.push_back(val);
            }
            // i told to dont forget thier index before.
            users[data[0]] = { data[0] ,data[1], data[2], getSpamVec(data[3]),getCatPreVec(data[4]) };

            // we must clear <data> to holed anoter 
            // user's data in next iteration
            data = {};
        }
    }

    // you must colse the file.
    file.close();
    cout << "load users file done\n";

}

void loadAndStoreFiles::loadNews() {

    ifstream file{ news_path };

    if (!file.is_open()) {
        cout << "can't open this file, try handle the file path\n";
    }
    else {

        vector<string> data;
        bool hdrFlag = 1;
        int idx = 0;
        int crrId;

        for (string line; getline(file, line);) {

            if (hdrFlag) {
                hdrFlag = 0;
                continue;
            };

            istringstream row(line);

            for (string val; getline(row, val, ',');) {

                data.push_back(val);
            }
            crrId = stoi(data[0]);
            news[crrId] = { crrId,      // id 
                            data[1],    // cat 
                            data[2],    // title
                            data[3],    // author
                            data[4],    // content
                            data[5],    // date
                 getRateVec(data[6]),
              addCommentVec(data[7]),
                       stoi(data[8]) };

            categorys[data[1]].push_back(crrId);
            ids.push_back(crrId);

            data = {};
        }
    }
    file.close();
    cout << "load news file done\n";
}


void loadAndStoreFiles::saveUsers(unordered_map<string, userData > users) {

    fstream file;
    file.open(users_path, ios::out);

    cout << "inside user\n";
    // add file header.
    file << "name,password,role,spam,Prefrence\n";

    for (auto user : users)
    {
        if (user.second.username == "") continue;

        file << user.first << ','
            << user.second.pass << ','
            << user.second.role << ','
            << user.second.getSpamStr() << ','
            << user.second.getCatStr()
            << "\n";
    }

    // we must colse it.
    file.close();

    cout << "save users file done\n";
}

void loadAndStoreFiles::saveNews(unordered_map<int, NewsArticle> news) {

    // Open the CSV file in append mode
    ofstream file;
    file.open(news_path, ios::out);
    file << "id,category,title,author,content,date,rate,comment,spam\n";

    for (auto curNews : news) {

        if (curNews.second.title == "") continue;

        file << curNews.first << "," <<
            curNews.second.category << "," <<
            curNews.second.title << "," <<
            curNews.second.author << "," <<
            curNews.second.description << "," <<
            curNews.second.date << "," <<
            curNews.second.getRateStr() << "," <<
            curNews.second.getCommStr() << "," <<
            curNews.second.spam << "\n";

    }
    // Close the file
    file.close();
}


void loadAndStoreFiles::removeNewsArticle(

    int id,
    unordered_map<int, NewsArticle>& news,
    vector<int>& ids,
    unordered_map<string, vector<int>>& categorys)
{
    /*
      Function: removeNewsArticle

      Description:
          Removes the news article with the given ID from the system.
          The news article is removed from the map called news, where the ID is used as the key.

      Parameters:
          id (int) - The ID of the news article to be removed.

      Returns:
          void
    */

    string tempCat = news[id].category;

    categorys[tempCat].erase(
        remove(categorys[tempCat].begin(),
            categorys[tempCat].end(),
            id),
        categorys[tempCat].end());

    ids.erase(
        remove(ids.begin(),
            ids.end(),
            id),
        ids.end()
    );
    news.erase(id);
}


vector<float> loadAndStoreFiles::getRateVec(string rateStr) {

    istringstream rowRate(rateStr);
    vector<float> rates;
    for (string val; getline(rowRate, val, '*');) {
        rates.push_back(stof(val));
    }
    return rates;
}

set<int> loadAndStoreFiles::getSpamVec(string str) {
    if (str.length() == 1) return { 0 };
    set<int> spams;

    istringstream rowRate(str);
    for (string val; getline(rowRate, val, '*');) {
        spams.insert(stoi(val));
    }
    return spams;
}

set<string> loadAndStoreFiles::getCatPreVec(string str)
{
    set<string> prefcat;
    istringstream rowcat(str);
    for (string val; getline(rowcat, val, '?');) {
        prefcat.insert(val);
    }
    return prefcat;
}


vector<vector<string>> loadAndStoreFiles::addCommentVec(string comment) {

    istringstream userAndCom(comment);
    vector<vector<string>> comments;

    vector<string> data;

    for (string val; getline(userAndCom, val, '+');) {

        istringstream raw(val);

        for (string val2; getline(raw, val2, '#');) {
            data.push_back(val2);
        }

        comments.push_back(data);
        data.clear();
    }
    return comments;
}

stack<int> loadAndStoreFiles::getIdsStack(vector<int> ids) {

    stack<int> ids_stack;

    for (auto id : ids)
        ids_stack.push(id);

    return ids_stack;
}

vector<int> loadAndStoreFiles::getSortedIds_byRate(unordered_map<int, NewsArticle> news)
{
    vector<int> tempvec = {};
    sortedLinkeList list;

    for (auto crNews : news) {

        Node* temp = new Node(crNews.second.id, crNews.second.getRate());
        list.insert(temp);
    }

    Node* temp = list.head;

    while (temp != NULL)
    {
        tempvec.push_back(temp->id);
        temp = temp->next;
    }

    return tempvec;
}

vector<int> loadAndStoreFiles::display_by_preferance(
    set<string> prefrenceCategory,
    unordered_map<string, vector<int>>& categorys
    , unordered_map<int, NewsArticle>& news, 
    loadAndStoreFiles tool)
{
    random_device rd;
    mt19937 g(rd());
    vector<int> randomized_ids;

    for (auto cat : prefrenceCategory) {
        for (auto ids : categorys[cat]) {
            randomized_ids.push_back(ids);
        }
    }
    shuffle(randomized_ids.begin(), randomized_ids.end(), g);
    return randomized_ids;
}
