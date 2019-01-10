import os
import shutil

current_path = os.path.dirname(__file__)
os.chdir(current_path)

shader_dir = 'shader'
bin_dir = 'bin/shader'

list = os.listdir(shader_dir)

include_path = shader_dir+os.path.sep+'include'

for i in range(0, len(list)):
    path = os.path.join(shader_dir, list[i])
    if os.path.isfile(path):
        input_file = path
        output_file = path.replace('.m4', '')
        os.system('m4 -I ' + include_path + ' ' +
                  input_file + ' > ' + output_file)

isExists = os.path.exists(bin_dir)
if not isExists:
    os.makedirs(bin_dir)

os.system('mv ' + shader_dir + os.path.sep+'*.vs ' + bin_dir)
os.system('mv ' + shader_dir + os.path.sep+'*.fs ' + bin_dir)
