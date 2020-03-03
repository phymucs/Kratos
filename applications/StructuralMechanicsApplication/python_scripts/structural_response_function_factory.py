from __future__ import print_function, absolute_import, division

# importing the Kratos Library
from KratosMultiphysics.StructuralMechanicsApplication import structural_response
from KratosMultiphysics.StructuralMechanicsApplication.structural_response import StrainEnergyResponseFunction
import KratosMultiphysics.ShapeOptimizationApplication as KSO

class CustomResponse(StrainEnergyResponseFunction):

    def __init__(self, response_id, response_settings, model):
        self.x = None
        self.y = None
        self.z = None
        super(CustomResponse, self).__init__(response_id, response_settings, model)

    def SetCoordinatesUpdate(self, x, y, z, model_part):
        self.x = x
        self.y = y
        self.z = z
        self.model_part = model_part
        print("::NODES AND MODEL PART RECIEVED::")

    def ModifyInitialGeometry(self):
        print("::ModifyInitialGeometry CALLED 1::")
        self.primal_analysis.ModifyInitialGeometry()
        #super(CustomResponse, self).__init__().GetSolver().ModifyInitialGeometry()

        for node in self.model_part.Nodes:
            node.X = self.x[node.Id-1]
            node.Y = self.y[node.Id-1]
            node.Z = self.z[node.Id-1]
        KSO.MeshControllerUtilities(self.model_part).SetReferenceMeshToMesh()
        print("::Nodes Transfered from OPTI MODELPART TO PRIMAL MODELPART::")

def CreateResponseFunction(response_id, response_settings, model):
    response_type = response_settings["response_type"].GetString()

    if response_type == "strain_energy":
        return CustomResponse(response_id, response_settings, model)
        # return structural_response.StrainEnergyResponseFunction(response_id, response_settings, model)

    elif response_type == "mass":
        return structural_response.MassResponseFunction(response_id, response_settings, model)

    elif response_type == "eigenfrequency":
        return structural_response.EigenFrequencyResponseFunction(response_id, response_settings, model)

    elif response_type == "adjoint_nodal_displacement":
        return structural_response.AdjointResponseFunction(response_id, response_settings, model)

    elif response_type == "adjoint_linear_strain_energy":
        return structural_response.AdjointResponseFunction(response_id, response_settings, model)

    elif response_type == "adjoint_local_stress":
        return structural_response.AdjointResponseFunction(response_id, response_settings, model)

    elif response_type == "adjoint_max_stress":
        return structural_response.AdjointResponseFunction(response_id, response_settings, model)

    elif response_type == "adjoint_nodal_reaction":
        return structural_response.AdjointResponseFunction(response_id, response_settings, model)

    else:
        raise NameError("The type of the following response function is not specified: "+ response_id +
                        ".\nAvailable types are: 'mass', 'strain_energy', 'eigenfrequency', 'adjoint_nodal_displacement', 'adjoint_linear_strain_energy', 'adjoint_local_stress', 'adjoint_max_stress', 'adjoint_nodal_reaction'." )