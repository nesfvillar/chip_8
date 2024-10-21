project(
  'chip_8', 'cpp',
  version : '1.0.0',
  license: 'Apache-2.0',
  default_options : ['cpp_std=c++23', 'warning_level=3'],
)

src = [
  'main.cpp',
  'emulator.cpp',
]

dependencies = [
  dependency('libadwaita-1'),
]

executable(
  'chip_8',
  src,
  dependencies: dependencies,
)
