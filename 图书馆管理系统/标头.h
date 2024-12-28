#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct Book {
    string id;
    string title;
    string author;
    string publisher;
    string isbn;
    int pages;
};

struct DVD {
    string id;
    string title;
    string author;
    string producer;
    int year;
    int duration;
};

vector<Book> books;
vector<DVD> dvds;

// 统一读取数据
void load_data(const string& filename) {
    ifstream file(filename);
    string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            stringstream ss(line);
            string type;
            getline(ss, type, '|');  // 读取物品类型

            if (type == "图书") {
                Book book;
                getline(ss, book.id, '|');
                getline(ss, book.title, '|');
                getline(ss, book.author, '|');
                getline(ss, book.publisher, '|');
                getline(ss, book.isbn, '|');
                ss >> book.pages;
                books.push_back(book);
            }
            else if (type == "光盘") {
                DVD dvd;
                getline(ss, dvd.id, '|');
                getline(ss, dvd.title, '|');
                getline(ss, dvd.author, '|');
                getline(ss, dvd.producer, '|');
                ss >> dvd.year;
                ss.ignore(1, '|');  // 跳过分隔符
                ss >> dvd.duration;
                dvds.push_back(dvd);
            }
        }
        file.close();
    }
}

// 统一保存数据
void save_data(const string& filename) {
    ofstream file(filename);

    if (file.is_open()) {
        // 保存图书数据，按照原格式进行输出
        for (const auto& book : books) {
            file << "图书|" << book.id << "|" << book.title << "|" << book.author
                << "|" << book.publisher << "|" << book.isbn << "|" << book.pages << endl;
        }

        // 保存光盘数据，按照原格式进行输出
        for (const auto& dvd : dvds) {
            file << "光盘|" << dvd.id << "|" << dvd.title << "|" << dvd.author
                << "|" << dvd.producer << "|" << dvd.year << "|" << dvd.duration << endl;
        }

        file.close();
    }
}

void add_item() {
    int type;
    cout << "请输入物品类别 (1. 图书 2. 光盘): ";
    cin >> type;
    cin.ignore();  // Ignore newline after the number

    if (type == 1) {  // 图书
        Book book;
        cout << "请输入物品编号: ";
        getline(cin, book.id);
        cout << "请输入物品标题: ";
        getline(cin, book.title);
        cout << "请输入物品作者: ";
        getline(cin, book.author);
        cout << "请输入出版社: ";
        getline(cin, book.publisher);
        cout << "请输入ISBN: ";
        getline(cin, book.isbn);
        cout << "请输入页数: ";
        cin >> book.pages;
        books.push_back(book);
    }
    else if (type == 2) {  // 光盘
        DVD dvd;
        cout << "请输入物品编号: ";
        getline(cin, dvd.id);
        cout << "请输入物品标题: ";
        getline(cin, dvd.title);
        cout << "请输入物品作者: ";
        getline(cin, dvd.author);
        cout << "请输入出品者: ";
        getline(cin, dvd.producer);
        cout << "请输入出品年份: ";
        cin >> dvd.year;
        cout << "请输入视频时长（分钟）: ";
        cin >> dvd.duration;
        dvds.push_back(dvd);
    }
}

