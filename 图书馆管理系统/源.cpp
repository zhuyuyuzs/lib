#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <ctime>  
#include <cstdlib> 


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
struct BorrowRecord {
    string item_id;       // 物品编号
    string item_type;     // 物品类型（图书或光盘）
    time_t borrow_time;   // 借阅时间
    time_t return_time;   // 归还时间
    bool is_returned;     // 是否归还
};

struct User {
    string username;
    string password;
    vector<BorrowRecord> borrowed_items;  // 用户的借阅记录
};


vector<Book> books;
vector<DVD> dvds;
vector<User> users;
User current_user;
// 当前登录的用户

void borrow_item() {
    if (current_user.username.empty()) {
        cout << "请先登录！" << endl;
        return;
    }

    int type;
    cout << "请输入物品类别 (1. 图书 2. 光盘): ";
    cin >> type;
    cin.ignore();  // 忽略输入的换行符

    if (type == 1) {  // 借阅图书
        string id;
        cout << "请输入图书编号: ";
        getline(cin, id);

        // 检查图书是否存在且未被借出
        auto it = find_if(books.begin(), books.end(), [&](const Book& b) { return b.id == id; });
        if (it != books.end()) {
            // 检查该用户是否已经借阅此图书
            auto borrow_it = find_if(current_user.borrowed_items.begin(), current_user.borrowed_items.end(),
                [&](const BorrowRecord& record) { return record.item_id == id; });
            if (borrow_it != current_user.borrowed_items.end()) {
                cout << "您已经借阅了此图书！" << endl;
                return;
            }

            // 借阅操作
            BorrowRecord record;
            record.item_id = id;
            record.item_type = "图书";
            record.borrow_time = time(0);  // 当前时间
            // 设置预计归还时间，假设借阅期限为30天
            record.return_time = record.borrow_time + 30 * 24 * 3600;
            record.is_returned = false;

            current_user.borrowed_items.push_back(record);
            cout << "图书借阅成功！请在30天内归还。" << endl;

        }
        else {
            cout << "图书编号未找到！" << endl;
        }

    }
    else if (type == 2) {  // 借阅光盘
        string id;
        cout << "请输入光盘编号: ";
        getline(cin, id);

        // 检查光盘是否存在且未被借出
        auto it = find_if(dvds.begin(), dvds.end(), [&](const DVD& d) { return d.id == id; });
        if (it != dvds.end()) {
            // 检查该用户是否已经借阅此光盘
            auto borrow_it = find_if(current_user.borrowed_items.begin(), current_user.borrowed_items.end(),
                [&](const BorrowRecord& record) { return record.item_id == id; });
            if (borrow_it != current_user.borrowed_items.end()) {
                cout << "您已经借阅了此光盘！" << endl;
                return;
            }

            // 借阅操作
            BorrowRecord record;
            record.item_id = id;
            record.item_type = "光盘";
            record.borrow_time = time(0);  // 当前时间
            // 设置预计归还时间，假设借阅期限为30天
            record.return_time = record.borrow_time + 30 * 24 * 3600;
            record.is_returned = false;

            current_user.borrowed_items.push_back(record);
            cout << "光盘借阅成功！请在30天内归还。" << endl;

        }
        else {
            cout << "光盘编号未找到！" << endl;
        }
    }
}

void display_borrowed_items() {
    if (current_user.username.empty()) {
        cout << "请先登录！" << endl;
        return;
    }

    if (current_user.borrowed_items.empty()) {
        cout << "您尚未借阅任何物品！" << endl;
        return;
    }

    cout << "=== 您的借阅记录 ===" << endl;
    for (const auto& record : current_user.borrowed_items) {
        string item_name;
        if (record.item_type == "图书") {
            auto it = find_if(books.begin(), books.end(), [&](const Book& b) { return b.id == record.item_id; });
            if (it != books.end()) {
                item_name = it->title;
            }
        }
        else if (record.item_type == "光盘") {
            auto it = find_if(dvds.begin(), dvds.end(), [&](const DVD& d) { return d.id == record.item_id; });
            if (it != dvds.end()) {
                item_name = it->title;
            }
        }

        // 显示借阅信息
        char buffer[80];
        struct tm* time_info;
        time_info = localtime(&record.borrow_time);
        strftime(buffer, 80, "%Y-%m-%d", time_info);
        string borrow_time_str(buffer);

        time_info = localtime(&record.return_time);
        strftime(buffer, 80, "%Y-%m-%d", time_info);
        string return_time_str(buffer);

        cout << "物品: " << item_name << " | 借出时间: " << borrow_time_str
            << " | 预计归还时间: " << return_time_str
            << " | " << (record.is_returned ? "已归还" : "尚未归还") << endl;
    }
}

