constexpr int HOLD_ON_OFF_SWITCH_PIN = 4;

void setup() {
    Serial.begin(9600);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    for (int i = 0; i < 5; i++) {
        delay(100);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(100);
        digitalWrite(LED_BUILTIN, LOW);
    }

    pinMode(HOLD_ON_OFF_SWITCH_PIN, INPUT);
}

void loop() {
    const int buttonState = digitalRead(HOLD_ON_OFF_SWITCH_PIN);
    Serial.println(buttonState);
    if (buttonState == HIGH) {
        digitalWrite(LED_BUILTIN, HIGH);
    } else {
        digitalWrite(LED_BUILTIN, LOW);
    }
}
