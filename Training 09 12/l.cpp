#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll n;
// Mảng tên: Sắp xếp theo thứ tự 1-based (1=Sheldon, 5=Howard)
string s[]={"","Sheldon","Leonard","Penny","Rajesh","Howard"};

main(){
    // Khởi tạo nhanh IO
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);

    cin>>n;

    ll total_cans = 5; // Tổng số lon trong vòng hiện tại (ban đầu là 5 * 2^0)
    ll cans_per_person = 1; // Số lần mỗi người uống trong vòng hiện tại (2^0)

    // Bước 1: Trừ đi số lon của các vòng trước đó
    while (n > total_cans) {
        // Trừ đi tổng số lon của vòng hiện tại (total_cans = 5 * cans_per_person)
        n -= total_cans;

        // Chuyển sang vòng tiếp theo
        cans_per_person *= 2; // Kích thước nhóm (số lần uống) nhân đôi
        total_cans *= 2; // Tổng số lon trong vòng tiếp theo = 5 * (cans_per_person mới)
    }

    // Sau vòng lặp, 'n' là chỉ số lon còn lại trong vòng hiện tại (1-based)
    // 'cans_per_person' là số lần mỗi người uống trong vòng này (W = 2^k)

    // Bước 2: Tìm người uống bằng cách chia n cho cans_per_person

    // Nếu n là bội số của cans_per_person (ví dụ: n=2, cans_per_person=2),
    // thì người uống là n/cans_per_person.
    // Nếu không (ví dụ: n=3, cans_per_person=2), thì người uống là (n/cans_per_person) + 1.

    ll person_index = (n + cans_per_person - 1) / cans_per_person;

    // Cách khác đơn giản hơn:
    // long long person_index = (n - 1) / cans_per_person + 1;

    cout << s[person_index];

    return 0;
}
