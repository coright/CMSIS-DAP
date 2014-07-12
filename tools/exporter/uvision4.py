"""
mbed SDK
Copyright (c) 2011-2013 ARM Limited

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
"""
from os.path import basename, join
from jinja2 import Template
from export_generator import Exporter
from yaml_parser import parse_yaml

class Uvision4(Exporter):
    NAME = 'uVision4'

    def __init__(self):
        self.data = []

    # interface_mcu, project_name, data
    def generate(self, target, project_name, data):

        expanded_dic = data.copy();
        expanded_dic['source_files_c'] = []

        # uvision needs filename plus path separately, expand data
        for file in data['source_files_c']:
            new_file = {"path" : file, "name" : basename(file)}
            expanded_dic['source_files_c'].append(new_file)

        # Project file
        self.gen_file('uvision4_%s.uvproj.tmpl' % target, expanded_dic, '%s.uvproj' % project_name)
        self.gen_file('uvision4_%s.uvopt.tmpl' % target, expanded_dic, '%s.uvopt' % project_name)
