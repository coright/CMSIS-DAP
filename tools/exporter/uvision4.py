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
import sys

class Uvision4(Exporter):
    NAME = 'uVision4'

    def __init__(self):
        self.data = []

    def expand_data(self, new_data, old_data, attribute, group):

        # new_data[attribute] = []
        # uvision needs filename plus path separately, expand data
        # print old_data
        if group:
            # print group
            # print old_data[attribute][group]
            # new_data[attribute][group] = []
            for file in old_data[group]:
                # print file
                if file:
                    new_file = {"path" : file, "name" : basename(file), "group" : group}
                    new_data[attribute].append(new_file)
        # print new_data[attribute]

    # interface_mcu, project_name, data
    def generate(self, target, project_name, ctx):
        expanded_dic = ctx.copy();
        expanded_dic['source_files_c'] = []
        expanded_dic['source_files_cpp'] = []
        expanded_dic['source_files_s'] = []
        for dic in ctx['source_files_c']:
            # print dic
            for k,v in dic.items():
                group = k
                # print "Old \n"
                self.expand_data(expanded_dic, dic, 'source_files_c', group)
                # print "New \n"
                # print expanded_dic
        for dic in ctx['source_files_cpp']:
            # print dic
            for k,v in dic.items():
                group = k
                # print "Old \n"
                self.expand_data(expanded_dic, dic, 'source_files_cpp', group)
                # print "New \n"
                # print expanded_dic
        for dic in ctx['source_files_s']:
            # print dic
            for k,v in dic.items():
                group = k
                # print "Old \n"
                self.expand_data(expanded_dic, dic, 'source_files_s', group)
                # print "New \n"
                # print expanded_dic\

        # print expanded_dic
        # sys.exit()
        # print target
        # Project file
        self.gen_file('uvision4_%s.uvproj.tmpl' % target, expanded_dic, '%s.uvproj' % project_name)
        self.gen_file('uvision4_%s.uvopt.tmpl' % target, expanded_dic, '%s.uvopt' % project_name)