void return_item() {
    if (current_user.username.empty()) {
        cout << "请先登录！" << endl;
        return;
    }

    string id;
    cout << "请输入要归还的物品编号: ";
    getline(cin, id);

    auto it = find_if(current_user.borrowed_items.begin(), current_user.borrowed_items.end(),
        [&](const BorrowRecord& record) { return record.item_id == id && !record.is_returned; });
    if (it != current_user.borrowed_items.end()) {
        // 物品归还
        it->is_returned = true;
        cout << "物品已成功归还！" << endl;
    }
    else {
        cout << "您没有借阅此物品，或此物品已归还！" << endl;
    }
}


// 统一读取数据
void load_data(const string& filename) {
    ifstream file(filename);
    string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            stringstream ss(line);
            string type;
            getline(ss, type, '|');
            // 读取物品类型

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
                ss.ignore(1, '|');
                // 跳过分隔符
                ss >> dvd.duration;
                dvds.push_back(dvd);
            }
        }
        file.close();
    }
}


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


void load_user_data(const string& filename) {
    ifstream file(filename);
    string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            stringstream ss(line);
            User user;
            getline(ss, user.username, '|');
            getline(ss, user.password, '|');
            users.push_back(user);
        }
        file.close();
    }
}


void save_user_data(const string& filename) {
    ofstream file(filename);

    if (file.is_open()) {
        for (const auto& user : users) {
            file << user.username << "|" << user.password << endl;
        }
        file.close();
    }
}


void register_user() {
    User new_user;
    cout << "请输入用户名: ";
    cin >> new_user.username;

    // 检查用户名是否已存在
    for (const auto& user : users) {
        if (user.username == new_user.username) {
            cout << "错误：用户名已存在！" << endl;
            return;
        }
    }

    cout << "请输入密码: ";
    cin >> new_user.password;

    users.push_back(new_user);
    save_user_data("users.txt");
    cout << "注册成功！" << endl;

}


bool login_user() {
    string username, password;
    cout << "请输入用户名: ";
    cin >> username;
    cout << "请输入密码: ";
    cin >> password;

    for (const auto& user : users) {
        if (user.username == username && user.password == password) {
            current_user = user;
            cout << "登录成功！" << endl;
            return true;
        }
    }

    cout << "用户名或密码错误！" << endl;
    return false;
}


void add_item() {
    if (current_user.username.empty()) {
        cout << "请先登录！" << endl;
        return;
    }

    int type;
    cout << "请输入物品类别 (1. 图书 2. 光盘): ";
    cin >> type;
    cin.ignore();
    // Ignore newline after the number

    if (type == 1) {
        // 图书
        Book book;
        cout << "请输入物品编号: ";
        getline(cin, book.id);

        // 检测编号是否重复
        for (const auto& b : books) {
            if (b.id == book.id) {
                cout << "错误：编号 " << book.id << " 已存在，无法重复录入！" << endl;
                return;
            }
        }

        cout << "请输入物品标题: ";
        getline(cin, book.title);

        // 检测标题是否重复
        for (const auto& b : books) {
            if (b.title == book.title) {
                cout << "错误：标题 \"" << book.title << "\" 已存在，无法重复录入！" << endl;
                return;
            }
        }

        cout << "请输入物品作者: ";
        getline(cin, book.author);
        cout << "请输入出版社: ";
        getline(cin, book.publisher);
        cout << "请输入ISBN: ";
        getline(cin, book.isbn);
        cout << "请输入页数: ";
        cin >> book.pages;
        books.push_back(book);

        save_data("items.txt");
        cout << "图书添加成功！" << endl;
    }
    else if (type == 2) {  // 光盘
        DVD dvd;
        cout << "请输入物品编号: ";
        getline(cin, dvd.id);

        // 检测编号是否重复
        for (const auto& d : dvds) {
            if (d.id == dvd.id) {
                cout << "错误：编号 " << dvd.id << " 已存在，无法重复录入！" << endl;
                return;
            }
        }

        cout << "请输入物品标题: ";
        getline(cin, dvd.title);

        // 检测标题是否重复
        for (const auto& d : dvds) {
            if (d.title == dvd.title) {
                cout << "错误：标题 \"" << dvd.title << "\" 已存在，无法重复录入！" << endl;
                return;
            }
        }

        cout << "请输入物品作者: ";
        getline(cin, dvd.author);
        cout << "请输入出品者: ";
        getline(cin, dvd.producer);
        cout << "请输入出品年份: ";
        cin >> dvd.year;
        cout << "请输入视频时长（分钟）: ";
        cin >> dvd.duration;
        dvds.push_back(dvd);

        save_data("items.txt");
        cout << "光盘添加成功！" << endl;
    }
}


