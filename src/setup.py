from setuptools import setup

# Available at setup time due to pyproject.toml
from pybind11.setup_helpers import Pybind11Extension, build_ext

import sys

__version__ = "12.0.1"

# The main interface is through Pybind11Extension.
# * You can add cxx_std=11/14/17, and then build_ext can be removed.
# * You can set include_pybind11=false to add the include directory yourself,
#   say from a submodule.
#
# Note:
#   Sort input source files if you glob sources to ensure bit-for-bit
#   reproducible builds (https://github.com/pybind/python_example/pull/53)

ext_modules = [
    Pybind11Extension(
        'slitherbots',
        [
            'src/pybind_slither.cpp',
            'src/logic.cpp'
        ],
        include_dirs=[
            "include/"
        ],
        language='c++'
        ),
]

setup(
    name="slitherbots",
    version=__version__,
    author="Tom Mohr, Andreas Faust",
    author_email="",
    url="",
    description="slither",
    long_description="",
    ext_modules=ext_modules,
    extras_require={},
    # Currently, build_ext only provides an optional "highest supported C++
    # level" feature, but in the future it may provide more features.
    cmdclass={"build_ext": build_ext},
    zip_safe=False,
)

