import os
def _change_file(filename, to_vs):
    file = open(filename)
    txt = file.read()
    file.close()
    if to_vs:
        txt = txt.replace("../sprites/", "./res/sprites/")
    else:
        txt = txt.replace("./res/sprites/", "../sprites/")
    file = open(filename, "w")
    file.write(txt)
    file.close()

def _all_tmx():
    files = os.listdir(".")
    return [f for f in files if f[-4:] == ".tmx"]
    
    
def change_to_tiled(filename):
    _change_file(filename, False)

def change_to_vs(filename):
    _change_file(filename, True)

def flip_all_to_vs():
     for file in _all_tmx():
        change_to_vs(file)

def flip_all_to_tiled():
    for file in _all_tmx():
        change_to_tiled(file)



""" End of file quick ref """
# change_to_tiled(filename):
# change_to_vs(filename)
# flip_all_to_tiled()
# flip_all_to_vs()


flip_all_to_vs()

