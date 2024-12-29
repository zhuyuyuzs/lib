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
    string item_id;       // ��Ʒ���
    string item_type;     // ��Ʒ���ͣ�ͼ�����̣�
    time_t borrow_time;   // ����ʱ��
    time_t return_time;   // �黹ʱ��
    bool is_returned;     // �Ƿ�黹
};

struct User {
    string username;
    string password;
    vector<BorrowRecord> borrowed_items;  // �û��Ľ��ļ�¼
};


vector<Book> books;
vector<DVD> dvds;
vector<User> users;
User current_user;
// ��ǰ��¼���û�

void borrow_item() {
    if (current_user.username.empty()) {
        cout << "���ȵ�¼��" << endl;
        return;
    }

    int type;
    cout << "��������Ʒ��� (1. ͼ�� 2. ����): ";
    cin >> type;
    cin.ignore();  // ��������Ļ��з�

    if (type == 1) {  // ����ͼ��
        string id;
        cout << "������ͼ����: ";
        getline(cin, id);

        // ���ͼ���Ƿ������δ�����
        auto it = find_if(books.begin(), books.end(), [&](const Book& b) { return b.id == id; });
        if (it != books.end()) {
            // �����û��Ƿ��Ѿ����Ĵ�ͼ��
            auto borrow_it = find_if(current_user.borrowed_items.begin(), current_user.borrowed_items.end(),
                [&](const BorrowRecord& record) { return record.item_id == id; });
            if (borrow_it != current_user.borrowed_items.end()) {
                cout << "���Ѿ������˴�ͼ�飡" << endl;
                return;
            }

            // ���Ĳ���
            BorrowRecord record;
            record.item_id = id;
            record.item_type = "ͼ��";
            record.borrow_time = time(0);  // ��ǰʱ��
            // ����Ԥ�ƹ黹ʱ�䣬�����������Ϊ30��
            record.return_time = record.borrow_time + 30 * 24 * 3600;
            record.is_returned = false;

            current_user.borrowed_items.push_back(record);
            cout << "ͼ����ĳɹ�������30���ڹ黹��" << endl;

        }
        else {
            cout << "ͼ����δ�ҵ���" << endl;
        }

    }
    else if (type == 2) {  // ���Ĺ���
        string id;
        cout << "��������̱��: ";
        getline(cin, id);

        // �������Ƿ������δ�����
        auto it = find_if(dvds.begin(), dvds.end(), [&](const DVD& d) { return d.id == id; });
        if (it != dvds.end()) {
            // �����û��Ƿ��Ѿ����Ĵ˹���
            auto borrow_it = find_if(current_user.borrowed_items.begin(), current_user.borrowed_items.end(),
                [&](const BorrowRecord& record) { return record.item_id == id; });
            if (borrow_it != current_user.borrowed_items.end()) {
                cout << "���Ѿ������˴˹��̣�" << endl;
                return;
            }

            // ���Ĳ���
            BorrowRecord record;
            record.item_id = id;
            record.item_type = "����";
            record.borrow_time = time(0);  // ��ǰʱ��
            // ����Ԥ�ƹ黹ʱ�䣬�����������Ϊ30��
            record.return_time = record.borrow_time + 30 * 24 * 3600;
            record.is_returned = false;

            current_user.borrowed_items.push_back(record);
            cout << "���̽��ĳɹ�������30���ڹ黹��" << endl;

        }
        else {
            cout << "���̱��δ�ҵ���" << endl;
        }
    }
}

void display_borrowed_items() {
    if (current_user.username.empty()) {
        cout << "���ȵ�¼��" << endl;
        return;
    }

    if (current_user.borrowed_items.empty()) {
        cout << "����δ�����κ���Ʒ��" << endl;
        return;
    }

    cout << "=== ���Ľ��ļ�¼ ===" << endl;
    for (const auto& record : current_user.borrowed_items) {
        string item_name;
        if (record.item_type == "ͼ��") {
            auto it = find_if(books.begin(), books.end(), [&](const Book& b) { return b.id == record.item_id; });
            if (it != books.end()) {
                item_name = it->title;
            }
        }
        else if (record.item_type == "����") {
            auto it = find_if(dvds.begin(), dvds.end(), [&](const DVD& d) { return d.id == record.item_id; });
            if (it != dvds.end()) {
                item_name = it->title;
            }
        }

        // ��ʾ������Ϣ
        char buffer[80];
        struct tm* time_info;
        time_info = localtime(&record.borrow_time);
        strftime(buffer, 80, "%Y-%m-%d", time_info);
        string borrow_time_str(buffer);

        time_info = localtime(&record.return_time);
        strftime(buffer, 80, "%Y-%m-%d", time_info);
        string return_time_str(buffer);

        cout << "��Ʒ: " << item_name << " | ���ʱ��: " << borrow_time_str
            << " | Ԥ�ƹ黹ʱ��: " << return_time_str
            << " | " << (record.is_returned ? "�ѹ黹" : "��δ�黹") << endl;
    }
}

