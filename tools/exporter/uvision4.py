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


class Uvision4():
    NAME = 'uVision4'

    def __init__(self):

    def gen_file(self, template_file, data, target_file):
        template_text = open(template_file).read()
        template = Template(template_text)
        target_text = template.render(data)

        target_path = join('../erase/', target_file)
        open(target_path, "w").write(target_text)

    def generate(self, data, target, project_name):
        # target = self.target.lower()

        # Project file
        self.gen_file('uvision4_%s.uvproj.tmpl' % target, data, '%s.uvproj' % project_name)
        self.gen_file('uvision4_%s.uvopt.tmpl' % target, data, '%s.uvopt' % project_name)
