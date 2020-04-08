#if !defined(KRATOS_MEMBRANE_DISCRETE_ELEMENT_H_INCLUDED )
#define  KRATOS_MEMBRANE_DISCRETE_ELEMENT_H_INCLUDED


// System includes

// External includes

// Project includes
#include "custom_elements/surface_base_discrete_element.h"

namespace Kratos
{
///@name Kratos Classes
///@{
/// Short class definition.
/** Plate in membrane. Optimized for Isogeometric Analysis by Kiendl et al. .
*/
class MembraneDiscreteElement
    : public SurfaceBaseDiscreteElement
{
public:
    ///@name Type Definitions
    ///@{
    /// Counted pointer of MembraneDiscreteElement
    KRATOS_CLASS_INTRUSIVE_POINTER_DEFINITION(MembraneDiscreteElement);
    ///@}
    ///@name Life Cycle
    ///@{
    /// Default constructor.
    // Constructor using an array of nodes
    MembraneDiscreteElement(IndexType NewId, GeometryType::Pointer pGeometry)
        : SurfaceBaseDiscreteElement(NewId, pGeometry)
    {};
    // Constructor using an array of nodes with properties
    MembraneDiscreteElement(IndexType NewId, GeometryType::Pointer pGeometry, PropertiesType::Pointer pProperties)
        : SurfaceBaseDiscreteElement(NewId, pGeometry, pProperties)
    {};

    // default constructor necessary for serialization
    MembraneDiscreteElement() : SurfaceBaseDiscreteElement() {};

    /// Destructor.
    virtual ~MembraneDiscreteElement() override
    {};

    Element::Pointer Create(IndexType NewId, NodesArrayType const& ThisNodes, PropertiesType::Pointer pProperties) const override
    {
        return Kratos::make_intrusive< MembraneDiscreteElement >(NewId, GetGeometry().Create(ThisNodes), pProperties);
    };

    ///@}
    ///@name Operations
    ///@{

    /**
    * This functions calculates both the RHS and the LHS
    * @param rLeftHandSideMatrix: The LHS
    * @param rRightHandSideVector: The RHS
    * @param rCurrentProcessInfo: The current process info instance
    * @param CalculateStiffnessMatrixFlag: The flag to set if compute the LHS
    * @param CalculateResidualVectorFlag: The flag to set if compute the RHS
    */
    void CalculateAll(
        MatrixType& rLeftHandSideMatrix,
        VectorType& rRightHandSideVector,
        ProcessInfo& rCurrentProcessInfo,
        const bool CalculateStiffnessMatrixFlag,
        const bool CalculateResidualVectorFlag
    ) override;


    /**
    * Calculate a double Variable on the Element Constitutive Law
    * @param rVariable: The variable we want to get
    * @param rOutput: The values obtained int the integration points
    * @param rCurrentProcessInfo: the current process info instance
    */
    void CalculateOnIntegrationPoints(
        const Variable<double>& rVariable,
        std::vector<double>& rOutput,
        const ProcessInfo& rCurrentProcessInfo
    ) override;

    /**
    * Calculate a Vector Variable on the Element Constitutive Law
    * @param rVariable: The variable we want to get
    * @param rOutput: The values obtained int the integration points
    * @param rCurrentProcessInfo: the current process info instance
    */
    void CalculateOnIntegrationPoints(
        const Variable<Vector>& rVariable,
        std::vector<Vector>& rValues,
        const ProcessInfo& rCurrentProcessInfo
    ) override;



    /**
    * This function provides the place to perform checks on the completeness of the input.
    * It is designed to be called only once (or anyway, not often) typically at the beginning
    * of the calculations, so to verify that nothing is missing from the input
    * or that no common error is found.
    * @param rCurrentProcessInfo
    */
    int Check(const ProcessInfo& rCurrentProcessInfo) override;




    std::string Info() const override
    {
        std::stringstream buffer;
        buffer << "MembraneElement #" << Id();
        return buffer.str();
    }

    /// Print information about this object.

    void PrintInfo(std::ostream& rOStream) const override
    {
        rOStream << "MembraneElement #" << Id();
    }

    ///@}

protected:

private:
    ///@name Static Member Variables
    ///@{
    ///@name Operations
    ///@{
    void CalculateMetric( MetricVariables& metric ) override;


    /**
    * This functions updates the constitutive variables
    * @param rActualMetric: The actual metric
    * @param rThisConstitutiveVariables: The constitutive variables to be calculated
    * @param rValues: The CL parameters
    * @param ThisStressMeasure: The stress measure considered
    */
    void CalculateConstitutiveVariables(
        MetricVariables& rActualMetric,
        ConstitutiveVariables& rThisConstitutiveVariablesMembrane,
        ConstitutiveLaw::Parameters& rValues,
        const ConstitutiveLaw::StressMeasure ThisStressMeasure
    );
    ///@}

    ///@}
    ///@name Serialization
    ///@{

    friend class Serializer;

    void save(Serializer& rSerializer) const override
    {
        KRATOS_SERIALIZE_SAVE_BASE_CLASS(rSerializer, Element)
    }

    void load(Serializer& rSerializer) override
    {
        KRATOS_SERIALIZE_LOAD_BASE_CLASS(rSerializer, Element)
    }

    ///@}

};     // Class MembraneDiscreteElement
///@}

}  // namespace Kratos.

#endif // KRATOS_MESHLESS_MEMBRANE_DISCRETE_ELEMENT_H_INCLUDED  defined