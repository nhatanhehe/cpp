#include "testlib.h"
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

// Hàm kiểm tra xem số có hợp lệ không (không có số 0 ở đầu nếu độ dài > 1)
bool isValidNumber(const string& s) {
    if (s.empty()) return false;
    for (char c : s) {
        if (!isdigit(c)) return false;
    }
    if (s.length() > 1 && s[0] == '0') return false;
    return true;
}

// Hàm cộng hai số nguyên lớn dưới dạng chuỗi
string addBigInt(const string& a, const string& b) {
    string res = "";
    int i = (int)a.length() - 1, j = (int)b.length() - 1, carry = 0;
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += a[i--] - '0';
        if (j >= 0) sum += b[j--] - '0';
        res += to_string(sum % 10);
        carry = sum / 10;
    }
    reverse(res.begin(), res.end());
    return res;
}

int main(int argc, char* argv[]) {
    // Khởi tạo testlib checker
    registerTestlibCmd(argc, argv);

    // Đọc dữ liệu từ file input (REBUSS.INP)
    string inf1 = inf.readString();
    string inf2 = inf.readString();
    string inf3 = inf.readString();

    // Đọc đáp án từ file ans (Jury's answer)
    string ans1 = ans.readString();
    bool ans_is_no_solution = (ans1.find("No Solution") != string::npos || ans1.find("NO SOLUTION") != string::npos);

    // Đọc kết quả từ file output của thí sinh (ouf)
    string ouf1 = ouf.readString();
    bool ouf_is_no_solution = (ouf1.find("No Solution") != string::npos || ouf1.find("NO SOLUTION") != string::npos);

    // Trường hợp đáp án là "No Solution"
    if (ans_is_no_solution) {
        if (!ouf_is_no_solution) {
            quitf(_wa, "Expected No Solution, but got a solution.");
        }
        quitf(_ok, "Correctly reported No Solution.");
    }
    // Trường hợp có lời giải
    else {
        if (ouf_is_no_solution) {
            quitf(_wa, "A solution exists, but contestant reported No Solution.");
        }

        // Đọc tiếp dòng 2 và dòng 3 từ file output của thí sinh
        string ouf2 = ouf.readString();
        string ouf3 = ouf.readString();

        // 1. Kiểm tra độ dài và khớp mẫu (pattern matching) với dòng 1
        if (ouf1.length() != inf1.length())
            quitf(_wa, "Line 1 length mismatch.");
        for (size_t i = 0; i < inf1.length(); i++) {
            if (inf1[i] != '*' && inf1[i] != ouf1[i])
                quitf(_wa, "Line 1 does not match the template pattern at index %d.", (int)i);
            if (!isdigit(ouf1[i]))
                quitf(_wa, "Line 1 contains non-digit characters.");
        }

        // 2. Kiểm tra dòng 2
        if (ouf2.length() != inf2.length())
            quitf(_wa, "Line 2 length mismatch.");
        for (size_t i = 0; i < inf2.length(); i++) {
            if (inf2[i] != '*' && inf2[i] != ouf2[i])
                quitf(_wa, "Line 2 does not match the template pattern at index %d.", (int)i);
            if (!isdigit(ouf2[i]))
                quitf(_wa, "Line 2 contains non-digit characters.");
        }

        // 3. Kiểm tra dòng 3
        if (ouf3.length() != inf3.length())
            quitf(_wa, "Line 3 length mismatch.");
        for (size_t i = 0; i < inf3.length(); i++) {
            if (inf3[i] != '*' && inf3[i] != ouf3[i])
                quitf(_wa, "Line 3 does not match the template pattern at index %d.", (int)i);
            if (!isdigit(ouf3[i]))
                quitf(_wa, "Line 3 contains non-digit characters.");
        }

        // 4. Kiểm tra ràng buộc chữ số đầu tiên phải khác 0 (tránh leading zeros)
        if (!isValidNumber(ouf1))
            quitf(_wa, "Line 1 has invalid leading zero.");
        if (!isValidNumber(ouf2))
            quitf(_wa, "Line 2 has invalid leading zero.");
        if (!isValidNumber(ouf3))
            quitf(_wa, "Line 3 has invalid leading zero.");

        // 5. Kiểm tra tính đúng đắn của phép cộng: ouf1 + ouf2 == ouf3
        if (addBigInt(ouf1, ouf2) != ouf3) {
            quitf(_wa, "Arithmetic equation is incorrect: %s + %s != %s",
                  ouf1.c_str(), ouf2.c_str(), ouf3.c_str());
        }

        // Nếu vượt qua mọi kiểm tra -> Chấm Đúng (Accepted)
        quitf(_ok, "Solution is correct.");
    }

    return 0;
}
