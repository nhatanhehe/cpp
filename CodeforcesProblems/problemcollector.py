import requests
import random
import time
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC

# --- BƯỚC 1: LẤY BÀI TẬP TỪ API ---
def get_problems(min_rating, max_rating, tags, count=5):
    url = "https://codeforces.com/api/problemset.problems"
    try:
        response = requests.get(url)
        data = response.json()
        if data["status"] != "OK":
            return []

        all_problems = data["result"]["problems"]
        valid_problems = []

        for p in all_problems:
            rating = p.get("rating")
            if rating is None or not (min_rating <= rating <= max_rating):
                continue
            p_tags = p.get("tags", [])
            if all(t in p_tags for t in tags):
                valid_problems.append(p)

        random.shuffle(valid_problems)
        return valid_problems[:count]
    except Exception as e:
        print(f"Lỗi API: {e}")
        return []

# --- BƯỚC 2: TỰ ĐỘNG TẠO CONTEST QUA SELENIUM ---
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC

def auto_create_mashup(contest_name, problems):
    if not problems:
        print("Không có bài tập để tạo contest.")
        return

    options = Options()
    options.add_experimental_option("debuggerAddress", "127.0.0.1:9222")
    driver = webdriver.Chrome(options=options)
    
    # Khởi tạo bộ đợi thông minh (chờ tối đa 10 giây)
    wait = WebDriverWait(driver, 10)
    
    try:
        print("[1/3] Đang truy cập trang tạo Mashup...")
        driver.get("https://codeforces.com/mashup/new")
        time.sleep(1.5)

        # 1. Điền tên Contest
        print(f" -> Đang điền tên contest: {contest_name}")
        name_input = driver.find_element(By.NAME, "contestName")
        name_input.clear()
        name_input.send_keys(contest_name)
        
        # 2. Điền thời gian (Duration)
        duration_input = driver.find_element(By.NAME, "contestDuration")
        duration_input.clear()
        duration_input.send_keys("180")
        
        # KÍCH HOẠT FORM: Click vào ô duration và nhấn Enter nhẹ để CF render ô nhập bài
        duration_input.send_keys(Keys.ENTER)
        time.sleep(1) 

        # 3. Đợi ô nhập bài tập xuất hiện thực sự trên giao diện
        print("[2/3] Đang đợi ô nhập bài tập hiển thị và nạp mã bài...")
        
        # Chờ cho tới khi ô input xuất hiện trong DOM và hiển thị trên màn hình
        search_input = wait.until(
            EC.visibility_of_element_located((By.CSS_SELECTOR, "input.search-input, #box input[type='text'], .caption input"))
        )

        mashup_codes = [f"{p['contestId']}{p['index']}" for p in problems]
        for code in mashup_codes:
            search_input.clear()
            search_input.send_keys(code)
            time.sleep(0.8) # Chờ CF nhận diện autocomplete
            search_input.send_keys(Keys.ENTER)
            print(f"    + Đã nạp bài: {code}")
            time.sleep(0.6)

        # 4. Bấm nút Submit tạo Contest cuối cùng
        print("[3/3] Đang nhấn nút tạo Contest...")
        submit_button = driver.find_element(By.CSS_SELECTOR, "input[type='submit'].submit")
        submit_button.click()
        
        print(f"\n🎉 HOÀN THÀNH TẠO CONTEST: {contest_name}")

    except Exception as e:
        print(f"\n[!] Gặp lỗi khi điều khiển trình duyệt: {e}")
        print(f"[!] Trình duyệt đang dừng ở URL: {driver.current_url}")
# --- CẤU HÌNH VÀ CHẠY ---
if __name__ == "__main__":
    # Thay đổi thông tin tài khoản CF của bạn ở đây
    CF_USERNAME = "hotaruu"
    CF_PASSWORD = "nhatanhCHT"
    
    CONTEST_NAME = "Training 08/06"
    RATING_MIN = 800
    RATING_MAX = 1300
    TAGS = ["greedy"]
    COUNT = 10

    print("=== ĐANG LỌC BÀI TẬP TỪ API ===")
    selected_problems = get_problems(RATING_MIN, RATING_MAX, TAGS, COUNT)
    
    if selected_problems:
        print(f"Đã chọn được {len(selected_problems)} bài tập phù hợp.")
        auto_create_mashup(CONTEST_NAME, selected_problems)
    else:
        print("Không tìm thấy bài tập nào thỏa mãn điều kiện để tạo contest.")