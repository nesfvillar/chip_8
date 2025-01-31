project(
  'chip_8',
  'cpp',
  version : '1.0.0',
  license : 'BSD-2-Clause',
  default_options : ['cpp_std=c++23', 'warning_level=3'],
)

src_files = [
  'src/main.cpp',
  'src/emulator.cpp',
  'src/instruction.cpp'
]

dependencies = [
  dependency('libadwaita-1'),
  dependency('gtkmm-4.0'),
]

executable(
  'chip_8',
  src_files,
  dependencies : dependencies,
)

