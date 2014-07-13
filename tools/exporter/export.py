from optparse import OptionParser
import yaml
import logging
import os
from yaml_parser import parse_yaml
from uvision4 import Uvision4

if __name__ == '__main__':
    logging.basicConfig(level=logging.INFO)
    # Parse Options
    parser = OptionParser()

    (options, args) = parser.parse_args()

    # get configuration from the YAML file
    f_boot = open('../records/bootloader_k20.yaml')
    f_flash = open('../records/flash_algo_k20.yaml')
    f_uvision = open('../records/uvision.yaml')
    f_boot_common = open('../records/bootloader_common.yaml')
    f_ubs = open('../records/usb.yaml')
    f_rtos = open('../records/rtos.yaml')

    config = yaml.load(f_boot)
    config.update(yaml.load(f_uvision))
    config.update(yaml.load(f_boot_common))
    config.update(yaml.load(f_ubs))
    config.update(yaml.load(f_rtos))
    config.update(yaml.load(f_flash))

    f_boot.close()
    f_uvision.close()
    f_boot_common.close()
    f_ubs.close()
    f_rtos.close()

    ctx = parse_yaml(config)
    exporter = Uvision4()
    #run exporter for defined bootloader project
    exporter.generate('k20dx128', 'k20_bootloader', ctx)
