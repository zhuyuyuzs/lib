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

// ͳһ��ȡ����
void load_data(const string& filename) {
    ifstream file(filename);
    string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            stringstream ss(line);
            string type;
            getline(ss, type, '|');  // ��ȡ��Ʒ����

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
                ss.ignore(1, '|');  // �����ָ���
                ss >> dvd.duration;
                dvds.push_back(dvd);
            }
        }
        file.close();
    }
}

// ͳһ��������
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

void add_item() {
    int type;
    cout << "��������Ʒ��� (1. ͼ�� 2. ����): ";
    cin >> type;
    cin.ignore();  // Ignore newline after the number

    if (type == 1) {  // ͼ��
        Book book;
        cout << "��������Ʒ���: ";
        getline(cin, book.id);
        cout << "��������Ʒ����: ";
        getline(cin, book.title);
        cout << "��������Ʒ����: ";
        getline(cin, book.author);
        cout << "�����������: ";
        getline(cin, book.publisher);
        cout << "������ISBN: ";
        getline(cin, book.isbn);
        cout << "������ҳ��: ";
        cin >> book.pages;
        books.push_back(book);
    }
    else if (type == 2) {  // ����
        DVD dvd;
        cout << "��������Ʒ���: ";
        getline(cin, dvd.id);
        cout << "��������Ʒ����: ";
        getline(cin, dvd.title);
        cout << "��������Ʒ����: ";
        getline(cin, dvd.author);
        cout << "�������Ʒ��: ";
        getline(cin, dvd.producer);
        cout << "�������Ʒ���: ";
        cin >> dvd.year;
        cout << "��������Ƶʱ�������ӣ�: ";
        cin >> dvd.duration;
        dvds.push_back(dvd);
    }
}

void query_item() {
    int choice;
    cout << "��ѯ��Ʒ�����԰�������������в�ѯ��" << endl;
    cout << "��������ϵͳ������������֮ƥ�����Ʒ��Ϣ����������ϵͳ���������и�������Ʒ��" << endl;
    cout << "�������ѯ���� (1 �� 2): ";
    cin >> choice;
    cin.ignore();  // Ignore newline after the number

    if (choice == 1) {  // �������ѯ
        string title;
        cout << "����������ѯ: ";
        getline(cin, title);

        bool found = false;
        for (const auto& book : books) {
            if (book.title == title) {
                cout << "ͼ�� | ���: " << book.id << " | ����: " << book.title << " | ����: " << book.author
                    << " | ������: " << book.publisher << " | ISBN: " << book.isbn << " | ҳ��: " << book.pages << endl;
                found = true;
            }
        }

        for (const auto& dvd : dvds) {
            if (dvd.title == title) {
                cout << "���� | ���: " << dvd.id << " | ����: " << dvd.title << " | ����: " << dvd.author
                    << " | ��Ʒ��: " << dvd.producer << " | ��Ʒ���: " << dvd.year << " | ��Ƶʱ��: " << dvd.duration << "����" << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "�ñ��ⲻ���ڣ�" << endl;
        }

    }
    else if (choice == 2) {  // ������ѯ
        string category;
        cout << "����������ѯ (ͼ�� �� ����): ";
        getline(cin, category);

        bool found = false;
        if (category == "ͼ��") {
            for (const auto& book : books) {
                cout << "ͼ�� | ���: " << book.id << " | ����: " << book.title << " | ����: " << book.author
                    << " | ������: " << book.publisher << " | ISBN: " << book.isbn << " | ҳ��: " << book.pages << endl;
                found = true;
            }
        }
        else if (category == "����") {
            for (const auto& dvd : dvds) {
                cout << "���� | ���: " << dvd.id << " | ����: " << dvd.title << " | ����: " << dvd.author
                    << " | ��Ʒ��: " << dvd.producer << " | ��Ʒ���: " << dvd.year << " | ��Ƶʱ��: " << dvd.duration << "����" << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "�����û����Ʒ��" << endl;
        }
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
            string new_pages_str;
            getline(cin, new_pages_str);
            if (!new_pages_str.empty()) {
                book.pages = stoi(new_pages_str);
            }

            found = true;
            cout << "ͼ����Ϣ���³ɹ���" << endl;
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
                string new_year_str;
                getline(cin, new_year_str);
                if (!new_year_str.empty()) {
                    dvd.year = stoi(new_year_str);
                }

                cout << "��ǰ��Ƶʱ��: " << dvd.duration << "����, ��������Ƶʱ�� (�������޸�): ";
                string new_duration_str;
                getline(cin, new_duration_str);
                if (!new_duration_str.empty()) {
                    dvd.duration = stoi(new_duration_str);
                }

                found = true;
                cout << "������Ϣ���³ɹ���" << endl;
                break;
            }
        }
    }

    if (!found) {
        cout << "�ñ�Ų����ڣ�" << endl;
    }
}


void delete_item() {
    string id;
    cout << "������Ҫɾ������Ʒ���: ";
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
        cout << "��Ʒɾ���ɹ���" << endl;
    }
    else {
        cout << "�ñ�Ų����ڣ�" << endl;
    }
}

