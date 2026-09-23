import requests
from bs4 import BeautifulSoup
import pandas as pd
import re
import time

url = "https://rank.thptchuyenhatinh.edu.vn/"

session = requests.Session()
headers = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/124.0.0.0 Safari/537.36',
    'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8',
    'Accept-Language': 'vi,en-US;q=0.9,en;q=0.8',
    'Referer': url,
    'Origin': url,
    'Connection': 'keep-alive'
}

try:
    session.get(url, headers=headers)
except Exception as e:
    print(f"Lưu ý: Hiện tại không thể kết nối tới website (Server có thể đang sập): {e}")

# ==================================================
# DANH SÁCH SỐ BÁO DANH CẦN CÀO (Thay đổi khoảng số ở đây)
# ==================================================
danh_sach_sbd = [str(i) for i in range(381070, 381085)] # Nới rộng phạm vi để test cho đã

du_lieu_tong_hop = []

print("==================================================")
print("BẮT ĐẦU CÀO ĐIỂM & TỰ ĐỘNG PHÂN CHIA SHEET EXCEL")
print("==================================================")

for sbd in danh_sach_sbd:
    print(f"--> Đang tra cứu SBD {sbd}: ", end="", flush=True)
    payload = {'sbd': sbd}
    
    try:
        # Gửi request bằng JSON chống lỗi hệ thống
        headers['Content-Type'] = 'application/json'
        response = session.post(url, json=payload, headers=headers)
        
        if response.status_code == 502:
            headers['Content-Type'] = 'application/x-www-form-urlencoded'
            response = session.post(url, data=payload, headers=headers)
            
        if response.status_code != 200:
            print(f"Bỏ qua (Mã lỗi: {response.status_code})")
            continue
            
        soup = BeautifulSoup(response.text, 'html.parser')
        text_all = re.sub(r'\s+', ' ', soup.get_text())
        
        if "Thông tin thí sinh" not in text_all:
            print("SBD trống.")
            continue
            
        thi_sinh = {
            "SBD": sbd,
            "Họ và tên": "",
            "Toán (Cơ bản)": "",
            "Tiếng Anh (Cơ bản)": "",
            "Ngữ văn (Cơ bản)": "",
            "Tổng Đại Trà": "",
            "Môn Chuyên 1": "",
            "Điểm Chuyên 1": "",
            "Tổng Điểm Chuyên 1": "",
            "Thứ hạng Chuyên 1": "",
            "Môn Chuyên 2": "",
            "Điểm Chuyên 2": "",
            "Tổng Điểm Chuyên 2": "",
            "Thứ hạng Chuyên 2": "",
            "Xếp Hạng Toàn Kỳ Thi": ""
        }
        
        # Bóc tách Họ tên
        ten_match = re.search(r"Họ và tên:\s*([^*]+)", text_all)
        if ten_match:
            thi_sinh["Họ và tên"] = ten_match.group(1).split("Số báo danh:")[0].strip()
        
        # Bóc tách xếp hạng chung
        hang_match = re.search(r"Đạt hạng\s*(\d+)\s*trong\s*(\d+)\s*thí sinh", text_all)
        if hang_match:
            thi_sinh["Xếp Hạng Toàn Kỳ Thi"] = f"{hang_match.group(1)}/{hang_match.group(2)}"
            
        tables = soup.find_all('table')
        
        # Bảng đại trà
        if len(tables) >= 1:
            for row in tables[0].find_all('tr'):
                cells = [c.get_text(strip=True) for c in row.find_all(['td', 'th'])]
                if len(cells) >= 2:
                    mon = cells[0]
                    diem = cells[1]
                    if "Toán" in mon: thi_sinh["Toán (Cơ bản)"] = diem
                    elif "Tiếng Anh" in mon: thi_sinh["Tiếng Anh (Cơ bản)"] = diem
                    elif "Ngữ văn" in mon: thi_sinh["Ngữ văn (Cơ bản)"] = diem
                    elif "Tổng không chuyên" in mon: thi_sinh["Tổng Đại Trà"] = diem
                        
        # Bảng chuyên
        if len(tables) >= 2:
            idx_chuyen = 1
            for row in tables[1].find_all('tr'):
                cells = [c.get_text(strip=True) for c in row.find_all(['td', 'th'])]
                if len(cells) >= 3 and "Môn" not in cells[0]:
                    if idx_chuyen == 1:
                        thi_sinh["Môn Chuyên 1"] = cells[0]
                        thi_sinh["Điểm Chuyên 1"] = cells[1]
                        thi_sinh["Tổng Điểm Chuyên 1"] = cells[2]
                        idx_chuyen += 1
                    elif idx_chuyen == 2:
                        thi_sinh["Môn Chuyên 2"] = cells[0]
                        thi_sinh["Điểm Chuyên 2"] = cells[1]
                        thi_sinh["Tổng Điểm Chuyên 2"] = cells[2]
                        idx_chuyen += 1
                elif len(cells) == 1 and ("Top" in cells[0] or "Hạng" in cells[0]) and "toàn kỳ thi" not in cells[0]:
                    if idx_chuyen == 2 and not thi_sinh["Thứ hạng Chuyên 1"]:
                        thi_sinh["Thứ hạng Chuyên 1"] = cells[0]
                    elif idx_chuyen == 3 and not thi_sinh["Thứ hạng Chuyên 2"]:
                        thi_sinh["Thứ hạng Chuyên 2"] = cells[0]
                        
        du_lieu_tong_hop.append(thi_sinh)
        print(f"Thành công! -> [{thi_sinh['Họ và tên']}]")
        
    except Exception as e:
        print(f"Lỗi: {e}")
        
    time.sleep(1.0)

