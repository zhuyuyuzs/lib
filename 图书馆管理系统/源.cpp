#include"��ͷ.h"
int main() {
    string filename = "media_data.txt";

    // ��ȡ����
    load_data(filename);

    int choice;
    while (true) {
        cout << "--- ͼ�����Ʒ����ϵͳ ---" << endl;
        cout << "��ѡ�������ţ�" << endl;
        cout << "1. �����Ʒ" << endl;
        cout << "2. ��ѯ��Ʒ" << endl;
        cout << "3. ��ʾ��Ʒ��" << endl;
        cout << "4. �༭��Ʒ" << endl;
        cout << "5. ɾ����Ʒ" << endl;
        cout << "6. �˳�" << endl;

        cout << "�����������ţ�1-6����";
        cin >> choice;
        cin.ignore();  // Ignore newline after choice input

        if (choice == 1) {
            add_item();
        }
        else if (choice == 2) {
            query_item();
        }
        else if (choice == 3) {
            display_items();  // ��ʾ��Ʒ��
        }
        else if (choice == 4) {
            edit_item();  // �༭��Ʒ
        }
        else if (choice == 5) {
            delete_item();
        }
        else if (choice == 6) {
            save_data(filename);  // �������ݵ��ļ�
            break;
        }
        else {
            cout << "��Ч��ѡ�����������룡" << endl;
        }
    }

    return 0;
}
