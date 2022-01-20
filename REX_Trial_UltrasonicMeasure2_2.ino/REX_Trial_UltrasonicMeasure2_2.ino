/*超音波センサーを使って人を検知しよう！その2-2
 * 内容
 * 距離が一定以下になると圧力ブザーを鳴らす
 */
const int tringPin = 2;
const int echoPin = 3;
const int buzzerPin = 6;

double duration = 0;
double distance = 0;

// Arduinoが起動した時，1度だけ実行
void setup() {
  Serial.begin(9600);
  pinMode(tringPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin,OUTPUT);
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
  duration = pulseIn(echoPin, HIGH)* pow(10,-6); // パルスが帰ってくるまでの時間μsを秒へ変換
  distance = duration * 34000 / 2; // 距離 = 時間 * 速度で表せるので，速度は音速340m/sなので→3400cm/sとする．2で割るのは，進んだ距離は出てきて帰ってきた時までの距離のため
  Serial.print("距離は");
  Serial.print(distance);
  Serial.println("cmです");

  //距離が10[cm]未満の時ブザーを鳴らす（救急車のサイレン）
  if(distance < 10){
    tone(buzzerPin,960,500);
    delay(500);
    tone(buzzerPin,770,500);
    delay(500);
  }
}
