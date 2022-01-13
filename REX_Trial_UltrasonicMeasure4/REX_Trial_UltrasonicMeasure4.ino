/*超音波センサーを使って人を検知しよう！その4
   内容
   距離によってLEDをつける数を変える
*/
const int tringPin = 2;
const int echoPin = 3;
const int ledPins[] = {11, 10, 9, 8, 7, 6, 5, 4, 3};
const int ledPinNum = 8;
double duration = 0;
double distance = 0;
int onLedPin = 3;

// Arduinoが起動した時，1度だけ実行
void setup() {
  Serial.begin(9600);
  pinMode(tringPin, OUTPUT);
  pinMode(echoPin, INPUT);
  for (int i = 0; i < ledPinNum; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

// 起動中ずっと実行
void loop() {
  // 両方のピンをLOWで初期化
  digitalWrite(tringPin, LOW);
  digitalWrite(echoPin, LOW);
  delayMicroseconds(1); // 1us待つ
  digitalWrite(tringPin, HIGH); // 超音波パルスをを発射
  delayMicroseconds(10); // 10us間待つ←リファレンスに準じて，最低10us必要
  digitalWrite(tringPin, LOW); // パルスを止める
  duration = pulseIn(echoPin, HIGH) * pow(10, -6); // パルスが帰ってくるまでの時間μsを秒へ変換
  distance = duration * 34000 / 2; // 距離 = 時間 * 速度で表せるので，速度は音速340m/sなので→3400cm/sとする．2で割るのは，進んだ距離は出てきて帰ってきた時までの距離のため
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