void query_item() {
    int choice;
    cout << "查询物品：可以按标题或者类别进行查询。" << endl;
    cout << "输入标题后，系统将返回所有与之匹配的物品信息；输入类别后，系统将返回所有该类别的物品。" << endl;
    cout << "请输入查询类型 (1 或 2): ";
    cin >> choice;
    cin.ignore();  // Ignore newline after the number

    if (choice == 1) {  // 按标题查询
        string title;
        cout << "请输入标题查询: ";
        getline(cin, title);

        bool found = false;
        for (const auto& book : books) {
            if (book.title == title) {
                cout << "图书 | 编号: " << book.id << " | 标题: " << book.title << " | 作者: " << book.author
                    << " | 出版社: " << book.publisher << " | ISBN: " << book.isbn << " | 页数: " << book.pages << endl;
                found = true;
            }
        }

        for (const auto& dvd : dvds) {
            if (dvd.title == title) {
                cout << "光盘 | 编号: " << dvd.id << " | 标题: " << dvd.title << " | 作者: " << dvd.author
                    << " | 出品者: " << dvd.producer << " | 出品年份: " << dvd.year << " | 视频时长: " << dvd.duration << "分钟" << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "该标题不存在！" << endl;
        }

    }
    else if (choice == 2) {  // 按类别查询
        string category;
        cout << "请输入类别查询 (图书 或 光盘): ";
        getline(cin, category);

        bool found = false;
        if (category == "图书") {
            for (const auto& book : books) {
                cout << "图书 | 编号: " << book.id << " | 标题: " << book.title << " | 作者: " << book.author
                    << " | 出版社: " << book.publisher << " | ISBN: " << book.isbn << " | 页数: " << book.pages << endl;
                found = true;
            }
        }
        else if (category == "光盘") {
            for (const auto& dvd : dvds) {
                cout << "光盘 | 编号: " << dvd.id << " | 标题: " << dvd.title << " | 作者: " << dvd.author
                    << " | 出品者: " << dvd.producer << " | 出品年份: " << dvd.year << " | 视频时长: " << dvd.duration << "分钟" << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "该类别没有物品！" << endl;
        }
    }
}

void display_items() {
    if (books.empty() && dvds.empty()) {
        cout << "物品库为空！" << endl;
        return;
    }

    cout << "--- 图书 ---" << endl;
    for (const auto& book : books) {
        cout << "编号: " << book.id << " | 标题: " << book.title << " | 作者: " << book.author
            << " | 出版社: " << book.publisher << " | ISBN: " << book.isbn << " | 页数: " << book.pages << endl;
    }

    cout << "--- 光盘 ---" << endl;
    for (const auto& dvd : dvds) {
        cout << "编号: " << dvd.id << " | 标题: " << dvd.title << " | 作者: " << dvd.author
            << " | 出品者: " << dvd.producer << " | 出品年份: " << dvd.year << " | 视频时长: " << dvd.duration << "分钟" << endl;
    }
}


void edit_item() {
    string id;
    cout << "请输入要编辑的物品编号: ";
    getline(cin, id);

    bool found = false;
    // 编辑图书
    for (auto& book : books) {
        if (book.id == id) {
            cout << "编辑图书 " << book.id << " 信息：" << endl;
            cout << "当前标题: " << book.title << ", 输入新标题 (留空则不修改): ";
            string new_title;
            getline(cin, new_title);
            if (!new_title.empty()) {
                book.title = new_title;
            }

            cout << "当前作者: " << book.author << ", 输入新作者 (留空则不修改): ";
            string new_author;
            getline(cin, new_author);
            if (!new_author.empty()) {
                book.author = new_author;
            }

            cout << "当前出版社: " << book.publisher << ", 输入新出版社 (留空则不修改): ";
            string new_publisher;
            getline(cin, new_publisher);
            if (!new_publisher.empty()) {
                book.publisher = new_publisher;
            }

            cout << "当前ISBN: " << book.isbn << ", 输入新ISBN (留空则不修改): ";
            string new_isbn;
            getline(cin, new_isbn);
            if (!new_isbn.empty()) {
                book.isbn = new_isbn;
            }

            cout << "当前页数: " << book.pages << ", 输入新页数 (留空则不修改): ";
            string new_pages_str;
            getline(cin, new_pages_str);
            if (!new_pages_str.empty()) {
                book.pages = stoi(new_pages_str);
            }

            found = true;
            cout << "图书信息更新成功！" << endl;
            break;
        }
    }

    // 编辑光盘
    if (!found) {
        for (auto& dvd : dvds) {
            if (dvd.id == id) {
                cout << "编辑光盘 " << dvd.id << " 信息：" << endl;
                cout << "当前标题: " << dvd.title << ", 输入新标题 (留空则不修改): ";
                string new_title;
                getline(cin, new_title);
                if (!new_title.empty()) {
                    dvd.title = new_title;
                }

                cout << "当前作者: " << dvd.author << ", 输入新作者 (留空则不修改): ";
                string new_author;
                getline(cin, new_author);
                if (!new_author.empty()) {
                    dvd.author = new_author;
                }

                cout << "当前出品者: " << dvd.producer << ", 输入新出品者 (留空则不修改): ";
                string new_producer;
                getline(cin, new_producer);
                if (!new_producer.empty()) {
                    dvd.producer = new_producer;
                }

                cout << "当前出品年份: " << dvd.year << ", 输入新出品年份 (留空则不修改): ";
                string new_year_str;
                getline(cin, new_year_str);
                if (!new_year_str.empty()) {
                    dvd.year = stoi(new_year_str);
                }

                cout << "当前视频时长: " << dvd.duration << "分钟, 输入新视频时长 (留空则不修改): ";
                string new_duration_str;
                getline(cin, new_duration_str);
                if (!new_duration_str.empty()) {
                    dvd.duration = stoi(new_duration_str);
                }

                found = true;
                cout << "光盘信息更新成功！" << endl;
                break;
            }
        }
    }

    if (!found) {
        cout << "该编号不存在！" << endl;
    }
}


void delete_item() {
    string id;
    cout << "请输入要删除的物品编号: ";
    getline(cin, id);

    bool found = false;
    for (auto it = books.begin(); it != books.end(); ++it) {
        if (it->id == id) {
            books.erase(it);
            found = true;
            break;
        }
    }

    if (!found) {
        for (auto it = dvds.begin(); it != dvds.end(); ++it) {
            if (it->id == id) {
                dvds.erase(it);
                found = true;
                break;
            }
        }
    }

    if (found) {
        cout << "物品删除成功！" << endl;
    }
    else {
        cout << "该编号不存在！" << endl;
    }
}

