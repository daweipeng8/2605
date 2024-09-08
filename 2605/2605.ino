bool motorControlFlag1 = false;
bool motorControlFlag2 = false;

bool flag = false;

void setup() {
  // 设置PA0, PA1为输入引脚
  pinMode(PA0, INPUT);
  pinMode(PA1, INPUT);

  pinMode(PA7, INPUT);

  // 设置PA4, PA5, PA6, PB0为输出引脚
  pinMode(PA4, OUTPUT);
  pinMode(PA5, OUTPUT);
  pinMode(PA6, OUTPUT);
  pinMode(PB0, OUTPUT);

  // 初始状态下将PA4, PA5, PA6, PB0设为低电平
  digitalWrite(PA4, LOW);
  digitalWrite(PA5, LOW);
  digitalWrite(PA6, LOW);
  digitalWrite(PB0, LOW);
  Serial.begin(9600);
}

void loop() {

  int val = analogRead(PA7);
  if (!flag)
  {
    if (val > 400)
    {
      delay(200);
      if (val > 200)
      {
        flag = true;
      }
    }
  }
  if (flag)
  {
    if (val < 100)
    {
      delay(200);
      if (val < 100)
      {
        flag = false;
        // 2号电机反转3秒
        digitalWrite(PA5, LOW);
        digitalWrite(PA6, HIGH);
        delay(3000);

        // 2号电机停止1秒
        digitalWrite(PA5, LOW);
        digitalWrite(PA6, LOW);
        delay(1000);

        // 1号电机反转1秒
        digitalWrite(PA4, LOW);
        digitalWrite(PB0, HIGH);
        delay(2000);

        // 1号电机停止
        digitalWrite(PA4, LOW);
        digitalWrite(PB0, LOW);
      }
    }
  }

  int PA0State = digitalRead(PA0);
  int PA1State = digitalRead(PA1);

  Serial.print(val);
  Serial.print("  ");
  Serial.print(PA0State);
  Serial.print("  ");
  Serial.print(PA1State);
  Serial.println("  ");
  delay(20);
  if (flag)
  {
    if (PA1State == HIGH && PA0State == LOW && !motorControlFlag1) {
      delay(20);
      if (digitalRead(PA1) == HIGH && digitalRead(PA0) == LOW && !motorControlFlag1) {
        motorControlFlag1 = true;  // 设置标志位1
        motorControlFlag2 = false; // 确保另一个标志位被重置

        // 1号电机正转2秒
        digitalWrite(PA4, HIGH);
        digitalWrite(PB0, LOW);
        delay(2000);

        // 1号电机停止1秒
        digitalWrite(PA4, LOW);
        digitalWrite(PB0, LOW);
        delay(1000);

        // 2号电机正转3秒
        digitalWrite(PA5, HIGH);
        digitalWrite(PA6, LOW);
        delay(3000);

        // 2号电机停止
        digitalWrite(PA5, LOW);
        digitalWrite(PA6, LOW);
      }
    } else if (PA1State == LOW && PA0State == HIGH && !motorControlFlag2) {
      delay(20);
      if (digitalRead(PA1) == LOW && digitalRead(PA0) == HIGH && !motorControlFlag2) {
        motorControlFlag2 = true;  // 设置标志位2
        motorControlFlag1 = false; // 确保另一个标志位被重置

        // 2号电机反转3秒
        digitalWrite(PA5, LOW);
        digitalWrite(PA6, HIGH);
        delay(3000);

        // 2号电机停止1秒
        digitalWrite(PA5, LOW);
        digitalWrite(PA6, LOW);
        delay(1000);

        // 1号电机反转1秒
        digitalWrite(PA4, LOW);
        digitalWrite(PB0, HIGH);
        delay(2000);

        // 1号电机停止
        digitalWrite(PA4, LOW);
        digitalWrite(PB0, LOW);
      }
    } else if ((PA1State == LOW && PA0State == LOW) || (PA1State == HIGH && PA0State == HIGH)) {
      // 当PA0和PA1都是低电平或都是高电平时，重置标志位
      motorControlFlag1 = false;
      motorControlFlag2 = false;
    }
  }
}
