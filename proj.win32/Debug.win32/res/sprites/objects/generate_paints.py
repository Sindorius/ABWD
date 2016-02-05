import pygame
import json
import os
import sys

ORDER = ['black',
         'blue1', 'blue2', 'blue3',
         'green1', 'green2', 'green3',
         'orange', 'red1', 'yellow1']

ORDER = ['red1',  'blue1', 'orange', 'yellow1', 'black',
         'blue2', 'blue3',
         'green1', 'green2', 'green3']

DEFAULT = pygame.Color(255, 0, 0)
TILE_DIM = 24
def get_color_key(filename):
    file = open(filename)
    result = json.loads(file.read())
    file.close()
    return result

def new_image(image, name, color):
    if "_bucket" in name:
        _bucket(image, name, color)
    elif "correct" in name:
        _overlay(image, name, color)
    elif "_paint" in name:
        _paint(image, name, color)
    else:
        pass

def _overlay(image, name, color):
    pic = pygame.Surface((TILE_DIM, TILE_DIM))
    _fill(pic, color)
    overlay = pygame.image.load(image)
    pic.blit(overlay, (0, 0))
    pygame.image.save(pic, name)

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

if __name__ == "__main__":
    screen = pygame.display.set_mode((0, 0), 0, 32)
    inv_dir = "./paint bases/"
    key = get_color_key("paints.json")
    files = os.listdir(inv_dir)
    bucket_image = pygame.Surface((TILE_DIM * len(ORDER), TILE_DIM), pygame.SRCALPHA, 32)
    bucket_image.convert_alpha()
    bucket_counter = 0
    for file in files:
        for name in ORDER:
            if file != "bucket_default.png":
                new_name = file.replace("default", name)
                new_image(inv_dir + file, new_name, key[name])
            else:
                colored_bucket = _bucket(inv_dir + file, key[name])
                bucket_image.blit(colored_bucket, (bucket_counter * TILE_DIM, 0))
                bucket_counter += 1
    pygame.image.save(bucket_image, "../buckets.png")
    pygame.quit()
    sys.exit()
    print("it's done")
