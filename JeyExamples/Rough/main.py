import shutil
import glob, os


original_directory = os.getcwd()

subfolder_names = ["jey", "kibs"]
# for subfolder_name in subfolder_names:
#     dst = os.path.join(str(original_directory), ("Folder_" + subfolder_name))
#     os.mkdir(dst)
#     os.chdir(dst)
#     f= open("guru99.txt","w+")
#     os.chdir(original_directory)
# os.mkdir('monster')
# os.makedirs('monster/jey')

for i in range (0,2):
    os.makedirs(original_directory+'/Opti_ITR_'+str(i))
    os.chdir(original_directory+'/Opti_ITR_'+str(i))
    f= open("guru99.txt","w+")