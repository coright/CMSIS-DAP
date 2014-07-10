"""Just a template for subclassing"""
import uuid, shutil, os, logging, fnmatch
#from os import walk, remove
from os.path import join, dirname, isdir, split
#from copy import copy
from jinja2 import Template
#from contextlib import closing
#from zipfile import ZipFile, ZIP_DEFLATED

#from workspace_tools.utils import mkdir
#from workspace_tools.toolchains import TOOLCHAIN_CLASSES
#from workspace_tools.targets import TARGET_MAP

class OldLibrariesException(Exception): pass

class Exporter():
    TEMPLATE_DIR = dirname(__file__)
    DOT_IN_RELATIVE_PATH = False

    def __init__(self):
        self.data = []

    def gen_file(self, template_file, data, target_file):
        template_path = join(Exporter.TEMPLATE_DIR, template_file)
        template_text = open(template_path).read()
        template = Template(template_text)
        target_text = template.render(data)

        project_file_loc = '../../project_files'
        if not os.path.exists(project_file_loc):
            os.makedirs(project_file_loc)
        target_path = join(project_file_loc, target_file)
        logging.debug("Generating: %s" % target_path)
        open(target_path, "w").write(target_text)

