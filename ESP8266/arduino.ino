#include <SoftwareSerial.h> // Thư viện cho cổng nối tiếp mềm
#define RX_PIN 10 // Chân RX của cổng nối tiếp mềm
#define TX_PIN 11 // Chân TX của cổng nối tiếp mềm
#define LED_PIN 13 // Chân kết nối với led

SoftwareSerial mySerial(RX_PIN, TX_PIN); // Tạo một đối tượng cổng nối tiếp mềm

void setup() {
  Serial.begin(9600); // Khởi tạo cổng nối tiếp cứng với tốc độ baud là 9600
  mySerial.begin(9600); // Khởi tạo cổng nối tiếp mềm với tốc độ baud là 9600
  pinMode(LED_PIN, OUTPUT); // Đặt chân kết nối với led là chân đầu ra
}

void loop() {
  if (mySerial.available()) { // Nếu có dữ liệu từ cổng nối tiếp mềm
    char c = mySerial.read(); // Đọc ký tự điều khiển
    mySerial.println(c); // In ra ký tự điều khiển qua cổng nối tiếp mềm
    Serial.println(c); // In ra ký tự điều khiển qua cổng nối tiếp cứng
    if (c == '0') { // Nếu ký tự là '0'
      // Bật led
      digitalWrite(LED_PIN, HIGH);
      Serial.println("LED is on"); // In trạng thái led qua cổng nối tiếp cứng
    }
    else if (c == '1') { // Nếu ký tự là 'f'
      // Tắt led
      digitalWrite(LED_PIN, LOW);
      Serial.println("LED is off"); // In trạng thái led qua cổng nối tiếp cứng
    }
    else { // Nếu ký tự khác
      // Không làm gì
      Serial.println("Invalid command"); // In báo lỗi qua cổng nối tiếp cứng
    }
  }
}
