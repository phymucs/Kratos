from __future__ import print_function, absolute_import, division #makes KratosMultiphysics backward compatible with python 2.6 and 2.7

import KratosMultiphysics as KM
from KratosMultiphysics.StructuralMechanicsApplication.structural_mechanics_analysis import StructuralMechanicsAnalysis
from KratosMultiphysics.ShapeOptimizationApplication import optimizer_factory
from KratosMultiphysics.ShapeOptimizationApplication.analyzer_base import AnalyzerBaseClass
import KratosMultiphysics.StructuralMechanicsApplication as StructuralMechanicsApplication
from KratosMultiphysics.StructuralMechanicsApplication import structural_response
from KratosMultiphysics import Parameters, Logger
from KratosMultiphysics.analysis_stage import AnalysisStage
import KratosMultiphysics.kratos_utilities as kratos_utilities
import KratosMultiphysics.ShapeOptimizationApplication as KSO
import time as timer
import shutil
import glob, os

class CustomAnalysis(StructuralMechanicsAnalysis):

    def __init__(self, model, project_parameters):
        self.x = None
        self.y = None
        self.z = None
        super(CustomAnalysis, self).__init__(model, project_parameters)

    def SetCoordinatesUpdate(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z
        self.primal_model_part2 = model.GetModelPart("Struct_Load_2")
        print("::NODES AND MODEL PART RECIEVED::", self.primal_model_part2)

    def ModifyInitialGeometry(self):
        print("::ModifyInitialGeometry CALLED 1::")
        super(CustomAnalysis, self).ModifyInitialGeometry()
        print("::NODES AND MODEL PART RECIEVED::", self.primal_model_part2)
        for node in self.model.GetModelPart("Struct_Load_2").Nodes:
            node.X = self.x[node.Id-1]
            node.Y = self.y[node.Id-1]
            node.Z = self.z[node.Id-1]
        KSO.MeshControllerUtilities(self.model.GetModelPart("Struct_Load_2")).SetReferenceMeshToMesh()
        print("::Nodes Transfered from OPTI MODELPART TO PRIMAL MODELPART::")

if __name__ == "__main__":

    #Read from Optimized MDPA (plateR)
    with open("plateModified.json",'r') as parameter_file:
        parameters = KM.Parameters(parameter_file.read())

    model = KM.Model()
    simulation1 = StructuralMechanicsAnalysis(model,parameters)
    primal_model_part1 = model.GetModelPart("Struct_Load_1")
    simulation1.Initialize()
    print("::OPTIMIZED MODEL::")
    x = []
    y = []
    z = []
    for node in primal_model_part1.Nodes:
        x.append(node.X)
        y.append(node.Y)
        z.append(node.Z)
        # print(node.Id, x[node.Id-1], y[node.Id-1], z[node.Id-1])
    

    #Read parameter from Original MDPA (plate)
    with open("PlateOptiResponse2.json",'r') as parameter_file:
        parameters = KM.Parameters(parameter_file.read())

    model = KM.Model()
    simulation2 = CustomAnalysis(model,parameters)
    simulation2.SetCoordinatesUpdate(x, y, z)

    shutil.rmtree('Response')
    original = os.getcwd()
    os.makedirs('Response')
    
    
    simulation2.Initialize()

    primal_model_part2 = model.GetModelPart("Struct_Load_2")

    time = primal_model_part2.ProcessInfo.GetValue(KM.TIME)
    time = simulation2._GetSolver().AdvanceInTime(time)
    simulation2.InitializeSolutionStep()
    os.chdir('Response')
    simulation2._GetSolver().Predict()       
    simulation2._GetSolver().SolveSolutionStep()
    simulation2.FinalizeSolutionStep()
    simulation2.OutputSolutionStep()
    simulation2.Finalize()

    os.chdir(original)

    # Cleaning
    kratos_utilities.DeleteDirectoryIfExisting("__pycache__")
    response_combination_filename = "response_combination.csv"
    kratos_utilities.DeleteFileIfExisting(response_combination_filename)
    kratos_utilities.DeleteFileIfExisting("plateThin3N.post")
    kratos_utilities.DeleteFileIfExisting("MultiAnalysis.post")
