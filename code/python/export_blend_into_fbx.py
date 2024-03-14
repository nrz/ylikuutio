#!/usr/bin/python3

# Data preprocessing script for converting .blend into .fbx.
#
# Copyright (C) 2015-2024 Antti Nuortimo.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

# This script does the following:
# 1. Unpack all data into local files.
# 2. Export data into an FBX file that is named after its parent directory.

import os
import bpy

# get the name of the directory where this 3D model file (.blend or something else) is located.
directory = os.path.basename(os.path.dirname(bpy.data.filepath))
new_filename = directory + ".fbx"
new_abs_filename = os.path.join(os.path.dirname(bpy.data.filepath), new_filename)
print("new_abs_filename: " + new_abs_filename)

# 1. Unpack all data into local files.
bpy.ops.file.unpack_all(method='WRITE_LOCAL')

# 2. Export data into an FBX file that is named after its parent directory.
bpy.ops.export_scene.fbx(
        filepath=new_abs_filename,
        check_existing=False,
        axis_forward='Z',
        axis_up='Y',
        use_selection=False)
