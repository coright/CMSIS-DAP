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
from yaml_parser import parse_yaml, get_project_name

class Uvision4(Exporter):
    NAME = 'uVision4'

    def __init__(self):
        self.data = []

    def expand_data(self, new_data, old_data, attribute, group):
        # uvision needs filename plus path separately, expand data
        if group:
            for file in old_data[group]:
                if file:
                    new_file = {"path" : file, "name" : basename(file)}
                    new_data[attribute].append(new_file)

    # interface_mcu, project_name, data
    def generate(self, target, project_name, ctx):
        expanded_dic = ctx.copy();
        expanded_dic['source_files_c'] = []
        expanded_dic['source_files_cpp'] = []
        expanded_dic['source_files_s'] = []

        for dic in ctx['source_files_c']:
            for k,v in dic.items():
                group = k
                self.expand_data(expanded_dic, dic, 'source_files_c', group)

        for dic in ctx['source_files_cpp']:
            for k,v in dic.items():
                group = k
                self.expand_data(expanded_dic, dic, 'source_files_cpp', group)

        for dic in ctx['source_files_s']:
            for k,v in dic.items():
                group = k
                self.expand_data(expanded_dic, dic, 'source_files_s', group)

        print expanded_dic
        # Project file
        self.gen_file('uvision4_%s.uvproj.tmpl' % target, expanded_dic, '%s.uvproj' % project_name)
        self.gen_file('uvision4_%s.uvopt.tmpl' % target, expanded_dic, '%s.uvopt' % project_name)
