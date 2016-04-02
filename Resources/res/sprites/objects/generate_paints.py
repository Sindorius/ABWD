import pygame
import json
import os
import sys

ORDER = ['red1',  'blue1', 'orange', 'yellow1', 'black',
         'blue2', 'blue3',
         'green1', 'green2', 'green3',
         'white', 'red2', 'grey1', 'grey2', 'purple1']

CRACK_WHITE = {
	'red1'     : 0,
	'blue1'    : 1,
	'orange'   : 0,
	'yellow1'  : 0,
	'black'    : 1,
	'blue2'    : 1,
	'blue3'    : 1,
	'green1'   : 1,
	'green2'   : 0,
	'green3'   : 0,
	'white'    : 0,
	'red2'     : 0,
	'grey1'    : 0,
	'grey2'    : 0,
	'purple1'  : 0
    }

WET_WHITE = {
	'red1'     : 1,
	'blue1'    : 1,
	'orange'   : 1,
	'yellow1'  : 0,
	'black'    : 1,
	'blue2'    : 1,
	'blue3'    : 1,
	'green1'   : 1,
	'green2'   : 1,
	'green3'   : 0,
	'white'    : 0,
	'red2'     : 1,
	'grey1'    : 1,
	'grey2'    : 0,
	'purple1'  : 1
    }

DEFAULT = pygame.Color(255, 0, 0)
TILE_DIM = 24

def get_color_key(filename):
    file = open(filename)
    result = json.loads(file.read())
    file.close()
    return result

def _overlay(pic, image):
    overlay = pygame.image.load(image)
    pic.blit(overlay, (0, 0))

def _paint(image, name, color):
    pic = pygame.image.load(image)
    _fill(pic, color)
    pygame.image.save(pic, name)

def _bucket(image, color):
    pic = pygame.image.load(image)
    color = pygame.Color(color[0], color[1], color[2])
    pixel_array = pygame.PixelArray(pic)
    pixel_array.replace(DEFAULT, color)
    return pixel_array.make_surface()

def _fill(surface, color):
    color = pygame.Color(color[0], color[1], color[2])
    surface.fill(color)

def generate_tiles(inv_dir, color_name, colors):
    save_tile(inv_dir, color_name, colors, True, False)
    save_tile(inv_dir, color_name, colors, True, True)
    save_tile(inv_dir, color_name, colors, False, False)
    save_tile(inv_dir, color_name, colors, False, True)
    
def save_tile(inv_dir, color_name, colors, correct, wet):
    correct_string = "" if correct else "in"
    dry_string = "wet" if wet else "dry"
    crack_string = "light" if CRACK_WHITE[color_name] else "dark"
    wet_string = "light" if WET_WHITE[color_name] else "dark"
    
    name = "tile_{}correct_{}_{}.png".format(correct_string, dry_string, color_name)
    
    pic = pygame.Surface((TILE_DIM, TILE_DIM))
    _fill(pic, colors)
    if wet:
        _overlay(pic, inv_dir + "tile_default_paint_{}_{}.png".format(dry_string, wet_string))  
    else:
        _overlay(pic, inv_dir + "tile_default_paint_{}.png".format(dry_string))
    if not correct:
        _overlay(pic, inv_dir + "tile_incorrect_{}.png".format(crack_string))
    pygame.image.save(pic, name)

if __name__ == "__main__":
    screen = pygame.display.set_mode((0, 0), 0, 32)
    inv_dir = "./paint bases/"
    key = get_color_key("paints.json")
    files = os.listdir(inv_dir)
    bucket_image = pygame.Surface((TILE_DIM * len(ORDER), TILE_DIM), pygame.SRCALPHA, 32)
    bucket_image.convert_alpha()
    bucket_counter = 0
    to_generate = [
        "bucket",
        "tiles"
        ]
    for color in ORDER:
        for item in to_generate:
            if item == "bucket":
                colored_bucket = _bucket(inv_dir + "bucket_default.png", key[color])
                bucket_image.blit(colored_bucket, (bucket_counter * TILE_DIM, 0))
                bucket_counter += 1
            elif "tile" in item:
                name = item.replace("default", color)
                new_tiles = generate_tiles(inv_dir, color, key[color])
    pygame.image.save(bucket_image, "../buckets.png")
    pygame.quit()
    sys.exit()
    print("it's done")
