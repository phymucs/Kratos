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

#if !defined(KRATOS_MPM_EXPLICIT_UTILITIES)
#define KRATOS_MPM_EXPLICIT_UTILITIES

// System includes

// External includes

// Project includes
#include "includes/model_part.h"
#include "includes/element.h"
#include "includes/variables.h"


#include "particle_mechanics_application_variables.h"

namespace Kratos
{
///@name Kratos Classes
///@{
/**
 * @namespace MPMExplicitUtilities
 * @ingroup ParticleMechanicsApplication
 * @brief This namespace includes several utilities necessaries for the computation of the explicit integration
 * @author Peter Wilson
 */
namespace MPMExplicitUtilities
{
    /// The size type definition
    typedef std::size_t SizeType;

    /// The index type definition
    typedef std::size_t IndexType;

    /// The arrays of elements and nodes
    typedef ModelPart::ElementsContainerType ElementsArrayType;
    typedef ModelPart::NodesContainerType NodesArrayType;
    typedef Node<3> NodeType;
    typedef Geometry<NodeType> GeometryType;
    
    // Reference https://github.com/KratosMultiphysics/Kratos/blob/MPM/explicit_time_int2/applications/ParticleMechanicsApplication/custom_elements/updated_lagrangian_quadrilateral.cpp


    // CalcuateExplicitInternalForce
    void KRATOS_API(PARTICLE_MECHANICS_APPLICATION) CalcuateExplicitInternalForce(GeometryType& rGeom, 
        const Matrix& rDN_DX, const Vector& rMPStress, const double& rMPVolume);
    
    // UpdateGaussPointExplicit
    void KRATOS_API(PARTICLE_MECHANICS_APPLICATION) UpdateGaussPointExplicit(GeometryType& rGeom,
        const double& rDeltaTime, const bool& isCentralDifference, Element& rElement, Vector& rN);

    // FinalizeSolutionStepExplicit

    // CalculateExplicitKinematics
    //void KRATOS_API(PARTICLE_MECHANICS_APPLICATION) CalculateExplicitKinematics(const GeometryType& rGeom, 
    //    const double rDeltaTime, Vector& rMPStrain, Matrix& rDeformationGradient, const bool& isCompressible);


}; // namespace ExplicitIntegrationUtilities
}  // namespace Kratos
#endif /* KRATOS_MPM_EXPLICIT_UTILITIES defined */
