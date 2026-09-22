# After an upload the board resets and its serial port is re-created. udev needs a
# moment to apply permissions, so opening the monitor right away fails with EACCES.
# Wait until the port can actually be opened before PlatformIO continues.
import glob
import os
import time

Import("env")


def wait_for_port(source, target, env):
    deadline = time.time() + 10
    time.sleep(0.5)
    while time.time() < deadline:
        for port in glob.glob("/dev/ttyACM*") + glob.glob("/dev/ttyUSB*"):
            try:
                os.close(os.open(port, os.O_RDWR | os.O_NONBLOCK | os.O_NOCTTY))
                return
            except OSError:
                pass
        time.sleep(0.2)
    print("Warning: serial port not accessible after upload")


env.AddPostAction("upload", wait_for_port)
