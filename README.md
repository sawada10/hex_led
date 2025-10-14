# LED コントローラー
## 概要
ROSシリアルでLEDを制御するためのプログラム。色、明るさ、点滅時間の変更やレインボーに光らせることができる。

## 実行環境
### 使用部品
- [M5StickC](https://www.switch-science.com/products/5517?_pos=10&_sid=1562a242b&_ss=r "M5 StickC")
  - M5Stackでも代用可能
  - ただし、プログラム中のNeopixel_PINはマイコンの種類によって異なるので注意
    - e.g.) M5StickCはデバイスの裏面で番号を確認でき、Neopixel_PIN = 32である.
    - また、M5stickC & noetic-devel のときは、クラスの参照先が間違っているので、[このコミット](https://github.com/sawada10/hex_led/commit/b69572a22edfd829e5d3aa5e29f797c54c0ec27f)が大切（M5stickC & melodic develのときは大丈夫)
      - cf.  [melodic-devel](https://github.com/ros-drivers/rosserial/blob/5ff397fc17b6935ccf90ed840bcb874bfd608fe9/rosserial_arduino/src/ros_lib/ros.h#L40)では上記のコミットの変更がマージされているが、[noetic-devel](https://github.com/ros-drivers/rosserial/blob/c169ae2173dcfda7cee567d64beae45198459400/rosserial_arduino/src/ros_lib/ros.h#L40)ではマージされていない
- [LED](https://www.switch-science.com/products/6058?_pos=1&_sid=431122913&_ss=r "LED")
- Arduino IDEを用いるとboardのバージョン等が理由でコンパイル時にエラーが出たりマイコンが再起動を繰り返したりすることがあるので、PlatformIOの使用を推奨

### 配線
Grove線でM5StickCとLEDをつなぐ。LEDは複数連結可能。

### 書き込み方
```
pio run -t upload
```
シリアルモニターを確認したいときは以下を実行
```
pio device monitor -b 115200
```

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
