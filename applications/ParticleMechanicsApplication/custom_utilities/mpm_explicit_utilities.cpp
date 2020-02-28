//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ \.
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:		 BSD License
//					 Kratos default license: kratos/license.txt
//
//  Main authors:    Peter Wilson
//

// System includes

// External includes

// Project includes
#include "custom_utilities/mpm_explicit_utilities.h"

namespace Kratos
{
    void MPMExplicitUtilities::CalcuateAndAddExplicitInternalForce(
        GeometryType& rGeom,
        const Matrix& rDN_DX,
        const Vector& rMPStress,
        const double& rMPVolume,
        Vector& rRightHandSideVector)
    {     
        KRATOS_TRY

        const unsigned int dimension = rGeom.WorkingSpaceDimension();
        const unsigned int number_of_nodes = rGeom.PointsNumber();
        array_1d<double, 3> nodal_force_internal_normal = ZeroVector(3); //PJW, needed for explicit force

        // Add in explicit internal force calculation (Fint = Volume*divergence(sigma))
        // TODO extend to 3D
        for (unsigned int i = 0; i < number_of_nodes; i++)
        {
            //f_x = V*(s_xx*dNdX + s_xy*dNdY)
            nodal_force_internal_normal[0] = rMPVolume *
                (rMPStress[0] * rDN_DX(i, 0) +
                    rMPStress[2] * rDN_DX(i, 1));

            //f_x = V*(s_yy*dNdX + s_xy*dNdX)
            nodal_force_internal_normal[1] = rMPVolume *
                (rMPStress[1] * rDN_DX(i, 1) +
                    rMPStress[2] * rDN_DX(i, 0));


            rRightHandSideVector[dimension*i] -= nodal_force_internal_normal[0]; //minus sign, internal forces
            rRightHandSideVector[dimension * i + 1] -= nodal_force_internal_normal[1]; //minus sign, internal forces

            if (dimension > 2)
            {
                // TODO add in third dimension here
                rRightHandSideVector[dimension * i + 2] -= nodal_force_internal_normal[2]; //minus sign, internal forces
            }
        }
            KRATOS_CATCH("")
    }

    /***********************************************************************************/
    /***********************************************************************************/

    void MPMExplicitUtilities::UpdateGaussPointExplicit(
        GeometryType& rGeom, 
        const double& rDeltaTime,
        const bool& isCentralDifference, 
        Element& rElement,
        Vector& rN)
    {
        KRATOS_TRY

        const unsigned int number_of_nodes = rGeom.PointsNumber();
        const unsigned int dimension = rGeom.WorkingSpaceDimension();
        bool isUpdateMPPositionFromUpdatedMPVelocity = true;

        // Update the MP Velocity
        const array_1d<double, 3>& MP_PreviousVelocity = rElement.GetValue(MP_VELOCITY);
        const array_1d<double, 3>& MP_PreviousAcceleration = rElement.GetValue(MP_ACCELERATION);
        array_1d<double, 3> MP_Velocity = ZeroVector(3);

        double alpha = 1.0;

        if (isCentralDifference)
        {
            alpha = 0.5;
            isUpdateMPPositionFromUpdatedMPVelocity = false;
        }

        // Advance the predictor velocity
        for (unsigned int i = 0; i < dimension; i++)
        {
            MP_Velocity[i] = MP_PreviousVelocity[i] + (1.0-alpha) * rDeltaTime * MP_PreviousAcceleration[i];
        }


        array_1d<double, 3> delta_xg = ZeroVector(3);
        array_1d<double, 3> MP_Acceleration = ZeroVector(3);

        for (unsigned int i = 0; i < number_of_nodes; i++)
        {
            const double nodal_mass = rGeom[i].FastGetSolutionStepValue(NODAL_MASS);

            if (nodal_mass > std::numeric_limits<double>::epsilon())
            {
                const array_1d<double, 3>& r_nodal_momenta = rGeom[i].FastGetSolutionStepValue(NODAL_MOMENTUM);
                const array_1d<double, 3>& r_current_residual = rGeom[i].FastGetSolutionStepValue(FORCE_RESIDUAL);
                const array_1d<double, 3>& r_middle_velocity = rGeom[i].FastGetSolutionStepValue(VELOCITY);

                for (unsigned int j = 0; j < dimension; j++)
                {
                    MP_Acceleration[j] += rN[i] * r_current_residual[j] / nodal_mass;
                    if (isCentralDifference)
                    {
                        delta_xg[j] += rDeltaTime * rN[i] * r_middle_velocity[j];
                    }
                    else if (!isUpdateMPPositionFromUpdatedMPVelocity)
                    {
                        delta_xg[j] += rDeltaTime * rN[i] * r_nodal_momenta[j] / nodal_mass;
                    }
                }
            }
        }

        // Update the MP Velocity corrector
        for (unsigned int j = 0; j < dimension; j++)
        {
            MP_Velocity[j] += alpha * rDeltaTime * MP_Acceleration[j];
        }
        rElement.SetValue(MP_VELOCITY, MP_Velocity);

        // Update the MP Position
        const array_1d<double, 3>& xg = rElement.GetValue(MP_COORD);
        if (isUpdateMPPositionFromUpdatedMPVelocity)
        {
            for (unsigned int j = 0; j < dimension; j++)
            {
                delta_xg[j] = rDeltaTime* MP_Velocity[j];
            }
        }
        const array_1d<double, 3>& new_xg = xg + delta_xg;
        rElement.SetValue(MP_COORD, new_xg);


        // Update the MP Acceleration
        rElement.SetValue(MP_ACCELERATION, MP_Acceleration);


        // Update the MP total displacement
        array_1d<double, 3>& MP_Displacement = rElement.GetValue(MP_DISPLACEMENT);
        MP_Displacement += delta_xg;
        rElement.SetValue(MP_DISPLACEMENT, MP_Displacement);

        KRATOS_CATCH("")
    }

