//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:         BSD License
//                   Kratos default license: kratos/license.txt
//
//  Main authors:    Tobias Teschemacher
//

#if !defined(KRATOS_INTEGRATION_POINT_CURVE_ON_SURFACE_3D_H_INCLUDED )
#define  KRATOS_INTEGRATION_POINT_CURVE_ON_SURFACE_3D_H_INCLUDED

// System includes

// External includes

// Project includes
#include "geometries/geometry.h"


namespace Kratos
{
/**
 * @class IntegrationPointCurveOnSurface3d
 * @ingroup KratosCore
 * @brief A sinlge integration point, that can be used for geometries without 
 *        a predefined integration scheme, i.e. they can handle material point elements,
 *        isogeometric analysis elements or standard finite elements which are defined
 *        at a single integration point.
 *        This point defines a line segment described on a underlying surface.
 *        Shape functions and integration types have to be precomputed and are set from 
 *        from outside.
 */
template<class TPointType> class IntegrationPointCurveOnSurface3d
    : public Geometry<TPointType>
{
public:

    /** Geometry as base class. */
    typedef Geometry<TPointType> BaseType;

    typedef Geometry<TPointType> GeometryType;

    /**
     * Pointer definition of IntegrationPointCurveOnSurface3d
     */
    KRATOS_CLASS_POINTER_DEFINITION( IntegrationPointCurveOnSurface3d );

    /** Integration methods implemented in geometry. */
    typedef GeometryData::IntegrationMethod IntegrationMethod;

    /** Redefinition of template parameter TPointType. */
    typedef TPointType PointType;

    /** Type used for indexing in geometry class.std::size_t used for indexing
    point or integration point access methods and also all other
    methods which need point or integration point index. */
    typedef typename BaseType::IndexType IndexType;

    /** This typed used to return size or dimension in
    geometry. Dimension, WorkingDimension, PointsNumber and
    ... return this type as their results. */
    typedef typename BaseType::SizeType SizeType;

    /** Array of counted pointers to point. This type used to hold
    geometry's points. */
    typedef  typename BaseType::PointsArrayType PointsArrayType;

    typedef array_1d<double, 2> TangentsArrayType;

    ///@}
    ///@name Life Cycle
    ///@{

    IntegrationPointCurveOnSurface3d(
        const PointsArrayType& ThisPoints,
        const CoordinatesArrayType& rLocalCoordinates,
        const TangentsArrayType& rTangents,
        const double& rIntegrationWeight,
        ShapeFunctionsDerivativesVectorType& rShapeFunctionsDerivativesVector)
        : BaseType( ThisPoints, nullptr )
    {
        msGeometryData = GeometryData(3, 3, 2);

        mpGeometryData = &mGeometryData;

        IntegrationPoint(rLocalCoordinates[0], rLocalCoordinates[1], rIntegrationWeight);

        IntegrationPointsContainerType IntegrationPoints = IntegrationPointsContainerType(1);
        IntegrationPoints[0] = IntegrationPoint;

        msGeometryData.SetGeometryData(IntegrationPoints, rShapeFunctionsDerivativesVector);
    }

    IntegrationPointCurveOnSurface3d(
        const PointsArrayType& ThisPoints,
        const IntgrationPoint& rIntegrationPoint,
        ShapeFunctionsDerivativesVectorType& rShapeFunctionsDerivativesVector)
        : BaseType(ThisPoints, nullptr)
    {
        msGeometryData = GeometryData(3, 3, 2);

        mpGeometryData = &mGeometryData;

        IntegrationPointsContainerType IntegrationPoints = IntegrationPointsContainerType(1);
        IntegrationPoints[0] = rIntegrationPoint;

        msGeometryData.SetGeometryData(rIntegrationPoint, rShapeFunctionsDerivativesVector);
    }

    /**
     * Copy constructor.
     * Constructs this geometry as a copy of given geometry.
     *
     * @note This copy constructor does not copy the points, thus,
     * the new geometry shares points with the source geometry. 
     * Any changes to the new geometry points affect the source
     * geometry points too.
     */
    IntegrationPointCurveOnSurface3d( IntegrationPointCurveOnSurface3d const& rOther )
        : BaseType( rOther )
    {
    }

    /**
     * Copy constructor from a geometry with other point type.
     * Construct this geometry as a copy of given geometry which
     * has different type of points. The given goemetry's
     * TOtherPointType* must be implicity convertible to this
     * geometry PointType.
     *
     * @note This copy constructor does not copy the points, thus,
     * the new geometry shares points with the source geometry.
     * Any changes to the new geometry points affect the source
     * geometry points too.
     */
    template<class TOtherPointType> IntegrationPointCurveOnSurface3d(
        IntegrationPointCurveOnSurface3d<TOtherPointType> const& rOther )
        : BaseType( rOther )
    {
    }

    /**
     * Destructor. Does nothing!!!
     */
    ~IntegrationPointCurveOnSurface3d() override {}

    GeometryData::KratosGeometryFamily GetGeometryFamily() const override
    {
        return GeometryData::Kratos_generic_family;
    }

    GeometryData::KratosGeometryType GetGeometryType() const override
    {
        return GeometryData::Kratos_generic_type;
    }

    /**
     * Operators
     */

    /**
     * Assignment operator.
     *
     * @note This copy constructor does not copy the points, thus,
     * the new geometry shares points with the source geometry.
     * Any changes to the new geometry points affect the source
     * geometry points too.
     *
     * @see Clone
     * @see ClonePoints
     */
    IntegrationPointCurveOnSurface3d& operator=( const IntegrationPointCurveOnSurface3d& rOther )
    {
        BaseType::operator=( rOther );

        return *this;
    }

    /**
     * Assignment operator for geometries with different point type.
     *
     * @note This copy constructor does not copy the points, thus,
     * the new geometry shares points with the source geometry.
     * Any changes to the new geometry points affect the source
     * geometry points too.
     *
     * @see Clone
     * @see ClonePoints
     */
    template<class TOtherPointType>
    IntegrationPointCurveOnSurface3d& operator=( IntegrationPointCurveOnSurface3d<TOtherPointType> const & rOther )
    {
        BaseType::operator=( rOther );

        return *this;
    }

    ///@}
    ///@name Operations
    ///@{
    typename BaseType::Pointer Create( PointsArrayType const& ThisPoints ) const override
    {
        return typename BaseType::Pointer( new IntegrationPointCurveOnSurface3d( ThisPoints ) );
    }

    ///@}
    /** Calculates global location of this integration point.

    \f[
    c_i = \sum_j^n(x_j)*x_i
    \f]

    j is the index of the node and i the global direction (x,y,z).

    @return Point which is the location of this geometry.
    */
    override Point Center() const
    {
        const SizeType points_number = PointsNumber();

        Point location = ZeroVector(3);
        const Matrix& ShapeFunctionValues();

        for (IndexType i = 0; i < PointsNumber(); ++i) {
            location.Coordinates() += (*this)[i].Coordinates()* Matrix(0, i);
        }
        return location;
    }


    /** Determinant of jacobians for given integration method. This
    method calculate determinant of jacobian in all
    integrations points of given integration method.

    @return Vector of double which is vector of determinants of
    jacobians \f$ |J|_i \f$ where \f$ i=1,2,...,n \f$ is the
    integration point index of given integration method.

    @see Jacobian
    @see InverseOfJacobian
    */
    override Vector& DeterminantOfJacobian(Vector& rResult, IntegrationMethod ThisMethod) const
    {
        if (rResult.size() != this->IntegrationPointsNumber(ThisMethod))
            rResult.resize(this->IntegrationPointsNumber(ThisMethod), false);

        for (unsigned int pnt = 0; pnt < this->IntegrationPointsNumber(ThisMethod); pnt++)
        {
            rResult[pnt] = DeterminantOfJacobian(
                0, ThisMethod);
        }
        return rResult;
    }

    /** Determinant of jacobian in specific integration point of
    given integration method. This method calculate determinant
    of jacobian in given integration point of given integration
    method.

    The tangential integration weight is already applied to the
    length of the line segment.

    @param IntegrationPointIndex index of integration point which jacobians has to
    be calculated in it.

    @param IntegrationPointIndex index of integration point
    which determinant of jacobians has to be calculated in it.

    @return Determinamt of jacobian matrix \f$ |J|_i \f$ where \f$
    i \f$ is the given integration point index of given
    integration method.

    @see Jacobian
    @see InverseOfJacobian
    */
    override double DeterminantOfJacobian(
        IndexType IntegrationPointIndex,
        IntegrationMethod ThisMethod) const
    {
        Matrix J;
        this->Jacobian(J, IntegrationPointIndex, ThisMethod);

        array_1d<double, 3> a_1 = row(J, 0);
        array_1d<double, 3> a_2 = row(J, 1);

        return std::norm_2(a_1 * mTangents[0] + a_2 * mTangents[1]);
    }

    /** Determinant of jacobian in given point. This method calculate determinant of jacobian
    matrix in given point.

    @param rPoint point which determinant of jacobians has to
    be calculated in it.

    @return Determinamt of jacobian matrix \f$ |J| \f$ in given
    point.

    @see DeterminantOfJacobian
    @see InverseOfJacobian
    */
    override double DeterminantOfJacobian(const CoordinatesArrayType& rPoint) const
    {
        return DeterminantOfJacobian(
            0,
            mpGeometryData->DefaultIntegrationMethod());
    }


    virtual Matrix Tangents(
        Matrix& rResult,
        IndexType IntegrationPointIndex,
        IntegrationMethod ThisMethod) const
    {
        Matrix J;
        this->Jacobian(J, IntegrationPointIndex, ThisMethod);

        array_1d<double, 3> a_1 = row(J, 0);
        array_1d<double, 3> a_2 = row(J, 1);

        // To Be done: rResult =

        return rResult;
    }

    ///@}
    ///@name Information
    ///@{
    std::string Info() const override
    {
        return "2 dimensional single line integration point defined in 3D space.";
    }

    /**
     * Print information about this object.
     * @param rOStream Stream to print into it.
     * @see PrintData()
     * @see Info()
     */
    void PrintInfo( std::ostream& rOStream ) const override
    {
        rOStream << "2 dimensional single line integration point defined in 3D space.";
    }

    /**
     * Print geometry's data into given stream.
     * Prints it's points by the order they stored in
     * the geometry and then center point of geometry.
     *
     * @param rOStream Stream to print into it.
     * @see PrintInfo()
     * @see Info()
     */
    void PrintData( std::ostream& rOStream ) const override
    {
        BaseType::PrintData( rOStream );
        std::cout << std::endl;
        Matrix jacobian;
        Jacobian( jacobian, PointType() );
        rOStream << "    Jacobian in the integration point\t : " << jacobian;
    }
    ///@}

protected:

    /**
    * there are no protected class members
     */

private:
    ///@name Static Member Variables
    ///@{
    GeometryData mGeometryData;

    array_1d<double, 2> mTangents;

    ///@}
    ///@name Serialization
    ///@{

    friend class Serializer;

    void save( Serializer& rSerializer ) const override
    {
        KRATOS_SERIALIZE_SAVE_BASE_CLASS( rSerializer, BaseType );
    }

    void load( Serializer& rSerializer ) override
    {
        KRATOS_SERIALIZE_LOAD_BASE_CLASS( rSerializer, BaseType );
    }

    IntegrationPointCurveOnSurface3d(): BaseType( PointsArrayType(), nullptr ) {}

    /**
     * Private Friends
     */

    template<class TOtherPointType> friend class IntegrationPointCurveOnSurface3d;

    /**
     * Un accessible methods
     */

}; // Class Geometry

/**
 * Input and output
 */
/**
 * input stream function
 */
template< class TPointType > inline std::istream& operator >> (
    std::istream& rIStream,
    IntegrationPointCurveOnSurface3d<TPointType>& rThis );

/**
         * output stream function
 */
template<class TPointType> inline std::ostream& operator << (
    std::ostream& rOStream,
    const IntegrationPointCurveOnSurface3d<TPointType>& rThis )
{
    rThis.PrintInfo( rOStream );
    rOStream << std::endl;
    rThis.PrintData( rOStream );
    return rOStream;
}

}  // namespace Kratos.

#endif // KRATOS_INTEGRATION_POINT_CURVE_ON_SURFACE_3D_H_INCLUDED  defined 
