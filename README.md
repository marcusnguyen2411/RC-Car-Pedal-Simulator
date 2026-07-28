# 🎛️Accelerating LED Dimmer

An Arduino LED controller built to test push-button acceleration logic. It uses quick taps for fine adjustments and a long press for smooth, continuous ramping - test run before applying it to my remote-controlled car project!

---

## 📹 Project Demonstration

https://github.com/user-attachments/assets/4b97dd0a-56e8-4f34-af69-1389dcbef28b

---

## 💻 Circuit Logic Snippet

```cpp
if (upEvent == 0) {
    upHold += 1;
    if (upHold >= 8) {
      if (upTime - upTemp > 0) {
        delay(upTime - upTemp);
        upTemp = upTemp + 2;
      };
      brightness += 2 + (upTemp / 10);
      brightness = check(brightness);
      analogWrite(LED, brightness);
      Serial.println(brightness);
    }
  } else if (upEvent == 1) {
    upHold = 0;
    upTemp = 0;
  }

