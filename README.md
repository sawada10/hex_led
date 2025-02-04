# LED コントローラー
## 概要
ROSシリアルでLEDを制御するためのプログラム。色、明るさ、点滅時間の変更やレインボーに光らせることができる。
## 実行環境
### 使用部品
- [M5StickC](https://www.switch-science.com/products/5517?_pos=10&_sid=1562a242b&_ss=r "M5 StickC")
  - M5Stackでも代用可能
- [LED](https://www.switch-science.com/products/6058?_pos=1&_sid=431122913&_ss=r "LED")
### 配線
Grove線でM5StickCとLEDをつなぐ。LEDは複数連結可能。

## 光り方を変える
```
rostopic pub /led_mode std_msgs/UInt16 "data: 1"
```
- 1: 常時点灯モード
- 2: 点滅モード
- 3: 七色モード
```
rostopic pub /led_rgb std_msgs/ColorRGBA "r: 255.0 g: 0.0 b: 0.0 a: 10.0"
```
rgb値を指定。aには明るさが入る。
```
rostopic pub /led_blink_time std_msgs/UInt16 "data: 3"
```
点滅モードのときに何回点滅するかを決める。
```
rostopic pub /led_duration std_msgs/Float32 "data: 2.0"
```
点滅モードのときの点灯時間を決定する。
```
rostopic pub /led_rainbow_delta_hue std_msgs/UInt16 "data: 5"
```
一つのLEDボード内の隣接するのLED同士の色のhue値を変える。
