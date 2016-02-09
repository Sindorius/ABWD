import pygame
import json
import os

def get_color_key(filename):
    file = open(filename)
    result = json.loads(file.read())
    file.close()
    return result

def new_image(image, name, colors):
    pic = pygame.image.load(image)
    pixel_array = pygame.PixelArray(pic)

    for (c1, c2) in colors.items():
        c1 = [int(x) for x in c1.split(' ')]
        c2 = [int(x) for x in c2.split(' ')]
        original = pygame.Color(c1[0], c1[1], c1[2])
        replacement = pygame.Color(c2[0], c2[1], c2[2])
        pixel_array.replace(original, replacement)
    pygame.image.save(pixel_array.make_surface(), name)

def get_colors(json_key):
    result = dict()
    items = json_key['replace']
    groups = items.keys()
    for group in groups:
        for item in items[group]:
            result[item] = items[group][item]
    return result
    
if __name__ == "__main__":
    inv_dir = "./inv/"
    key = get_color_key("key.json")
    names = list(key)
    files = os.listdir(inv_dir)
    files = ["char_default_idle0.png", "char_default_idle1.png"]
    for file in files:
        for name in names:
            new_name = file.replace("default", name)
            new_image(inv_dir + file, new_name, get_colors(key[name]))
    print("it's done")