print("\n--------------------------------------------------")
print("TIẾN HÀNH PHÂN CHIA VÀ XUẤT FILE EXCEL...")
print("--------------------------------------------------")

if du_lieu_tong_hop:
    df = pd.DataFrame(du_lieu_tong_hop)
    file_name = "Ket_Qua_Tuyen_Sinh_Chuyen_Ha_Tinh.xlsx"
    
    # Sử dụng ExcelWriter để ghi nhiều sheet
    with pd.ExcelWriter(file_name, engine='openpyxl') as writer:
        # Trang 1: Chứa tất cả mọi người
        df.to_excel(writer, sheet_name="TỔNG HỢP", index=False)
        print("-> Đã tạo trang [TỔNG HỢP]")
        
        # Tìm danh sách các môn chuyên thực tế có trong dữ liệu cào được
        mon_1 = df["Môn Chuyên 1"].dropna().unique()
        mon_2 = df["Môn Chuyên 2"].dropna().unique()
        danh_sach_mon_chuyen = set(list(mon_1) + list(mon_2))
        
        # Lọc và chia từng môn thành một trang riêng
        for mon in danh_sach_mon_chuyen:
            mon_clean = str(mon).strip()
            if not mon_clean or mon_clean == "nan":
                continue
                
            # Lọc những thí sinh thi môn này ở NV1 hoặc NV2
            df_loc = df[(df["Môn Chuyên 1"] == mon_clean) | (df["Môn Chuyên 2"] == mon_clean)]
            
            # Làm sạch tên trang (Excel không cho phép đặt tên sheet chứa ký tự đặc biệt như / \ ? * :)
            ten_sheet = re.sub(r'[\\/*?:\[\]]', '', mon_clean)[:30].strip()
            
            # Xuất dữ liệu môn đó vào trang riêng
            df_loc.to_excel(writer, sheet_name=ten_sheet, index=False)
            print(f"-> Đã lọc thành công trang [{ten_sheet}] (Có {len(df_loc)} thí sinh)")

    print(f"\nHOÀN THÀNH XUẤT SẮC! File Excel đa trang đã được lưu tại: {file_name}")
else:
    print("Không có dữ liệu để xuất file.")
print("--------------------------------------------------")