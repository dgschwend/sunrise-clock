Sunrise Clock
=============

![top view](https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/top.jpg)
![wide view](https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/wide.jpg)

A beautiful, hand-made alarm clock that uses slowly increasing light and sound to wake you up.

![low light](https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/li6.jpg)
![medium light](https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/li10.jpg)
![bright light](https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/li23.jpg)

### Project Features

Built for an Arduino Pro Mini using the fantastic [Arduino Che Cosa framework](http://github.com/mikaelpatel/Cosa).

  - White LED Matrix Display shows Time and Menus
  ![display](https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/disp.jpg)
  ![display](https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/front.jpg)
  - IR recevier and Apple Remote (others usable as well), for control and configuration

  ![ir](https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/remote.jpg)
  - TinyRTC Real-Time Clock (for time and alarms, battery-backup)

  ![rtc](https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/rtc.jpg)
  - Cheap chinese MP3 Player for Wakeup Sound

  ![mp3 player](https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/mp3.jpg)
  - Audio Volume Control (via LM1972)

  ![Audio Board](https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/AudioBoard.jpg)
  - Audio Switch (internal MP3 player/external AUX)

  ![audio ports](https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/audio.jpg)
  - 2 x 3W Amplifier (PAM8403)

  ![amplifier](https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/amplifier.jpg)
  - 2-way Speaker (subwoofer included in glass sphere)

  ![tweeter](https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/tweeter.jpg)
  ![speaker inside](https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/speaker_inside.jpg)
  - Cree LMH2 850-lumen LED with sunset dimming

  ![cree lmh2 led](https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/cree_led.jpg)
  - 2x USB Charger 5V @ 1.5A

  ![usb charger ports](https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/charge.jpg)
  - USB Debug Port <--> FTDI <--> Arduino
  - USB Port for MP3 Player (access SD Card, change sound)
  - old Apple iBook G4 Power Supply @24.8V, 1.8A for Power

  ![power and usb config ports](https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/power.jpg)


### Under-the-Hood Impressions
![cables](https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/cables.jpg)
![Audio Board](https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/AudioBoard.jpg)
![dc-dc converter](https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/dc-dc-conv.jpg)

![amplifier](https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/amplifier.jpg)
![speaker inside](https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/speaker_inside.jpg)
![tweeter](https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/tweeter1.jpg)

![dark](https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/dark.jpg)
![low light 4](https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/li4.jpg)
![low light 5](https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/li5.jpg)

![low light 6](https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/li6.jpg)
![medium light](https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/li10.jpg)
![bright light](https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/li23.jpg)

### Hardware
Schematics and Details to follow.

[i_amplifier]: https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/amplifier.jpg
[amplifier]: https://github.com/dgschwend/sunrise-clock/blob/master/Documentation/Photos/amplifier.jpg
[i_audio]: https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/audio.jpg
[audio]: https://github.com/dgschwend/sunrise-clock/blob/master/Documentation/Photos/audio.jpg
[i_AudioBoard]: https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/AudioBoard.jpg
[AudioBoard]: https://github.com/dgschwend/sunrise-clock/blob/master/Documentation/Photos/AudioBoard.jpg
[i_cables]: https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/cables.jpg
[cables]: https://github.com/dgschwend/sunrise-clock/blob/master/Documentation/Photos/cables.jpg
[i_charge]: https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/charge.jpg
[charge]: https://github.com/dgschwend/sunrise-clock/blob/master/Documentation/Photos/charge.jpg
[i_cree_led]: https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/cree_led.jpg
[cree_led]: https://github.com/dgschwend/sunrise-clock/blob/master/Documentation/Photos/cree_led.jpg
[i_dark]: https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/dark.jpg
[dark]: https://github.com/dgschwend/sunrise-clock/blob/master/Documentation/Photos/dark.jpg
[i_dc-dc-conv]: https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/dc-dc-conv.jpg
[dc-dc-conv]: https://github.com/dgschwend/sunrise-clock/blob/master/Documentation/Photos/dc-dc-conv.jpg
[i_disp]: https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/disp.jpg
[disp]: https://github.com/dgschwend/sunrise-clock/blob/master/Documentation/Photos/disp.jpg
[i_front]: https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/front.jpg
[front]: https://github.com/dgschwend/sunrise-clock/blob/master/Documentation/Photos/front.jpg
[i_li4]: https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/li4.jpg
[li4]: https://github.com/dgschwend/sunrise-clock/blob/master/Documentation/Photos/li4.jpg
[i_li5]: https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/li5.jpg
[li5]: https://github.com/dgschwend/sunrise-clock/blob/master/Documentation/Photos/li5.jpg
[i_li6]: https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/li6.jpg
[li6]: https://github.com/dgschwend/sunrise-clock/blob/master/Documentation/Photos/li6.jpg
[i_li10]: https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/li10.jpg
[li10]: https://github.com/dgschwend/sunrise-clock/blob/master/Documentation/Photos/li10.jpg
[i_li23]: https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/li23.jpg
[li23]: https://github.com/dgschwend/sunrise-clock/blob/master/Documentation/Photos/li23.jpg
[i_mp3]: https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/mp3.jpg
[mp3]: https://github.com/dgschwend/sunrise-clock/blob/master/Documentation/Photos/mp3.jpg
[i_power]: https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/power.jpg
[power]: https://github.com/dgschwend/sunrise-clock/blob/master/Documentation/Photos/power.jpg
[i_remote]: https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/remote.jpg
[remote]: https://github.com/dgschwend/sunrise-clock/blob/master/Documentation/Photos/remote.jpg
[i_rtc]: https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/rtc.jpg
[rtc]: https://github.com/dgschwend/sunrise-clock/blob/master/Documentation/Photos/rtc.jpg
[i_speaker_inside]: https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/speaker_inside.jpg
[speaker_inside]: https://github.com/dgschwend/sunrise-clock/blob/master/Documentation/Photos/speaker_inside.jpg
[i_top]: https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/top.jpg
[top]: https://github.com/dgschwend/sunrise-clock/blob/master/Documentation/Photos/top.jpg
[i_tweeter]: https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/tweeter.jpg
[tweeter]: https://github.com/dgschwend/sunrise-clock/blob/master/Documentation/Photos/tweeter.jpg
[i_tweeter1]: https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/tweeter1.jpg
[tweeter1]: https://github.com/dgschwend/sunrise-clock/blob/master/Documentation/Photos/tweeter1.jpg
[i_wide]: https://raw.githubusercontent.com/dgschwend/sunrise-clock/master/Documentation/Photos/Thumbs/wide.jpg
[wide]: https://github.com/dgschwend/sunrise-clock/blob/master/Documentation/Photos/wide.jpg
