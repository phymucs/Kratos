//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:		 BSD License
//					 Kratos default license: kratos/license.txt
//
//  Main authors:    Dharmin Shah (https://github.com/sdharmin)
//

// System includes
#include <cmath>
#include <limits>

// External includes

// Project includes
#include "includes/define.h"
#include "utilities/variable_utils.h"

// Application includes
#include "custom_utilities/rans_check_utilities.h"
#include "custom_utilities/rans_calculation_utilities.h"
#include "rans_application_variables.h"
#include "fluid_dynamics_application_variables.h"

// Include base h
#include "rans_compute_reactions_process.h"

namespace Kratos
{
RansComputeReactionsProcess::RansComputeReactionsProcess(
    Model& rModel, Parameters rParameters)
    : mrModel(rModel), mrParameters(rParameters)
{
    KRATOS_TRY

    Parameters default_parameters = Parameters(R"(
        {
            "model_part_name"         : "PLEASE_SPECIFY_MODEL_PART_NAME",
            "echo_level"              : 0
        })");

    mrParameters.ValidateAndAssignDefaults(default_parameters);

    mEchoLevel = mrParameters["echo_level"].GetInt();
    mModelPartName = mrParameters["model_part_name"].GetString();


    KRATOS_CATCH("");
}


void RansComputeReactionsProcess::ExecuteFinalizeSolutionStep()
{
    KRATOS_TRY

    ModelPart::ConditionsContainerType& r_conditions =
        mrModel.GetModelPart(mModelPartName).Conditions();
    const int number_of_conditions = r_conditions.size();

    VariableUtils().SetHistoricalVariableToZero(REACTION,  mrModel.GetModelPart(mModelPartName).Nodes());

#pragma omp parallel for
    for (int i_cond = 0; i_cond < number_of_conditions; ++i_cond)
    {
        ModelPart::ConditionType& r_condition = *(r_conditions.begin() + i_cond);
        CalculateReactionValues(r_condition);
    }
    //node loop
    ModelPart::NodesContainerType& r_nodes= mrModel.GetModelPart(mModelPartName).Nodes();
    int number_of_nodes = r_nodes.size();
    #pragma omp parallel for
    for (int i_node = 0; i_node < number_of_nodes; ++i_node)
    {
        NodeType& r_node = *(r_nodes.begin() + i_node);
        const array_1d<double, 3>& pressure_force = r_node.FastGetSolutionStepValue(NORMAL) * (-1.0 * r_node.FastGetSolutionStepValue(PRESSURE));
        r_node.FastGetSolutionStepValue(REACTION) += pressure_force;
    }
    

    KRATOS_INFO_IF(this->Info(), mEchoLevel > 0)
        << "Computed Reaction terms for " << mModelPartName << " for slip condition.\n";

    KRATOS_CATCH("");
}

// void RansComputeReactionsProcess::ExecuteInitialize()
// {
   
//     ModelPart::NodesContainerType& r_nodes =
//         mrModel.GetModelPart(mModelPartName).Nodes();
//     const int number_of_nodes = r_nodes.size();
// #pragma omp parallel for
//     for (int i_node = 0; i_node < number_of_nodes; ++i_node)
//     {
//         NodeType& r_node = *(r_nodes.begin() + i_node);
//         r_node.FastGetSolutionStepValue(REACTION)=ZeroVector(3);
//     }


//     KRATOS_INFO_IF(this->Info(), mEchoLevel > 0)
//         << "Making Reaction initially for dofs in " << mModelPartName << "0.0.\n";
    
// }

int RansComputeReactionsProcess::Check()
{
    KRATOS_TRY
    RansCheckUtilities::CheckIfModelPartExists(mrModel, mModelPartName);

    ModelPart& r_model_part = mrModel.GetModelPart(mModelPartName);

    RansCheckUtilities::CheckIfVariableExistsInModelPart(r_model_part, REACTION);
    RansCheckUtilities::CheckIfVariableExistsInModelPart(r_model_part, DENSITY);
    RansCheckUtilities::CheckIfVariableExistsInModelPart(r_model_part, FRICTION_VELOCITY);
    RansCheckUtilities::CheckIfVariableExistsInModelPart(r_model_part, PRESSURE);
    RansCheckUtilities::CheckIfVariableExistsInModelPart(r_model_part, NORMAL);

    return 0;
    KRATOS_CATCH("");
}

std::string RansComputeReactionsProcess::Info() const
{
    return std::string("RansComputeReactionsProcess");
}

void RansComputeReactionsProcess::PrintInfo(std::ostream& rOStream) const
{
    rOStream << this->Info();
}

void RansComputeReactionsProcess::PrintData(std::ostream& rOStream) const
{
}

void RansComputeReactionsProcess::CalculateReactionValues(ModelPart::ConditionType& rCondition)
{

    if (RansCalculationUtilities::IsWall(rCondition))
    {


        ModelPart::ConditionType::GeometryType& r_geometry = rCondition.GetGeometry();
        for (IndexType i_node = 0; i_node < r_geometry.PointsNumber(); ++i_node)
        {
            NodeType& r_node = r_geometry[i_node];
            const double rho = r_node.FastGetSolutionStepValue(DENSITY);
            const  array_1d<double, 3>& r_friction_force =rCondition.GetValue(FRICTION_VELOCITY)* (rho *  
                                                        norm_2(rCondition.GetValue(FRICTION_VELOCITY)) * r_geometry.DomainSize());
            #pragma omp critical
            {
                r_node.FastGetSolutionStepValue(REACTION) += (r_friction_force/r_geometry.PointsNumber());
            }
        }
    }

    //mrModel.GetModelPart(mModelPartName).GetCommunicator().AssembleCurrentData(REACTION);

}

} // namespace Kratos.