void return_item() {
    if (current_user.username.empty()) {
        cout << "���ȵ�¼��" << endl;
        return;
    }

    string id;
    cout << "������Ҫ�黹����Ʒ���: ";
    getline(cin, id);

    auto it = find_if(current_user.borrowed_items.begin(), current_user.borrowed_items.end(),
        [&](const BorrowRecord& record) { return record.item_id == id && !record.is_returned; });
    if (it != current_user.borrowed_items.end()) {
        // ��Ʒ�黹
        it->is_returned = true;
        cout << "��Ʒ�ѳɹ��黹��" << endl;
    }
    else {
        cout << "��û�н��Ĵ���Ʒ�������Ʒ�ѹ黹��" << endl;
    }
}


// ͳһ��ȡ����
void load_data(const string& filename) {
    ifstream file(filename);
    string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            stringstream ss(line);
            string type;
            getline(ss, type, '|');
            // ��ȡ��Ʒ����

            if (type == "ͼ��") {
                Book book;
                getline(ss, book.id, '|');
                getline(ss, book.title, '|');
                getline(ss, book.author, '|');
                getline(ss, book.publisher, '|');
                getline(ss, book.isbn, '|');
                ss >> book.pages;
                books.push_back(book);
            }
            else if (type == "����") {
                DVD dvd;
                getline(ss, dvd.id, '|');
                getline(ss, dvd.title, '|');
                getline(ss, dvd.author, '|');
                getline(ss, dvd.producer, '|');
                ss >> dvd.year;
                ss.ignore(1, '|');
                // �����ָ���
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
        // ����ͼ�����ݣ�����ԭ��ʽ�������
        for (const auto& book : books) {
            file << "ͼ��|" << book.id << "|" << book.title << "|" << book.author
                << "|" << book.publisher << "|" << book.isbn << "|" << book.pages << endl;
        }

        // ����������ݣ�����ԭ��ʽ�������
        for (const auto& dvd : dvds) {
            file << "����|" << dvd.id << "|" << dvd.title << "|" << dvd.author
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
    cout << "�������û���: ";
    cin >> new_user.username;

    // ����û����Ƿ��Ѵ���
    for (const auto& user : users) {
        if (user.username == new_user.username) {
            cout << "�����û����Ѵ��ڣ�" << endl;
            return;
        }
    }

    cout << "����������: ";
    cin >> new_user.password;

    users.push_back(new_user);
    save_user_data("users.txt");
    cout << "ע��ɹ���" << endl;

}


bool login_user() {
    string username, password;
    cout << "�������û���: ";
    cin >> username;
    cout << "����������: ";
    cin >> password;

    for (const auto& user : users) {
        if (user.username == username && user.password == password) {
            current_user = user;
            cout << "��¼�ɹ���" << endl;
            return true;
        }
    }

    cout << "�û������������" << endl;
    return false;
}


void add_item() {
    if (current_user.username.empty()) {
        cout << "���ȵ�¼��" << endl;
        return;
    }

    int type;
    cout << "��������Ʒ��� (1. ͼ�� 2. ����): ";
    cin >> type;
    cin.ignore();
    // Ignore newline after the number

    if (type == 1) {
        // ͼ��
        Book book;
        cout << "��������Ʒ���: ";
        getline(cin, book.id);

        // ������Ƿ��ظ�
        for (const auto& b : books) {
            if (b.id == book.id) {
                cout << "���󣺱�� " << book.id << " �Ѵ��ڣ��޷��ظ�¼�룡" << endl;
                return;
            }
        }

        cout << "��������Ʒ����: ";
        getline(cin, book.title);

        // �������Ƿ��ظ�
        for (const auto& b : books) {
            if (b.title == book.title) {
                cout << "���󣺱��� \"" << book.title << "\" �Ѵ��ڣ��޷��ظ�¼�룡" << endl;
                return;
            }
        }

        cout << "��������Ʒ����: ";
        getline(cin, book.author);
        cout << "�����������: ";
        getline(cin, book.publisher);
        cout << "������ISBN: ";
        getline(cin, book.isbn);
        cout << "������ҳ��: ";
        cin >> book.pages;
        books.push_back(book);

        save_data("items.txt");
        cout << "ͼ����ӳɹ���" << endl;
    }
    else if (type == 2) {  // ����
        DVD dvd;
        cout << "��������Ʒ���: ";
        getline(cin, dvd.id);

        // ������Ƿ��ظ�
        for (const auto& d : dvds) {
            if (d.id == dvd.id) {
                cout << "���󣺱�� " << dvd.id << " �Ѵ��ڣ��޷��ظ�¼�룡" << endl;
                return;
            }
        }

        cout << "��������Ʒ����: ";
        getline(cin, dvd.title);

        // �������Ƿ��ظ�
        for (const auto& d : dvds) {
            if (d.title == dvd.title) {
                cout << "���󣺱��� \"" << dvd.title << "\" �Ѵ��ڣ��޷��ظ�¼�룡" << endl;
                return;
            }
        }

        cout << "��������Ʒ����: ";
        getline(cin, dvd.author);
        cout << "�������Ʒ��: ";
        getline(cin, dvd.producer);
        cout << "�������Ʒ���: ";
        cin >> dvd.year;
        cout << "��������Ƶʱ�������ӣ�: ";
        cin >> dvd.duration;
        dvds.push_back(dvd);

        save_data("items.txt");
        cout << "������ӳɹ���" << endl;
    }
}


void display_items() {
    if (books.empty() && dvds.empty()) {
        cout << "��Ʒ��Ϊ�գ�" << endl;
        return;
    }

    // ͳ�Ƶ�ǰ�������
    cout << "��ǰ��������" << endl;
    cout << "ͼ������: " << books.size() << " ��" << endl;
    cout << "��������: " << dvds.size() << " ��" << endl;
    cout << endl;

    cout << "--- ͼ�� ---" << endl;
    for (const auto& book : books) {
        cout << "���: " << book.id << " | ����: " << book.title << " | ����: " << book.author
            << " | ������: " << book.publisher << " | ISBN: " << book.isbn << " | ҳ��: " << book.pages << endl;
    }

    cout << "--- ���� ---" << endl;
    for (const auto& dvd : dvds) {
        cout << "���: " << dvd.id << " | ����: " << dvd.title << " | ����: " << dvd.author
            << " | ��Ʒ��: " << dvd.producer << " | ��Ʒ���: " << dvd.year << " | ��Ƶʱ��: " << dvd.duration << "����" << endl;
    }


}


void edit_item() {
    if (current_user.username.empty()) {
        cout << "���ȵ�¼��" << endl;
        return;
    }

    string id;
    cout << "������Ҫ�༭����Ʒ���: ";
    getline(cin, id);

    bool found = false;
    // �༭ͼ��
    for (auto& book : books) {
        if (book.id == id) {
            cout << "�༭ͼ�� " << book.id << " ��Ϣ��" << endl;
            cout << "��ǰ����: " << book.title << ", �����±��� (�������޸�): ";
            string new_title;
            getline(cin, new_title);
            if (!new_title.empty()) {
                book.title = new_title;
            }

            cout << "��ǰ����: " << book.author << ", ���������� (�������޸�): ";
            string new_author;
            getline(cin, new_author);
            if (!new_author.empty()) {
                book.author = new_author;
            }

            cout << "��ǰ������: " << book.publisher << ", �����³����� (�������޸�): ";
            string new_publisher;
            getline(cin, new_publisher);
            if (!new_publisher.empty()) {
                book.publisher = new_publisher;
            }

            cout << "��ǰISBN: " << book.isbn << ", ������ISBN (�������޸�): ";
            string new_isbn;
            getline(cin, new_isbn);
            if (!new_isbn.empty()) {
                book.isbn = new_isbn;
            }

            cout << "��ǰҳ��: " << book.pages << ", ������ҳ�� (�������޸�): ";
            string new_pages;
            getline(cin, new_pages);
            if (!new_pages.empty()) {
                book.pages = stoi(new_pages);
            }

            found = true;
            break;
        }
    }




    // �༭����
    if (!found) {
        for (auto& dvd : dvds) {
            if (dvd.id == id) {
                cout << "�༭���� " << dvd.id << " ��Ϣ��" << endl;
                cout << "��ǰ����: " << dvd.title << ", �����±��� (�������޸�): ";
                string new_title;
                getline(cin, new_title);
                if (!new_title.empty()) {
                    dvd.title = new_title;
                }

                cout << "��ǰ����: " << dvd.author << ", ���������� (�������޸�): ";
                string new_author;
                getline(cin, new_author);
                if (!new_author.empty()) {
                    dvd.author = new_author;
                }

                cout << "��ǰ��Ʒ��: " << dvd.producer << ", �����³�Ʒ�� (�������޸�): ";
                string new_producer;
                getline(cin, new_producer);
                if (!new_producer.empty()) {
                    dvd.producer = new_producer;
                }

                cout << "��ǰ��Ʒ���: " << dvd.year << ", �����³�Ʒ��� (�������޸�): ";
                string new_year;
                getline(cin, new_year);
                if (!new_year.empty()) {
                    dvd.year = stoi(new_year);
                }

                cout << "��ǰ��Ƶʱ��: " << dvd.duration << ", ��������Ƶʱ�� (�������޸�): ";
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
        cout << "��Ʒ���δ�ҵ���" << endl;
    }
    else {
        save_data("items.txt");
        cout << "��Ʒ��Ϣ�༭�ɹ���" << endl;
    }


}


void delete_item() {
    string id;
    cout << "������Ҫɾ������Ʒ���: ";
    getline(cin, id);
    // ��ȡ�û��������Ʒ���

    bool found = false;

    // ɾ��ͼ��
    for (auto it = books.begin(); it != books.end(); ++it) {
        if (it->id == id) {
            books.erase(it);
            // ɾ����ͼ��
            found = true;
            cout << "ͼ���� " << id << " ��ɾ����" << endl;
            break;
        }
    }

    // ���û��ɾ��ͼ�飬�����ɾ������
    if (!found) {
        for (auto it = dvds.begin(); it != dvds.end(); ++it) {
            if (it->id == id) {
                dvds.erase(it);
                // ɾ���ù���
                found = true;
                cout << "���̱�� " << id << " ��ɾ����" << endl;
                break;
            }
        }
    }

    if (!found) {
        cout << "δ�ҵ��ñ�ŵ���Ʒ��" << endl;
    }
    else {
        save_data("items.txt");
    }


}

void logout_user() {
    if (current_user.username.empty()) {
        cout << "��ǰû���û���¼��" << endl;
        return;
    }
    current_user = User();  // ��յ�ǰ�û���Ϣ
    cout << "�ǳ��ɹ���" << endl;
}

void save_and_exit() {
    save_data("media_data.txt");
    save_user_data("users.txt");
    cout << "�����ѱ��棬���򼴽��˳���" << endl;
    exit(0);
    // �˳�����
}

void main_menu() {
    load_data("media_data.txt");
    load_user_data("users.txt");

    int choice;
    while (true) {
        cout << "=== ��ӭʹ����Ʒ����ϵͳ ===" << endl;

        if (current_user.username.empty()) {
            cout << "1. ע��" << endl;
            cout << "2. ��¼" << endl;
        }
        else {
            cout << "��ӭ��" << current_user.username << "!" << endl;
            cout << "3. ������Ʒ" << endl;
            cout << "4. �����Ʒ" << endl;
            cout << "5. �༭��Ʒ" << endl;
            cout << "6. ɾ����Ʒ" << endl;
            cout << "7. ע��" << endl;
            cout << "8. ������Ʒ" << endl;
            cout << "9. ��ʾ���ļ�¼" << endl;
            cout << "10. �黹��Ʒ" << endl;
        }
        cout << "���������: ";
        cin >> choice;
        cin.ignore(); // ���Ի��з�

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
            cout << "��Ч��ѡ�����������롣" << endl;
            break;
        }
    }
}


int main() {
    cout << "===================================" << endl;
    cout << "��������... " << endl;


    // �������˵�����
    main_menu();

    cout << "===================================" << endl;
    cout << "�������˳���" << endl;
    return 0;
}
