from __future__ import print_function, absolute_import, division  # makes KratosMultiphysics backward compatible with python 2.6 and 2.7

# Importing the Kratos Library
import KratosMultiphysics

# Import applications
import KratosMultiphysics.MeshMovingApplication as KratosMeshMoving

# Import baseclass
from KratosMultiphysics.MeshMovingApplication.mesh_solver_base import MeshSolverBase


def CreateSolver(model, custom_settings):
    return MeshSolverStructuralSimilarity(model, custom_settings)


class MeshSolverStructuralSimilarity(MeshSolverBase):
    def __init__(self, model, custom_settings):
        super(MeshSolverStructuralSimilarity, self).__init__(model, custom_settings)
        print("::[MeshSolverStructuralSimilarity]:: Construction finished")

    def _create_mesh_motion_solving_strategy(self):
        linear_solver = self.get_linear_solver()
<<<<<<< HEAD
        reform_dofs_each_step = self.settings["reform_dofs_each_step"].GetBool()
        print("PRINT REFORM DOFS EACH STEP         ", reform_dofs_each_step)
        compute_reactions = self.settings["compute_reactions"].GetBool()
=======

        print("PRINT LINEAR SOLVER", linear_solver)
        time_order = self.settings["time_order"].GetInt()
        print("PRINT TIME ORDER -----   ", time_order)

        reform_dofs_each_step = self.settings["reform_dofs_each_step"].GetBool()
        print("PRINT REFORM DOFS EACH STEP         ", reform_dofs_each_step)
        compute_reactions = self.settings["compute_reactions"].GetBool()

        print("COMPUTE REACTIONS >>>>>", compute_reactions)
        calculate_mesh_velocities = self.settings["calculate_mesh_velocities"].GetBool()
        print("CALCULATE MESH VELOCITIES ----++++    ", calculate_mesh_velocities)
        echo_level = self.settings["echo_level"].GetInt()

>>>>>>> f63c77c39467d9805ba37509300d50cee2397d56
        solving_strategy = KratosMeshMoving.StructuralMeshMovingStrategy(self.mesh_model_part,
                                                             linear_solver,
                                                             0,
                                                             reform_dofs_each_step,
                                                             compute_reactions,
<<<<<<< HEAD
                                                             False,
                                                             self.echo_level)
=======
                                                             calculate_mesh_velocities,
                                                             echo_level)
        print("FINALLY SOLVING STRATEGY              ", solving_strategy)

>>>>>>> f63c77c39467d9805ba37509300d50cee2397d56
        return solving_strategy
