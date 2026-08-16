import subprocess

def build(compiler="g++"):
    if compiler == "cl":
        subprocess.run(["cl", "src/*.cpp", "/EHsc", "/std:c++17", "/Fe:flux"], shell=True)
    elif compiler in ["g++", "clang++"]:
        subprocess.run(f"{compiler} src/*.cpp -std=c++17 -o flux", shell=True)
    else:
        print(f"\nCompiler '{compiler}' not found.\n")


def execute(compiler="g++", executable="flux", filename="main.flxx", is_compiled=True):
    if is_compiled:
        subprocess.run([f"./{executable}", "run", filename])
    else:
        build(compiler)
        execute(compiler=compiler, filename=filename, is_compiled=True)

execute(filename="tests/flow.flxx")