import subprocess
import sys
from pathlib import Path


def execute(filepath):
    res = subprocess.run(
        ["./flux", "run", f"tests/{filepath}"], capture_output=True, text=True
    )

    with open(f"tests/{filepath.replace('.flxx', '.txt')}") as f:
        expected = f.read()

    return res.stdout.strip() == expected.strip()


def test():
    files = [
        f.name
        for f in Path("./tests").iterdir()
        if f.is_file() and f.name.endswith(".flxx")
    ]
    for file in files:
        if execute(file) == False:
            return 1
    return 0


if __name__ == "__main__":
    if test() == 1:
        print("\nError detected during testing.")
        sys.exit(1)
    else:
        print("\nAll tests completed successfully.")
        sys.exit(0)
