from __future__ import print_function, absolute_import, division #makes KratosMultiphysics backward compatible with python 2.6 and 2.7

import KratosMultiphysics as KM
import KratosMultiphysics.ShapeOptimizationApplication as KSO
from KratosMultiphysics.StructuralMechanicsApplication.structural_mechanics_analysis import StructuralMechanicsAnalysis
from KratosMultiphysics.ShapeOptimizationApplication import optimizer_factory
from KratosMultiphysics.ShapeOptimizationApplication.analyzer_base import AnalyzerBaseClass
import KratosMultiphysics.StructuralMechanicsApplication as StructuralMechanicsApplication
from KratosMultiphysics.StructuralMechanicsApplication import structural_response
from KratosMultiphysics.StructuralMechanicsApplication.structural_mechanics_analysis import StructuralMechanicsAnalysis
from KratosMultiphysics import Parameters, Logger
from KratosMultiphysics.analysis_stage import AnalysisStage
import time as timer
import shutil
import glob, os

if __name__ == "__main__":

    #Read parameter
    with open("ProjectParameters5.json",'r') as parameter_file:
        parameters = KM.Parameters(parameter_file.read())

    model = KM.Model()
    simulation = StructuralMechanicsAnalysis(model,parameters)
    primal_model_part = model.GetModelPart(parameters["solver_settings"]["model_part_name"].GetString())
    simulation.Initialize()

    #RunSolutionLoop
    #   1   InitializeSolutionStep
    #   2   Calculate value -> Perdict & SolveSolutionStep
    #   3   Calculate gradient
    #   4   FinalizeSolutionStep 
    #   5   Reset Mesh & Displacement
    #   6   OutputSolutionStep & Finalize

    print("\n::PRIMAL::")
    for node in primal_model_part.Nodes:
        if node.Id < 6:
            print(node.Id, node.X, node.Y, node.Z)
    
    #################################################################
    time = primal_model_part.ProcessInfo.GetValue(KM.TIME)
    time = simulation._GetSolver().AdvanceInTime(time)
    simulation.InitializeSolutionStep()

    simulation._GetSolver().Predict()
    simulation._GetSolver().SolveSolutionStep()

    simulation.FinalizeSolutionStep()
    simulation.OutputSolutionStep()

    print("\n::PRIMAL:1:")
    for node in primal_model_part.Nodes:
        if node.Id < 6:
            dx = node.GetSolutionStepValue(KM.DISPLACEMENT_X,0)
            dy = node.GetSolutionStepValue(KM.DISPLACEMENT_Y,0)
            dz = node.GetSolutionStepValue(KM.DISPLACEMENT_Z,0)
            print(node.Id, node.X, node.Y, node.Z, dx, dy, dz)

    KSO.MeshControllerUtilities(primal_model_part).SetMeshToReferenceMesh()

    print("\n::before reset:1:")
    for node in primal_model_part.Nodes:
        if node.Id < 6:
            dx = node.GetSolutionStepValue(KM.DISPLACEMENT_X,0)
            dy = node.GetSolutionStepValue(KM.DISPLACEMENT_Y,0)
            dz = node.GetSolutionStepValue(KM.DISPLACEMENT_Z,0)
            print(node.Id, node.X, node.Y, node.Z, dx, dy, dz)

    KSO.MeshControllerUtilities(primal_model_part).SetDeformationVariablesToZero()

    print("\n::After reset:1:")
    for node in primal_model_part.Nodes:
        if node.Id < 6:
            dx = node.GetSolutionStepValue(KM.DISPLACEMENT_X,0)
            dy = node.GetSolutionStepValue(KM.DISPLACEMENT_Y,0)
            dz = node.GetSolutionStepValue(KM.DISPLACEMENT_Z,0)
            print(node.Id, node.X, node.Y, node.Z, dx, dy, dz)
            
    ###################################################################################

    time = primal_model_part.ProcessInfo.GetValue(KM.TIME)
    time = simulation._GetSolver().AdvanceInTime(time)
    simulation.InitializeSolutionStep()
    
    simulation._GetSolver().Predict()
    simulation._GetSolver().SolveSolutionStep()
    
    simulation.FinalizeSolutionStep()
    simulation.OutputSolutionStep()
  
    print("\n::PRIMAL:1:")
    for node in primal_model_part.Nodes:
        if node.Id < 6:
            dx = node.GetSolutionStepValue(KM.DISPLACEMENT_X,0)
            dy = node.GetSolutionStepValue(KM.DISPLACEMENT_Y,0)
            dz = node.GetSolutionStepValue(KM.DISPLACEMENT_Z,0)
          
            print(node.Id, node.X, node.Y, node.Z, dx, dy, dz)
   

    simulation.Finalize()
