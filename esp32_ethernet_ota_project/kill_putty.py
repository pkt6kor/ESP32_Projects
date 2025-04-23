import subprocess

def before_upload(*args, **kwargs):
    print("🛑 Closing existing PuTTY sessions...")
    try:
        subprocess.run(["taskkill", "/IM", "putty.exe", "/F"], check=True)
        print("✅ PuTTY sessions closed.")
    except subprocess.CalledProcessError:
        print("⚠️ PuTTY not running or already closed.")

before_upload()
