from optparse import OptionParser
import yaml
import logging
import os
from yaml_parser import parse_yaml, get_project_files, get_mcu
from uvision4 import Uvision4
import sys

def process_all_projects(dic):
    projects = []
    yaml_files = []
    for k,v in dic['projects'].items():
        projects.append(k);

    for project in projects:
        yaml_files = get_project_files(dic, project) # TODO fix list inside list
        for yaml_file in yaml_files[0]:              # accesing the first item as it's another list
            file = open(yaml_file)
            config.update(yaml.load(file))
            file.close()
        ctx = parse_yaml(config)
        exporter = Uvision4()
        #run exporter for defined bootloader project
        exporter.generate(get_mcu(dic), ctx['name'], ctx)

if __name__ == '__main__':
    logging.basicConfig(level=logging.DEBUG)
    os.chdir('../..') # always should be in the root directory for the project

    # Parse Options
    parser = OptionParser()
    parser.add_option("-f", "--file", help="Yaml projects file")

    (options, args) = parser.parse_args()

    if not options.file:
        print "No project file give. Please provide one. Exiting"
        sys.exit()

    print "Processing projects file."
    project_file = open(options.file)
    config = yaml.load(project_file)

    process_all_projects(config)
    project_file.close()
