load('//:buckaroo_macros.bzl', 'buckaroo_deps')

cxx_binary(
  name = 'compiler',
  headers = glob([
    'src/**/*.h'
  ]),
  srcs = glob([
    'src/**/*.cpp'
  ]),
  deps = buckaroo_deps()
)
