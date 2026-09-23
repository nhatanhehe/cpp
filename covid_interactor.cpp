#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <set>
#include <cstdlib>

using namespace std;

// Hàm báo lỗi và dừng chương trình nếu thí sinh sai
void die(const string& msg) {
    cerr << "WRONG ANSWER: " << msg << endl;
    exit(1);
}

int main() {
    // Tắt đồng bộ để tránh bị nghẽn buffer, nhưng bắt buộc phải tự flush
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ifstream fin("test.inp");
    if (!fin) {
        cerr << "Loi: Khong tim thay file test.inp de doc dap an an!" << endl;
        return 1;
    }

    int T;
    if (!(fin >> T)) die("File test.inp trong.");

    // Giao tiếp 1: Gửi T cho chương trình của thí sinh
    cout << T << "\n";
    cout.flush();

    for (int t = 1; t <= T; ++t) {
        int num_infected;
        fin >> num_infected;
        set<int> infected;
        for (int i = 0; i < num_infected; ++i) {
            int p;
            fin >> p;
            infected.insert(p);
        }

        string result_str = "";

        // Giao tiếp 2: Đọc 10 dòng test kit từ thí sinh
        for (int i = 0; i < 10; ++i) {
            int k;
            if (!(cin >> k)) die("Test " + to_string(t) + ": Khong doc duoc so luong mau k cua kit " + to_string(i+1));

            bool is_positive = false;
            for (int j = 0; j < k; ++j) {
                int p;
                cin >> p;
                if (infected.count(p)) {
                    is_positive = true;
                }
            }
            // Nếu có ít nhất 1 mẫu bệnh, kit đó dương tính
            result_str += (is_positive ? "+" : "-");
        }

        // Giao tiếp 3: Gửi chuỗi kết quả 10 ký tự lại cho thí sinh
        cout << result_str << "\n";
        cout.flush();

        // Giao tiếp 4: Đọc câu trả lời cuối cùng của thí sinh (người bị nhiễm hoặc 0)
        int ans;
        if (!(cin >> ans)) die("Test " + to_string(t) + ": Khong doc duoc ket qua cuoi cung tu thi sinh.");

        // Kiểm tra kết quả
        if (num_infected == 0) {
            if (ans != 0) {
                die("Test " + to_string(t) + ": Sai. Khong co ai nhiem nhung ban tra loi " + to_string(ans));
            }
        } else {
            // Yêu cầu của đề: Nếu có 2 người nhiễm, chỉ cần in ra 1 trong 2 người đó
            if (infected.count(ans) == 0) {
                die("Test " + to_string(t) + ": Sai. Nguoi " + to_string(ans) + " khong bi nhiem. Dap an dung la mot trong cac nguoi sau: ...");
            }
        }
    }

    // Nếu chạy qua hết các testcase mà không dính lỗi
    cerr << "ACCEPTED! Ban da vuot qua tat ca cac test." << endl;
    return 0;
}