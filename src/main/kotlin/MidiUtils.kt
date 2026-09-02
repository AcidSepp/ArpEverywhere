import javax.sound.midi.MidiDevice
import javax.sound.midi.MidiMessage
import javax.sound.midi.MidiSystem
import javax.sound.midi.Receiver
import javax.sound.midi.SysexMessage
import kotlin.text.toHexString

fun getOutputDevice(outputDeviceName: String): MidiDevice {
    var outputDevice: MidiDevice? = null
    while (outputDevice == null) {
        outputDevice = MidiSystem.getMidiDeviceInfo().map {
            MidiSystem.getMidiDevice(it)
        }.filter {
            it.maxReceivers != 0
        }.lastOrNull {
            it.deviceInfo.name.contains(outputDeviceName)
        }
        if (outputDevice != null) {
            outputDevice.open()
            return outputDevice
        }
    }
    throw RuntimeException()
}

fun getInputDevice(inputDeviceName: String): MidiDevice {
    var inputDevice: MidiDevice? = null
    while (inputDevice == null) {
        inputDevice = MidiSystem.getMidiDeviceInfo().map {
            MidiSystem.getMidiDevice(it)
        }.filter {
            it.maxTransmitters != 0
        }.lastOrNull {
            it.deviceInfo.name.contains(inputDeviceName)
        }
        if (inputDevice != null) {
            inputDevice.open()
            return inputDevice
        }
    }
    throw RuntimeException()
}

fun Receiver.send(midiMessage: MidiMessage) {
    send(midiMessage, -1)
}

fun MidiMessage.toHexString(): String = message.joinToString(
    prefix = "(", postfix = ")", separator = ","
) { "0x" + it.toHexString() }


fun sysExMessageOf(vararg intArray: Int): SysexMessage {
    val bytes = intArray.map { it.toByte() }
    return SysexMessage(bytes.toByteArray(), bytes.size)
}