import sys
import numpy
from PIL import Image

if len(sys.argv) < 2:
    print("Expected image file as input")
    sys.exit(-1)

image_path = sys.argv[1]

use_atlas = "atlas" in sys.argv;

sprite_size = 8
positions = [
    ("WIRE_VERTICAL", 0, 0),
    ("WIRE_HORIZONTAL", 8, 0),

    ("WIRE_BEND_TOP_RIGHT", 16, 0),
    ("WIRE_BEND_BOTTOM_RIGHT", 24, 0),
    ("WIRE_BEND_BOTTOM_LEFT", 32, 0),
    ("WIRE_BEND_TOP_LEFT", 40, 0),

    ("WIRE_T_TOP", 48, 0),
    ("WIRE_T_RIGHT", 56, 0),
    ("WIRE_T_BOTTOM", 0, 8),
    ("WIRE_T_LEFT", 8, 8),

    ("WIRE_CROSS", 16, 8),

    ("WIRE_ARROW_DOWN", 24, 8),
    ("WIRE_ARROW_LEFT", 32, 8),
    ("WIRE_ARROW_UP", 40, 8),
    ("WIRE_ARROW_RIGHT", 48, 8),

    ("SELECTION_HOVER", 56, 8),
    ("SELECTION_DELETE", 56, 16),

    ("LED_OFF", 0, 16),
    ("LED_ON", 8, 16),

    ("GATE_AND", 0, 24),
    ("GATE_OR", 8, 24),
    ("GATE_NOT", 16, 24),
    ("GATE_XOR", 24, 24)
]

definitions = []


header = f"#ifndef SPRITEDATA_H\n#define SPRITEDATA_H\n#define SPRITE_SIZE {sprite_size}"
footer = "#endif"

def get_color_string(image: Image):
    rgba = lambda arr: arr[0] << 24 | arr[1] << 16 | arr[2] << 8 | arr[3]
    width, height = image.size
    pixel_count = width * height
    raw = numpy.array(image).ravel()
    chunks = list(numpy.split(raw, pixel_count))
    shifted = [rgba(chunk) for chunk in chunks]
    return ", ".join([hex(color) for color in shifted])

with Image.open(image_path) as im:
    if use_atlas:
        colors = get_color_string(im)
        body = f"const int ATLAS[{64 * 64}] = \u007b{colors}\u007d;"
    else:
        for name, x, y in positions:
            rect = (
                x * sprite_size,
                y * sprite_size,
                (x + 1) * sprite_size,
                (y + 1) * sprite_size,
            )
            sprite_region = im.crop(rect)
            colors = get_color_string(sprite_region)
            definitions.append(f"const int SPRITE_{name}[] = \u007b{colors}\u007d;")
        
        body = '\n'.join(definitions)
        
print(f"{header}\n{body}\n{footer}")
