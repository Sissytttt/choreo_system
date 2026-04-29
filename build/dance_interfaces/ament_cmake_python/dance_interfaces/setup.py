from setuptools import find_packages
from setuptools import setup

setup(
    name='dance_interfaces',
    version='0.0.0',
    packages=find_packages(
        include=('dance_interfaces', 'dance_interfaces.*')),
)
