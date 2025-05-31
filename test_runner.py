print("Test file for signaltools module — Projekt 3 — działa poprawnie")

import subprocess

def run_test(name, exe_path):
    print(f"Running test: {name}")
    result = subprocess.run([exe_path], capture_output=True, text=True)
    print(result.stdout)
    if result.returncode != 0:
        print("Test failed.")
    else:
        print("Test passed.")

if __name__ == "__main__":
    exe_path = "build/Release/projekt_main.exe"
    run_test("Main Program Execution", exe_path)
