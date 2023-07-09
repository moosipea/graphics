import sys

if len(sys.argv) < 3:
    print("Expected vertex and fragment shader as input")
    sys.exit(-1)

print("#ifndef SHADERDATA_H\n#define SHADERDATA_H")

for path in sys.argv[1:3]:
    with open(path, "r") as file:
        name = path.removesuffix(".glsl").upper() + "_SOURCE"
        content = file.read().replace("\n", "\\n")
        print(f"const char *{name} = \"{content}\";")

print("#endif")