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
    key = get_color_key("key.json")
    files = ['pteradactyl_left0.png', 'pteradactyl_left1.png',
         'pteradactyl_left2.png', 'pteradactyl_left3.png',
         'pteradactyl_left4.png', 'pteradactyl_left5.png',
         'pteradactyl_left6.png', 'pteradactyl_right0.png',
         'pteradactyl_right1.png', 'pteradactyl_right2.png',
         'pteradactyl_right3.png', 'pteradactyl_right4.png',
         'pteradactyl_right5.png', 'pteradactyl_right6.png']
    for file in files:
        new_name = "angry_" + file
        new_image(file, new_name, key)
    print("it's done")
