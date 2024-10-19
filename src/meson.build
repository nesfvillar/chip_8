project('chip_8', 'cpp',
  default_options : ['cpp_std=c++23', 'warning_level=3'])

src = ['main.cpp', 'emulator.cpp']

dependencies = [dependency('libadwaita-1')]

executable('chip_8', src, dependencies: dependencies)
