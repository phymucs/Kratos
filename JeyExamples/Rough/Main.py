import shutil
import glob, os
import KratosMultiphysics.kratos_utilities as kratos_utilities



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
    print(i)
    shutil.rmtree('Opti_ITR_'+str(i))
for i in range (0,2):
    os.makedirs(original_directory+'/Opti_ITR_'+str(i))
    os.chdir(original_directory+'/Opti_ITR_'+str(i))
    f= open("guru95.txt","w+")
    print('done')

# response_directory[response_id] = original_directory + "Response_", response_id

# os.mkdir('Res')
#                                                                    
# os.makedirs(str(response_directory[response_id])+'/Opti_ITR_'+str(optimizationIteration))
#                                                                     
# os.chdir(str(response_directory[response_id]) + '/Opti_ITR_'+str(optimizationIteration))

# self.response_functions[response_id] = csm_response_factory.CreateResponseFunction(response_id, response_settings, self.model) 

# os.chdir(original_directory) 