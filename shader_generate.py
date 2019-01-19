import os
import shutil
import sys

def RemoveShaderFiles(path):
    list = os.listdir(path)
    for i in range(0, len(list)):
        ext = os.path.splitext(list[i])
        print(ext[1])
        if (ext[1] == ".vs") or (ext[1] == ".fs"):
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
    current_path = os.getcwd()
    current_path = current_path[:current_path.find('build', 1)]
    print(current_path)

    os.chdir(current_path)

    shader_dir = current_path + 'shader'
    bin_dir = current_path + 'bin' + os.path.sep + 'shader'
    include_path = shader_dir+os.path.sep+'include'

    isExists = os.path.exists(bin_dir)
    if not isExists:
        os.makedirs(bin_dir)

    RemoveShaderFiles(bin_dir)
    RemoveShaderFiles(shader_dir)
    GenerateShaderFiles(shader_dir, include_path)

