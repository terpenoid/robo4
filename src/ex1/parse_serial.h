/*

  https://alexgyver.ru/lessons/serial/


  Данный алгоритм позволяет получить через Serial пачку значений, и раскидать
  их в целочисленный массив. Использовать можно банально для управления
  ЧЕМ УГОДНО через bluetooth, так как bluetooth модули есть UART интерфейс связи.
  Либо управлять через Serial с какой-то программы с ПК
  Как использовать:
  1) В PARSE_AMOUNT указывается, какое количество значений мы хотим принять.
  От этого значения напрямую зависит размер массива принятых данных, всё просто
  2) Есть массив inputData, его размер задаётся дефайном INPUT_AMOUNT
  Вот это значение должно быть больше или равно числу СИМВОЛОВ, которое будет в пакете
  То есть в с чёт идут пробелы, цифры и заголовок и хвост
  Пример: пакет $110 25 600 920; содержит 16 символов, таким образом INPUT_AMOUNT должен быть НЕ МЕНЬШЕ!
  3) Пакет данных на приём должен иметь вид:
  Начало - символ $
  Разделитель - пробел
  Завершающий символ - ;
  Пример пакета: $110 25 600 920;  будет раскидан в массив intData согласно порядку слева направо
  Что делает данный скетч:
  Принимает пакет данных указанного выше вида, раскидывает его в массив intData, затем выводит обратно в порт.
*/
#define PARSE_AMOUNT 4       // число значений в массиве, который хотим получить
#define INPUT_AMOUNT 80      // максимальное количество символов в пакете, который идёт в сериал
char inputData[INPUT_AMOUNT];  // массив входных значений (СИМВОЛЫ)
int intData[PARSE_AMOUNT];     // массив численных значений после парсинга
boolean recievedFlag;
boolean getStarted;
byte index;
String string_convert;
void parsing(Stream &port) { // Serial/BT/etc
  while (port.available() > 0) {
    char incomingByte = port.read();      // обязательно ЧИТАЕМ входящий символ
    if (incomingByte == '$') {              // если это $
      getStarted = true;                    // поднимаем флаг, что можно парсить
    } else if (incomingByte != ';' && getStarted) { // пока это не ;
      // в общем происходит всякая магия, парсинг осуществляется функцией strtok_r
      inputData[index] = incomingByte;
      index++;
      inputData[index] = '\0';
    } else {
      if (getStarted) {
        char *p = inputData;
        char *str;
        index = 0;
        String value = "";
        while ((str = strtok_r(p, " ", & p)) != NULL) {
          string_convert = str;
          intData[index] = string_convert.toInt();
          index++;
        }
        index = 0;
      }
    }
    if (incomingByte == ';') {        // если таки приняли ; - конец парсинга
      getStarted = false;
      recievedFlag = true;
    }
  }
}
