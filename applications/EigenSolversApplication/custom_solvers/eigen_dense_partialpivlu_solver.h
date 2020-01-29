/*
//  KRATOS _______
//        / ____(_)___ ____  ____
//       / __/ / / __ `/ _ \/ __ \
//      / /___/ / /_/ /  __/ / / /
//     /_____/_/\__, /\___/_/ /_/ SolversApplication
//             /____/
//
//  Author: Quirin Aumann
*/

#if !defined(KRATOS_EIGEN_DENSE_PARTIALPIVLU_SOLVER_H_INCLUDED)
#define KRATOS_EIGEN_DENSE_PARTIALPIVLU_SOLVER_H_INCLUDED

// External includes
#include <Eigen/LU>

// Project includes
#include "includes/define.h"

namespace Kratos {

template <typename TScalar = double>
class EigenDensePartialPivLUSolver
{
public:
    using Scalar = TScalar;
    using Matrix = Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>;
    using Vector = Eigen::Matrix<Scalar, Eigen::Dynamic, 1>;

private:
    Eigen::PartialPivLU<Matrix> m_solver;

public:
    static std::string Name()
    {
        return "complex_dense_partialpivlu";
    }

    void Initialize(Parameters settings)
    {
    }

    bool Compute(Eigen::Map<Matrix> a)
    {
        m_solver.compute(a);

        return true;
    }

    bool Solve(Eigen::Ref<const Vector> b, Eigen::Ref<Vector> x) const
    {
        x = m_solver.solve(b);

        return true;
    }

    void PrintInfo(std::ostream &rOStream) const
    {
        rOStream << "EigenDirectSolver <" << Name() << "> finished.";
    }

    std::string GetSolverErrorMessages() const
    {
        return "No additional information";
    }
};

} // namespace Kratos

#endif // defined(KRATOS_EIGEN_DENSE_PARTIALPIVLU_SOLVER_H_INCLUDED)
