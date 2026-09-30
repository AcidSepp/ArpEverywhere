# ArpEverywhere
This project aims to bring Hold and Arp to Synthesizers that do not have it.

[![Adding Hold and Better Arp to the Korg Minilogue](https://img.youtube.com/vi/hi0-8F53ltk/0.jpg)](https://www.youtube.com/watch?v=hi0-8F53ltk)

## BOM
- Microcontroller
  - 1x Arduino Nano ESP32
  - 1x 32 PIN DIP Socket, 15. (wide)
- ICs
  - 2x 6n128 Optocoupler
  - 2x 8 PIN DIP Socket
- Switches
  - 4x Toggle Switch
  - 2x 12 Way Rotary Switch
- Sockets
  - 4x MIDI 5Pin DIN Panel Mount Socket
- Resistors
  - 2x 480-1KΩ
  - 2x 4.7KΩ
  - 2x 10Ω
  - 2x 20Ω
  - 2x 100Ω
  - 24x 1kΩ
  - 4x 10kΩ
  - 2x 220Ω
- Diodes
  - 2x 1n914 Diode
- Connectors
  - 6x 2.54mm 0.1" Pitch PCB Mount Screw Terminal Block
- Prototype Board

## MIDI IN Circuit
The MIDI IN circuit is based on the [MIDI IN circuit form Notes And Volts](https://www.notesandvolts.com/2015/02/midi-and-arduino-build-midi-input.html).
Modifications to make it compatible with 3.3V:
- Connect Pin 8 of the optocoupler to +5V.
- Connect Pin 6 of the optocoupler to the RX Pin and to +3.3V via a 480-1KΩ resistor.

## MIDI OUT Circuit
The MIDI OUT circuit is based on the [MIDI OUT circuit from Notes And Volts](https://www.notesandvolts.com/2015/03/midi-for-arduino-build-midi-output.html).
Modifications to make it compatible with 3.3V:
- Connect Pin 4 of the MIDI Out Socket to +3.3V via a 30Ω resistor.
- Connect Pin 5 of the MIDI Out Socket to the TX Pin via a 10Ω resistor.

## Rotary Switch Circuit
The Rotary Switch Circuit is based on [Scotty D's circuit](https://www.youtube.com/watch?v=UbnNhUDheE8&t=487s).
I do not use the capacitor, and add another 1kΩ resitor at the end of the ladder.

## Toggle Switch Circuit
I used a standard toggle switch circuit with a 10KΩ pullup-resistor.
