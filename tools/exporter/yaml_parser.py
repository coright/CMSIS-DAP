from compiler.ast import flatten
import sys

def parse_yaml(dic):
    ctx = {
        'name': '' ,
        'mcu' : '',
        'include-paths': [],
        'scatter_file': '',
        'source_files_c': {},
        'source_files_cpp': {},
        'source_files_s': {},
        'source_files_obj': [],
        'source_files_lib': [],
        'symbols': [],
        'flags' : [],
    }
    #print '\n'
    # get name
    ctx['name'] = get_project_name(dic)
    #print ctx['name']
    # get include paths
    ctx['include-paths'] = get_include_paths(dic)
    #print ctx['include-paths']
    # get linker file
    ctx['scatter_file'] = get_scatter_file(dic)
    #print ctx['scatter_file']
    # get source files
    virtual_dir = get_virtual_dir(dic)
    # if virtual_dir:
    ctx['source_files_c'][virtual_dir] = {}
    ctx['source_files_c'][virtual_dir] = get_source_files_by_extension(dic, 'c')
    # else:
    #     ctx['source_files_c'][virtual_dir] = get_source_files_by_extension(dic, 'c')

    ctx['source_files_cpp'][virtual_dir] = {}
    ctx['source_files_cpp'][virtual_dir] = get_source_files_by_extension(dic, 'cpp')

    # need to consider all object names (.asm, .s)
    ctx['source_files_s'][virtual_dir] = {}
    ctx['source_files_s'][virtual_dir] = get_source_files_by_extension(dic, 's')

    # need to consider all object names (.o, .obj)
    ctx['source_files_obj'] = get_source_files_by_extension(dic, 'o')
    ctx['source_files_obj'].append(get_source_files_by_extension(dic, 'obj'))
    # need to consider all library names (.lib, .ar)
    ctx['source_files_lib'] = get_source_files_by_extension(dic, 'lib')
    ctx['source_files_lib'].append (get_source_files_by_extension(dic, 'ar'))
    ctx['source_files_lib'].append (get_source_files_by_extension(dic, 'a'))
    # print ctx['source_files_c']
    # get symbols
    ctx['symbols'] = get_macros(dic)
    #print ctx['symbols']
    # get flags
    ctx['flags'] = get_cc_flags(dic)
    ctx['mcu'] = _finditem(dic, 'mcu')
    return ctx

def get_cc_flags(dic):
    return _finditem(dic, 'cc-flags')

def get_project_name(dic):
    return _finditem(dic, 'project-name')

def get_project_name_list(dic_list):
    for dic in dic_list:
        result = _finditem(dic, 'project-name')
        # print result
        # print dic
        if result:
            return result
    return None

def parse_list_yaml(project_list):
    ctx = {
        'name': '' ,
        'mcu' : '',
        'include_paths': [],
        'scatter_file': '',
        'source_files_c': [],
        'source_files_cpp': [],
        'source_files_s': [],
        'source_files_obj': [],
        'source_files_lib': [],
        'symbols': [],
        'flags' : [],
    }

    for dic in project_list:
        name = _finditem(dic, 'name') #TODO fix naming
        if name:
            ctx['name'] = name
        mcu = name = _finditem(dic, 'mcu') #TODO fix naming
        if mcu:
            ctx['mcu'] = mcu
        include_paths = get_include_paths(dic)
        if include_paths:
            ctx['include_paths'].append(include_paths)
        scatter_file = _finditem(dic, 'scatter_file')
        if scatter_file:
            ctx['scatter_file'] = scatter_file
        source_c = find_all_values(dic, 'source_files_c')
        if source_c:
            ctx['source_files_c'].append(source_c)
        source_cpp = find_all_values(dic, 'source_files_cpp')
        if source_cpp:
            ctx['source_files_cpp'].append(source_cpp)
        source_s = find_all_values(dic, 'source_files_s')
        if source_s:
            ctx['source_files_s'].append(source_s)
        source_obj = find_all_values(dic, 'source_files_obj')
        if source_obj:
            ctx['source_files_obj'].append(source_obj)
        source_lib = find_all_values(dic, 'source_files_lib')
        if source_lib:
            ctx['source_files_lib'].append(source_lib)

        symbols = find_all_values(dic, 'symbols')
        if symbols:
            ctx['symbols'].append(symbols)
        flags = find_all_values(dic, 'flags')
        if flags:
            ctx['flags'].append(flags)

    ctx['flags'] = flatten(ctx['flags'])
    ctx['symbols'] = flatten(ctx['symbols'])
    ctx['include_paths'] = flatten(ctx['include_paths'])
    return ctx

def get_macros(dic):
    return _finditem(dic, 'macros')

def get_include_paths(dic):
    paths_list = find_all_values(dic, 'include-paths')
    paths = flatten(paths_list)
    return paths

def get_source_files_by_extension(dic, extension):
    find_extension = 'source-files-' + extension
    source_list = find_all_values(dic, find_extension)
    source = flatten(source_list)
    return source

def find_all_values(obj, key):
    files = []
    if key in obj:
        return obj[key]
    for k, v in obj.items():
        if isinstance(v,dict):
            item = find_all_values(v, key)
            if item is not None:
                files.append(item)
    return files

def _finditem(obj, key):
    if key in obj:
        return obj[key]
    for k, v in obj.items():
        if isinstance(v,dict):
            item = _finditem(v, key)
            if item is not None:
                return item

def get_scatter_file(dic):
    return _finditem(dic, 'linker-file')

def get_virtual_dir(dic):
    return _finditem(dic, 'virtual-dir')

def get_project_files(dic, name):
    return flatten(find_all_values(dic, name))

def get_mcu(dic_list):
    for dic in dic_list:
        result = _finditem(dic, 'mcu')
        if result:
            return result
    return None
