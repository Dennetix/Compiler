def buckaroo_cell(package): 
  cell = native.read_config('buckaroo', package, '').strip()
  if cell == '': 
    fail('Buckaroo does not have "' + package + '" installed. ')
  return cell

def buckaroo_deps(): 
  raw = native.read_config('buckaroo', 'dependencies', '').split(' ')
  return [ x.strip() for x in raw if len(x.strip()) > 0 ]

def buckaroo_deps_from_package(package): 
  cell = buckaroo_cell(package)
  all_deps = buckaroo_deps()
  return [ x for x in all_deps if x.startswith(cell) ]
