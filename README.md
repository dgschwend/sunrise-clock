Sunrise Clock
=============

[![Image of Alarm Clock from Wide Angle][i_wide]][wide]        
[![Image of Top of Alarm Clock][i_top]][top]

A hand-made alarm clock that uses slowly increasing light and sound to wake you up.

[![Image of Low Light][i_li4]][li4] 
[![Image of Low Light][i_li6]][li6] 
[![Image of Medium Light][i_li10]][li10] 
[![Image of Bright Light][i_li23]][li23]

## Project Features

Built for an Arduino Pro Mini using the fantastic [Arduino Che Cosa framework](http://github.com/mikaelpatel/Cosa).

  - White LED Matrix Display shows Time and Menus
   [![Image of Display][i_disp]][disp]    
   [![Image of Front][i_front]][front]

  - [![Image of IR Remote][i_remote]][remote]        IR recevier, Apple Remote (or others) for control

  - [![Image of Real-Time Clock][i_rtc]][rtc]        TinyRTC Real-Time Clock (for time and alarms, battery-backup)
  
  - [![Image of MP3 Player][i_mp3]][mp3]        Cheap chinese MP3 Player for Wakeup Sound

  - [![Image of AudioBoard][i_AudioBoard]][AudioBoard]        Audio Volume Control (via LM1972)

  - [![Image of Audio AUX Port][i_audio]][audio]        Audio Switch (external Jack input, internal MP3)

  - [![Image of Amplifier][i_amplifier]][amplifier]        2 x 3W Amplifier (PAM8403)

  - [![Image of Tweeter][i_tweeter]][tweeter]        2-way Speaker
  - [![Image of Speaker inside][i_speaker_inside]][speaker_inside]        Subwoofer included in glass sphere
 
  - [![Image of Charge Port][i_charge]][charge]        2x USB Charger 5V @ 1.5A

  - [![Image of Power and USB Config Port][i_power]][power]        USB Flash / Debug Port <--> FTDI <--> Arduino

  - [![Image of Cree LMH2 LED][i_cree_led]][cree_led]                     Cree LMH2 850-lumen LED with sunset dimming

  - old Apple iBook G4 Power Supply @24.8V, 1.8A for Power


## Under-the-Hood Impressions

### Setup and Cabling
[![Image of Cables][i_cables]][cables]
[![Image of DC-DC Converter][i_dc-dc-conv]][dc-dc-conv]
[![Image of Real-Time Clock][i_rtc]][rtc]

DIY PCB for Audio Volume Control. All cabling and setup still in prototype stage. I'm thinking about doing a small PCB for all the components... Audio Quality could certainly be improved with properly shielded 4-layer PCB.

### Audio Hardware
[![Image of Amplifier][i_amplifier]][amplifier]
[![Image of AudioBoard][i_AudioBoard]][AudioBoard]
[![Image of Speaker inside][i_speaker_inside]][speaker_inside]
[![Image of Tweeter][i_tweeter1]][tweeter1]

Subwoofer Speaker uses the Glass Sphere (from an IKEA Fado Lamp) as Body. Sealing of Glass Sphere using custom Silicone Ring. No apsorptive material in sphere yet... might improve frequency response!

[![Image of MP3 Player][i_mp3]][mp3]
[![Image of Dark State][i_dark]][dark]

### Dimming of LED
[![Image of Very Low Light][i_li4]][li4]
[![Image of Low Light][i_li5]][li5]
[![Image of Low Light][i_li6]][li6]
[![Image of Medium Light][i_li10]][li10]
[![Image of Bright Light][i_li23]][li23]

## More Infos
Star this Project and contact me if you would like to know more. Right now, many parts are not properly documented. If there's any interest, I may draw and publish the full Schematics.

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
