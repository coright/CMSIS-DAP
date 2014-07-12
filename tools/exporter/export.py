from optparse import OptionParser
import yaml
import logging
import os
from yaml_parser import parse_yaml
from uvision4 import Uvision4

#from workspace_tools.bootloader import BOOTLOADER_TARGETS

# class Loader(yaml.Loader):

#     def __init__(self, stream):

#         self._root = os.path.split(stream.name)[0]

#         super(Loader, self).__init__(stream)

#     def include(self, node):

#         filename = os.path.join(self._root, self.construct_scalar(node))

#         with open(filename, 'r') as f:
#             return yaml.load(f, Loader)

#Loader.add_constructor('!include', Loader.include)

if __name__ == '__main__':
    logging.basicConfig(level=logging.INFO)
    # Parse Options
    parser = OptionParser()


#    parser.add_option("-b", "--bootloader", metavar="MCU", default='K20',
#        help="bootloader project build (%s)" % ', '.join(BOOTLOADER_TARGETS))

    (options, args) = parser.parse_args()

    # get configuration from the YAML file
    f_boot = open('../records/bootloader_k20.yaml')
    f_flash = open('../records/flash_algo_k20.yaml')
    f_uvision = open('../records/uvision.yaml')
    f_boot_common = open('../records/bootloader_common.yaml')
    f_ubs = open('../records/usb.yaml')
    f_rtos = open('../records/rtos.yaml')

    # config = yaml.load(f_boot, Loader)
    config = yaml.load(f_boot)
    config.update(yaml.load(f_uvision))
    config.update(yaml.load(f_boot_common))
    config.update(yaml.load(f_ubs))
    config.update(yaml.load(f_rtos))
    config.update(yaml.load(f_flash))

    #logging.info(config)
    # for data in config:
    #print config

    f_boot.close()
    f_uvision.close()
    f_boot_common.close()
    f_ubs.close()
    f_rtos.close()

    ctx = parse_yaml(config)
    exporter = Uvision4()
    #run exporter for defined bootloader project
    exporter.generate('k20dx128', 'k20_bootloader', ctx)
