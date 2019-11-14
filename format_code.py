import os
import subprocess

path = '.'

files = []
# r=root, d=directories, f = files
for r, d, f in os.walk(path):
    for file in f:
        if '.cpp' in file or '.h' in file:
            files.append(os.path.join(r, file))

cmd = ['clang-format.exe', '-i', '-verbose']
cmd.extend(files)
p = subprocess.Popen(cmd)
p.communicate()

