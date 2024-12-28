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

struct User {
    string username;
    string password;
};

vector<Book> books;
vector<DVD> dvds;
vector<User> users;
User current_user;  
// ��ǰ��¼���û�



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
            } else if (type == "����") {
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
    } else if (type == 2) {  // ����
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
    } else {
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
    } else {
        save_data("items.txt");
    }

    
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
        } else {
            cout << "��ӭ��" << current_user.username << "!" << endl;
            cout << "3. ������Ʒ" << endl;
            cout << "4. �����Ʒ" << endl;
            cout << "5. �༭��Ʒ" << endl;
            cout << "6. ɾ����Ʒ" << endl;
            cout << "7. ע��" << endl;
        }
        cout << "8. ���沢�˳�" << endl;

        cout << "��ѡ�����: ";
        cin >> choice;
        cin.ignore();

        if (current_user.username.empty()) {
            if (choice == 1) {
                register_user();
            } else if (choice == 2) {
                if (!login_user()) {
                    continue;
                }
            }
        } else {
            if (choice == 3) {
                display_items();
            } else if (choice == 4) {
                add_item();
            } else if (choice == 5) {
                edit_item();
            } else if (choice == 6) {
                delete_item();
            } else if (choice == 7) {
                current_user.username.clear();
                cout << "ע���ɹ���" << endl;
            } else if (choice == 8) {
                save_and_exit();
            }
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
