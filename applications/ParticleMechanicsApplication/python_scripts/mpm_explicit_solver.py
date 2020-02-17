from __future__ import print_function, absolute_import, division  # makes KratosMultiphysics backward compatible with python 2.6 and 2.7

# Importing the Kratos Library
import KratosMultiphysics

# Import applications and dependencies
import KratosMultiphysics.ParticleMechanicsApplication as KratosParticle

# Importing the base class
from KratosMultiphysics.ParticleMechanicsApplication.mpm_solver import MPMSolver

def CreateSolver(model, custom_settings):
    return MPMExplicitSolver(model, custom_settings)

class MPMExplicitSolver(MPMSolver):

    def __init__(self, model, custom_settings):
        # Set defaults and validate custom settings in the base class.
        # Construct the base solver.
        super(MPMExplicitSolver, self).__init__(model, custom_settings)
        KratosMultiphysics.Logger.PrintInfo("::[MPMExplicitSolver]:: ", "Construction is finished.")

    @classmethod
    def GetDefaultSettings(cls):
        this_defaults = KratosMultiphysics.Parameters("""{
            "scheme_type"   : "forward_euler",
            "stress_update" : "USL"
        }""")
        this_defaults.AddMissingParameters(super(MPMExplicitSolver, cls).GetDefaultSettings())
        return this_defaults


    def AddVariables(self):
        super(MPMExplicitSolver, self).AddVariables()
        self._AddDynamicVariables(self.grid_model_part)
        grid_model_part = self.GetGridModelPart()

        # Adding explicit variables
        grid_model_part.AddNodalSolutionStepVariable(KratosMultiphysics.FORCE_RESIDUAL)
        grid_model_part.AddNodalSolutionStepVariable(KratosMultiphysics.RESIDUAL_VECTOR)

        scheme_type = self.settings["scheme_type"].GetString()
        if(scheme_type == "central_differences"):
            grid_model_part.AddNodalSolutionStepVariable(ParticleMechanicsApplication.MIDDLE_VELOCITY)
        KratosMultiphysics.Logger.PrintInfo("::[MPMExplicitSolver]:: ", "Variables are all added.")

    ### Protected functions ###

    def _CreateSolutionScheme(self):
        grid_model_part = self.GetGridModelPart()
        domain_size = self._GetDomainSize()
        block_size  = domain_size
        if (self.settings["pressure_dofs"].GetBool()):
            block_size += 1

        # Setting the time integration schemes
        scheme_type = self.settings["scheme_type"].GetString()
        isCentralDifference = False
        StressUpdateOption = 0

        if(scheme_type == "forward_euler"):
            stress_update = self.settings["stress_update"].GetString() #0 = USF, 1 = USL, 2 = MUSL
            if(stress_update == "USF"):
                StressUpdateOption = 0
            elif(stress_update == "USL"):
                StressUpdateOption = 1
            elif(stress_update == "MUSL"):
                StressUpdateOption = 2
            else:
                err_msg = "The requested stress update \"" + stress_update + "\" is not available!\n"
                err_msg += "Available options are: \"USF\", \"USL\",\"MUSL\""
        elif(scheme_type == "central_difference"):
            isCentralDifference = True
        else:
            err_msg = "The requested scheme type \"" + scheme_type + "\" is not available!\n"
            err_msg += "Available options are: \"forward_euler\", \"central_difference\""
            raise Exception(err_msg)

        is_dynamic = self._IsDynamic()

        return KratosParticle.MPMExplicitScheme( grid_model_part,
                                                 StressUpdateOption,
                                                 isCentralDifference)

    def _CreateSolutionStrategy(self):
        analysis_type = self.settings["analysis_type"].GetString()
        if analysis_type == "linear":
                self.material_point_model_part.ProcessInfo.SetValue(KratosParticle.IS_EXPLICIT, True)
                solution_strategy = self._CreateLinearStrategy()
        else:
            err_msg =  "The requested explicit analysis type \"" + analysis_type + "\" is not available!\n"
            err_msg += "Available explicit options are: \"linear\""
            raise Exception(err_msg)
        return solution_strategy


    def _CreateLinearStrategy(self):
        computing_model_part = self.GetComputingModelPart()
        solution_scheme = self._GetSolutionScheme()
        linear_solver = self._GetLinearSolver()
        reform_dofs_at_each_step = False ## hard-coded, but can be changed upon implementation
        calc_norm_dx_flag = False ## hard-coded, but can be changed upon implementation
        return KratosMultiphysics.ResidualBasedLinearStrategy(computing_model_part,
                                                              solution_scheme,
                                                              linear_solver,
                                                              self.settings["compute_reactions"].GetBool(),
                                                              reform_dofs_at_each_step,
                                                              calc_norm_dx_flag,
                                                              self.settings["move_mesh_flag"].GetBool())

    def _IsDynamic(self):
        return True