    /***********************************************************************************/
    /***********************************************************************************/
    
    void MPMExplicitUtilities::CalculateMUSLGridVelocity(
        GeometryType& rGeom,
        Element& rElement,
        Vector& rN)
    {

        KRATOS_TRY
        const unsigned int dimension = rGeom.WorkingSpaceDimension();
        const unsigned int number_of_nodes = rGeom.PointsNumber();
        const array_1d<double, 3>& MP_Velocity = rElement.GetValue(MP_VELOCITY);
        const double& MP_Mass = rElement.GetValue(MP_MASS);

        for (unsigned int i = 0; i < number_of_nodes; i++)
        {
            array_1d<double, 3>& r_current_velocity = rGeom[i].FastGetSolutionStepValue(VELOCITY);
            const double& r_nodal_mass = rGeom[i].FastGetSolutionStepValue(NODAL_MASS);

            for (unsigned int j = 0; j < dimension; j++)
            {
                // we need to use the original shape functions here (calculated before the momenta update)
                r_current_velocity[j] += rN[i] * MP_Mass * MP_Velocity[j] / r_nodal_mass;
            }
        }

        KRATOS_CATCH("")
    }

    /***********************************************************************************/
    /***********************************************************************************/
    
    void MPMExplicitUtilities::CalculateExplicitKinematics(
        GeometryType& rGeom,
        const Matrix& rDN_DX,
        const double rDeltaTime,
        Vector& rMPStrain,
        Matrix& rDeformationGradient,
        const bool& isCompressible)
    {
        KRATOS_TRY

        const SizeType dimension = rGeom.WorkingSpaceDimension();
        const SizeType number_of_nodes = rGeom.PointsNumber();


        //Calculate velocity gradients
        Matrix velocityGradient = Matrix(dimension, dimension, 0.0);
        for (IndexType nodeIndex = 0; nodeIndex < number_of_nodes; nodeIndex++)
        {
            const array_1d<double, 3 >& nodal_velocity = rGeom[nodeIndex].FastGetSolutionStepValue(VELOCITY);

            for (IndexType i = 0; i < dimension; i++)
            {
                for (IndexType j = 0; j < dimension; j++)
                {
                    velocityGradient(i, j) += nodal_velocity[i] * rDN_DX(nodeIndex, j);
                }
            }
        }
        

        //Calculate rate of deformation and spin tensors
        Matrix rateOfDeformation = 0.5 * (velocityGradient + trans(velocityGradient));
        Matrix spinTensor = velocityGradient - rateOfDeformation;


        //Calculate objective Jaumann strain rate
        Matrix jaumannRate = rateOfDeformation -
            (prod(spinTensor, rateOfDeformation)) * rDeltaTime +
            prod((rateOfDeformation * rDeltaTime), spinTensor);

        // TODO extend to 3D
        rMPStrain(0) += jaumannRate(0, 0) * rDeltaTime; //e_xx
        rMPStrain(1) += jaumannRate(1, 1) * rDeltaTime; //e_yy
        rMPStrain(2) += 2.0 * jaumannRate(0, 1) * rDeltaTime; //e_xy


        // Model compressibility
        if (isCompressible)
        {
            Matrix I = IdentityMatrix(dimension);
            Matrix updatedDeformationGradient = prod((I + rDeltaTime * velocityGradient),
                rDeformationGradient);
            rDeformationGradient = updatedDeformationGradient;
        }

        KRATOS_CATCH("")
    }
} // namespace Kratos
