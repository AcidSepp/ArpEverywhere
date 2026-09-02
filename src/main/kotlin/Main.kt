import javax.sound.midi.*
import javax.sound.midi.ShortMessage.NOTE_OFF
import javax.sound.midi.ShortMessage.NOTE_ON

fun main() {
    println("ALL MIDI DEVICES:")
    MidiSystem.getMidiDeviceInfo().map {
        MidiSystem.getMidiDevice(it)
    }.forEach {
        println("Name: ${it.deviceInfo.name} Desc: ${it.deviceInfo.description}")
        println("MaxReceivers: ${it.maxReceivers} MaxTransmitters: ${it.maxTransmitters}")
        println()
    }
    println("------")

    val notesActuallyHeld = mutableListOf<Byte>()
    val notesSustained = mutableListOf<Byte>()

    val mixerOutputDevice = getOutputDevice("minilogue")
    mixerOutputDevice.open()

    Runtime.getRuntime().addShutdownHook(object : Thread() {
        override fun run() {
            for (i in 0 until 127) {
                println("All notes off!")
                mixerOutputDevice.receiver.send(ShortMessage(NOTE_OFF, i, 127))
            }
        }
    })

    val mixerInputDevice = getInputDevice("minilogue")
    mixerInputDevice.transmitter.receiver = object : Receiver {
        override fun send(message: MidiMessage, timeStamp: Long) {
            if (message.message[0].toUByte() == NOTE_ON.toUByte()) {
                println("NOTE ON: ${message.message[1]}")

                // if no notes are held, the player is inputting a new chord
                if (notesActuallyHeld.isEmpty()) {
                    notesSustained.forEach {
                        mixerOutputDevice.receiver.send(ShortMessage(NOTE_OFF, it.toInt(), 127))
                    }
                    notesSustained.clear()
                }

                notesActuallyHeld.add(message.message[1])
                notesSustained.add(message.message[1])

                mixerOutputDevice.receiver.send(ShortMessage(NOTE_ON, message.message[1].toInt(), 127))
                println("Notes sustained: $notesSustained")
                println("Notes actually held: $notesActuallyHeld")
            }
            if (message.message[0].toUByte() == NOTE_OFF.toUByte()) {
                println("NOTE OFF: ${message.message[1]}")
                notesActuallyHeld.remove(message.message[1])

                println("Notes sustained: $notesSustained")
                println("Notes actually held: $notesActuallyHeld")
            }
        }

        override fun close() {
            TODO("Not yet implemented")
        }
    }
    mixerInputDevice.open()

}

