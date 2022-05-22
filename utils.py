from os import listdir
from os.path import isfile, join
import importlib.util
import sys
from slitherbots import Snake

def get_snakes():
    snake_files = [f for f in listdir("users") if isfile(join("users", f))]
    snakes = []
    for snake_file in snake_files:
        spec = importlib.util.spec_from_file_location(snake_file, join("users", snake_file))
        module = importlib.util.module_from_spec(spec)
        sys.modules[spec.name] = module 
        spec.loader.exec_module(module)
        snake = Snake(snake_file[:-3],module.step)
        snakes.append(snake)
    return snakes

