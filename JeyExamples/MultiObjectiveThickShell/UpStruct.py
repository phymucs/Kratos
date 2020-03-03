from __future__ import print_function, absolute_import, division #makes KratosMultiphysics backward compatible with python 2.6 and 2.7

import KratosMultiphysics as KM
from KratosMultiphysics.StructuralMechanicsApplication.structural_mechanics_analysis import StructuralMechanicsAnalysis
from KratosMultiphysics.ShapeOptimizationApplication import optimizer_factory
from KratosMultiphysics.ShapeOptimizationApplication.analyzer_base import AnalyzerBaseClass
import KratosMultiphysics.StructuralMechanicsApplication as StructuralMechanicsApplication
from KratosMultiphysics.StructuralMechanicsApplication import structural_response
from KratosMultiphysics.StructuralMechanicsApplication.structural_mechanics_analysis import StructuralMechanicsAnalysis
from KratosMultiphysics import Parameters, Logger
from KratosMultiphysics.analysis_stage import AnalysisStage
import KratosMultiphysics.kratos_utilities as kratos_utilities
import KratosMultiphysics.ShapeOptimizationApplication as KSO
import time as timer
import shutil
import glob, os

if __name__ == "__main__":

    #Read from Optimized MDPA (plateR)
    with open("ProjectParameters5.json",'r') as parameter_file:
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
        print(node.Id, x[node.Id-1], y[node.Id-1], z[node.Id-1])
    

    #Read parameter from Original MDPA (plate)
    with open("ProjectParameters6.json",'r') as parameter_file:
        parameters = KM.Parameters(parameter_file.read())

    model = KM.Model()
    simulation2 = StructuralMechanicsAnalysis(model,parameters)
    simulation2.Initialize()
    primal_model_part2 = model.GetModelPart("Struct_Load_1")

    for node in primal_model_part2.Nodes:
        node.X = x[node.Id-1]
        node.Y = y[node.Id-1]
        node.Z = z[node.Id-1]
    KSO.MeshControllerUtilities(primal_model_part2).SetReferenceMeshToMesh()
    print("::Nodes Transfered from OPTI MODELPART TO PRIMAL MODELPART::")

    time = primal_model_part2.ProcessInfo.GetValue(KM.TIME)
    time = simulation2._GetSolver().AdvanceInTime(time)
    simulation2.InitializeSolutionStep()

    simulation2._GetSolver().Predict()       #ignore and check the domain size, bc load =0
    simulation2._GetSolver().SolveSolutionStep()

    simulation2.FinalizeSolutionStep()
    simulation2.OutputSolutionStep()
    simulation2.Finalize()

    # Cleaning
    kratos_utilities.DeleteDirectoryIfExisting("__pycache__")
    response_combination_filename = "response_combination.csv"
    kratos_utilities.DeleteFileIfExisting(response_combination_filename)
