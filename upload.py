Import("env")

env.Replace(
    UPLOADERFLAGS=[
        "-v",
        "-patmega4809",
        "-cwiring",
        "-P/dev/cu.usbmodem2101",  # <== Replace with your actual port
        "-b115200",
        "-D",
        "-Uflash:w:$SOURCE:i"
    ]
)
