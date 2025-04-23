import subprocess

putty_path = r"C:\\Program Files\\PuTTY\\putty.exe"  # Adjust path if PuTTY is elsewhere

env_sessions = {
    "Board_A": "ETHERNET_A",
    "Board_B": "ETHERNET_B"
}

def after_upload(source, target, env):
    env_name = env["PIOENV"]
    session = env_sessions.get(env_name)

    if session:
        print(f"🚀 Launching PuTTY session: {session}")
        try:
            subprocess.Popen([putty_path, "-load", session])
        except Exception as e:
            print(f"❌ Failed to launch PuTTY: {e}")
    else:
        print("⚠️ No PuTTY session mapped for this environment.")
