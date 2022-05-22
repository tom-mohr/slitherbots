from os import listdir
from os.path import isfile, join
MODULE_PATH = "/path/to/your/module/__init__.py"
MODULE_NAME = "mymodule"
import importlib.util
import sys


def get_users():
    user_files = [f for f in listdir("users") if isfile(join("users", f))]
    users = []
    for f in user_files:
        spec = importlib.util.spec_from_file_location(f, join("users", f))
        module = importlib.util.module_from_spec(spec)
        sys.modules[spec.name] = module 
        spec.loader.exec_module(module)
        users.append((f[:-3],module.step))
    return users

