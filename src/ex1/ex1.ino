#include <Servo.h>


class Sweeper
{
    Servo servo; // сервопривод
    int pos; // текущее положение сервы
    int increment; // увеличиваем перемещение на каждом шаге
    int updateInterval; // промежуток времени между обновлениями
    unsigned long lastUpdate; // последнее обновление положения

  public:
    Sweeper(int interval)
    {
      updateInterval = interval;
      increment = 1;
    }

    void Attach(int pin)
    {
      servo.attach(pin);
    }

    void Detach()
    {
      servo.detach();
    }

    void Update()
    {
      if ((millis() - lastUpdate) > updateInterval) // время обновлять
      {
        lastUpdate = millis();
        pos += increment;
        servo.write(pos);
        Serial.println(pos);
        if ((pos >= 180) || (pos <= 0)) // конец вращения
        {
          // обратное направление
          increment = -increment;
        }
      }
    }
};


Sweeper sweeper1(15);
Sweeper sweeper2(25);

void setup() {
  Serial.begin(9600);
  sweeper1.Attach(9);
}

void loop() {
  sweeper1.Update();
  if (digitalRead(2) == HIGH)
  {
    sweeper2.Update();
  }
}
