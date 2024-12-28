#include"标头.h"
int main() {
    string filename = "media_data.txt";

    // 读取数据
    load_data(filename);

    int choice;
    while (true) {
        cout << "--- 图书馆物品管理系统 ---" << endl;
        cout << "请选择操作编号：" << endl;
        cout << "1. 添加物品" << endl;
        cout << "2. 查询物品" << endl;
        cout << "3. 显示物品库" << endl;
        cout << "4. 编辑物品" << endl;
        cout << "5. 删除物品" << endl;
        cout << "6. 退出" << endl;

        cout << "请输入操作编号（1-6）：";
        cin >> choice;
        cin.ignore();  // Ignore newline after choice input

        if (choice == 1) {
            add_item();
        }
        else if (choice == 2) {
            query_item();
        }
        else if (choice == 3) {
            display_items();  // 显示物品库
        }
        else if (choice == 4) {
            edit_item();  // 编辑物品
        }
        else if (choice == 5) {
            delete_item();
        }
        else if (choice == 6) {
            save_data(filename);  // 保存数据到文件
            break;
        }
        else {
            cout << "无效的选择，请重新输入！" << endl;
        }
    }

    return 0;
}
