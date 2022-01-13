/*超音波センサーを使って人を検知しよう！その5
   内容
   NewPringを使ってプログラムを簡略化しよう！
*/
#include <NewPing.h>
NewPing sonar(2,2,200); // trigPinとechoPinがどこについているか，最大何センチまで測れるのかを設定

const int ledPins[] = {11, 10, 9, 8, 7, 6, 5, 4, 3};
const int ledPinNum = 8;
int distance = 0;
int onLedPin = 0;

// Arduinoが起動した時，1度だけ実行
void setup() {
  Serial.begin(9600);
  for (int i = 0; i < ledPinNum; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

// 起動中ずっと実行
void loop() {
  distance = sonar.ping_cm(); // 距離を取得
  
  Serial.print("距離は");
  Serial.print(distance);
  Serial.println("cmです");

  // 距離によって数値を変える
  onLedPin = map(distance, 3, 30, 8, 0); // 3~30[cm]の距離をいい感じに8~0の間に調節してくれる
  
  // 8個のLEDを点灯させるプログラム
  for (int i = 0; i < ledPinNum; i++) {
    if (i < onLedPin) {
      digitalWrite(ledPins[i], HIGH);
    } else {
      digitalWrite(ledPins[i], LOW);
    }
  }
}
