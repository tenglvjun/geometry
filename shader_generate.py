import os
import shutil
import sys

def RemoveShaderFiles(path):
    list = os.listdir(path)
    for i in range(0, len(list)):
        ext = os.path.splitext(path)
        if (ext == ".vs") or (ext == ".fs"):
            os.remove(os.path.join(path, list[i]))

def GenerateShaderFiles(path, include):
    shader_list = []
    list = os.listdir(path)
    for i in range(0, len(list)):
        path = os.path.join(shader_dir, list[i])
        if os.path.isfile(path):
            input_file = path
            output_file = path.replace('.m4', '')
            os.system('m4 -I ' + include + ' ' +
                    input_file + ' > ' + output_file)
            shader_list.append(output_file)

    for i in range(0, len(shader_list)):
        shutil.move(shader_list[i], bin_dir)


if __name__ == "__main__":
    shader_dir = 'shader'
    bin_dir = 'bin/shader'
    include_path = shader_dir+os.path.sep+'include'

    isExists = os.path.exists(bin_dir)
    if not isExists:
        os.makedirs(bin_dir)

    RemoveShaderFiles(shader_dir)
    GenerateShaderFiles(shader_dir, include_path)

