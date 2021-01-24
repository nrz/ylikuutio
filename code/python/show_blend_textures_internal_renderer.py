#!/usr/bin/python3

# Data preprocessing script for printing information about
# the textures used by the Blender internal renderer.
#
# Copyright (C) 2015-2021 Antti Nuortimo.
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
# 1. Show the textures used by internal renderer.

import os
import bpy

# print all objects.
print("Objects (bpy.data.objects):")

print("Objects and their materials:")
for obj in bpy.data.objects:
    print("Object: " + obj.name)
    for material in obj.material_slots:
        print("Material: " + material.name)

print("Materials (bpy.data.materials):")

for material in bpy.data.materials:
    # print("Material: " + material.name)
    for texture_slot in material.texture_slots:
        if texture_slot is None:
            continue
        # print("Texture slot: " + texture_slot.name)
        if texture_slot.texture is None:
            continue
        if texture_slot.texture.image is None:
            continue
        if texture_slot.texture.image.filepath is None:
            continue
        old_filepath = texture_slot.texture.image.filepath
        print("Old filepath: " + old_filepath) # This is the filename, may need some processing.
        old_filename = os.path.basename(old_filepath)
        print("Old filename: " + old_filename) # This is the filename, may need some processing.
