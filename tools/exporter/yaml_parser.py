def parse_yaml(dic):
    ctx = {
        'name': '' ,
        'include_paths': [],
        'scatter_file': '',
        'source_files': [],
        'symbols': [],
        'flags' : [],
    }
    print '\n'
    # get name
    ctx['name'] = get_name(dic)
    #print ctx['name']
    # get include paths
    ctx['include_paths'] = get_include_paths(dic)
    #print ctx['include_paths']
    # get linker file
    ctx['scatter_file'] = get_scatter_file(dic)
    #print ctx['scatter_file']
    # get source files
    ctx['source_files'] = get_source_files(dic)
    # print ctx['source_files']
    # get symbols
    ctx['symbols'] = get_macros(dic)
    #print ctx['symbols']
    # get flags
    ctx['flags'] = get_cc_flags(dic)
    return ctx

def get_cc_flags(dic):
    return _finditem(dic, 'cc-flags')

def get_name(dic):
    return _finditem(dic, 'project-name')

def get_macros(dic):
    return _finditem(dic, 'macros')

def get_include_paths(dic):
    paths_list = find_all_values(dic, 'include-paths')
    paths = flatten(paths_list)
    return paths

def get_source_files(dic):
    source_list = find_all_values(dic, 'source-files')
    source = flatten(source_list)
    return source

def flatten(list_of_list):
    list = []
    for ll in list_of_list:
        for l in ll:
            list.append(l)
    return list

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