void display_items() {
    if (books.empty() && dvds.empty()) {
        cout << "物品库为空！" << endl;
        return;
    }

    // 统计当前库存数量
    cout << "当前库存情况：" << endl;
    cout << "图书数量: " << books.size() << " 本" << endl;
    cout << "光盘数量: " << dvds.size() << " 个" << endl;
    cout << endl;

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
    if (current_user.username.empty()) {
        cout << "请先登录！" << endl;
        return;
    }

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
            string new_pages;
            getline(cin, new_pages);
            if (!new_pages.empty()) {
                book.pages = stoi(new_pages);
            }

            found = true;
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
                string new_year;
                getline(cin, new_year);
                if (!new_year.empty()) {
                    dvd.year = stoi(new_year);
                }

                cout << "当前视频时长: " << dvd.duration << ", 输入新视频时长 (留空则不修改): ";
                string new_duration;
                getline(cin, new_duration);
                if (!new_duration.empty()) {
                    dvd.duration = stoi(new_duration);
                }

                found = true;
                break;
            }
        }
    }

    if (!found) {
        cout << "物品编号未找到！" << endl;
    }
    else {
        save_data("items.txt");
        cout << "物品信息编辑成功！" << endl;
    }


}


void delete_item() {
    string id;
    cout << "请输入要删除的物品编号: ";
    getline(cin, id);
    // 获取用户输入的物品编号

    bool found = false;

    // 删除图书
    for (auto it = books.begin(); it != books.end(); ++it) {
        if (it->id == id) {
            books.erase(it);
            // 删除该图书
            found = true;
            cout << "图书编号 " << id << " 已删除！" << endl;
            break;
        }
    }

    // 如果没有删除图书，则继续删除光盘
    if (!found) {
        for (auto it = dvds.begin(); it != dvds.end(); ++it) {
            if (it->id == id) {
                dvds.erase(it);
                // 删除该光盘
                found = true;
                cout << "光盘编号 " << id << " 已删除！" << endl;
                break;
            }
        }
    }

    if (!found) {
        cout << "未找到该编号的物品！" << endl;
    }
    else {
        save_data("items.txt");
    }


}

void logout_user() {
    if (current_user.username.empty()) {
        cout << "当前没有用户登录。" << endl;
        return;
    }
    current_user = User();  // 清空当前用户信息
    cout << "登出成功！" << endl;
}

void save_and_exit() {
    save_data("media_data.txt");
    save_user_data("users.txt");
    cout << "数据已保存，程序即将退出。" << endl;
    exit(0);
    // 退出程序
}

void main_menu() {
    load_data("media_data.txt");
    load_user_data("users.txt");

    int choice;
    while (true) {
        cout << "=== 欢迎使用物品管理系统 ===" << endl;

        if (current_user.username.empty()) {
            cout << "1. 注册" << endl;
            cout << "2. 登录" << endl;
        }
        else {
            cout << "欢迎，" << current_user.username << "!" << endl;
            cout << "3. 查阅物品" << endl;
            cout << "4. 添加物品" << endl;
            cout << "5. 编辑物品" << endl;
            cout << "6. 删除物品" << endl;
            cout << "7. 注销" << endl;
            cout << "8. 借阅物品" << endl;
            cout << "9. 显示借阅记录" << endl;
            cout << "10. 归还物品" << endl;
        }
        cout << "请输入操作: ";
        cin >> choice;
        cin.ignore(); // 忽略换行符

        switch (choice) {
        case 1:
            register_user();
            break;
        case 2:
            login_user();
            break;
        case 3:
            display_items();
            break;
        case 4:
            add_item();
            break;
        case 5:
            edit_item();
            break;
        case 6:
            delete_item();
            break;
        case 7:
            logout_user();
            break;
        case 8:
            borrow_item();
            break;
        case 9:
            display_borrowed_items();
            break;
        case 10:
            return_item();
            break;
        default:
            cout << "无效的选择，请重新输入。" << endl;
            break;
        }
    }
}


int main() {
    cout << "===================================" << endl;
    cout << "程序启动... " << endl;


    // 调用主菜单函数
    main_menu();

    cout << "===================================" << endl;
    cout << "程序已退出。" << endl;
    return 0;
}
