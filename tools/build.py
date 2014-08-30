#! /usr/bin/env python

# CMSIS-DAP Interface Firmware
# Copyright (c) 2009-2014 ARM Limited
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

from __future__ import print_function
import sys
import os
from os.path import join
from os.path import basename
import subprocess
import settings
import logging
from optparse import OptionParser


##
# @brief Class to build uVision projects.
class UV4Project(object):
    # Status codes from building a project.
    
    ## No warnings or errors.
    SUCCESS = 0
    ## Warnings only.
    WARNINGS = 1
    ## Fatal errors and possibly warnings.
    ERRORS = 2
    ## The request target does not exist.
    INVALID_TARGET = 3
    ## The project file does not exit.
    INVALID_PROJECT = 15
    
    ##
    # @brief Constructor.
    # @param self
    # @param project Path to the project file.
    def __init__(self, project):
        self.project = project
    
    ##
    # @brief Build a target of the project.
    #
    # @param self
    # @param target Name of the desired target to build. If not specified, or set to None, the
    #   currently selected target (in the GUI) will be built.
    # @param logFile Path to a file that the build log will be written to. The path is relative
    #   to the project file's directory. The log file will be created if it doesn't exist, and
    #   it will be overwritten if it does already exist.
    #
    # @return The integer status code from the uVision build.
    def build(self, target=None, logFile=None):
        # Build list of arguments to UV4.
        argList = [settings.UV4, '-r', '-j0', self.project]
        if target:
            argList += ['-t', target]
        if logFile:
            argList += ['-o', logFile]
        
        # Run UV4 command.
        return subprocess.call(argList)

##
# @brief Command line interface to UV4 builder.
class Builder(object):
    def __init__(self):
        self.rootPath = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
        self.projectPath = os.path.join(self.rootPath, 'generated_projects')
    
    def _build_project_list(self, tool):
        projects = []
        # projects are named the same as the dir without the toolchain name
        for dirpath, dirnames, files in os.walk(self.projectPath):
            for d in dirnames:
                if d.startswith(tool):
                    projects.append(d)
        return projects

    def run(self):
        # Build arg parser.
        parser = OptionParser()
        parser.add_option("-i", "--ide", help="Create project files for toolchain (uvision by default)")
        parser.add_option("-v", "--verbose", action="store_true", help="Print messages during builds")
        #parser.add_argument("-l", "--log", metavar="PATH", help="Specify the log file.")

        (options, args) = parser.parse_args()

        # set the default to uvision if not provided
        if not options.ide:
            options.ide = 'uvision'
            print("[WARNING] Building uVision projects by default")

        # Create a list of projects in the generator directory
        error_list = []
        build_list = self._build_project_list(options.ide)

        for k in build_list:
            project_name = k + '.uvproj'
            project_name = project_name.strip(options.ide + '_')
            path_plus_project = self.projectPath + '\\' + k + '\\' + project_name
            
            project = UV4Project(path_plus_project)
            print("Building project %s..." % (project_name))
            status = project.build(None, 'build_log.txt')
            
            if options.verbose:
                print("Status = %d" % status)
            if status != UV4Project.SUCCESS and status != UV4Project.WARNINGS:
                error_list.append(project_name)

        for e in error_list:
            print("\tFailed to build %s" % (e))

if __name__ == "__main__":
    exit(Builder().run())

