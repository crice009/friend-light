from os import system

def after_upload(source, target, env):
    print("Starting monitor...")
    system("pio device monitor")

def init(env):
    env.AddPostAction("upload", after_upload)

Import("env") # this line is a PlatformIO API to access build environment
init(env) # this line uses python to do a thing to PlatformIO build environment