//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ \.
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:         BSD License
//                   Kratos default license: kratos/license.txt
//
//  Main authors:    Jordi Cotela
//                   Suneth Warnakulasuriya (https://github.com/sunethwarna)
//

#if !defined(KRATOS_TURBULENCE_EVM_K_EPSILON_PROCESS_H_INCLUDED)
#define KRATOS_TURBULENCE_EVM_K_EPSILON_PROCESS_H_INCLUDED

// System includes
#include <iostream>
#include <string>

// Project includes
#include "includes/cfd_variables.h"
#include "includes/communicator.h"
#include "includes/kratos_parameters.h"
#include "includes/model_part.h"
#include "processes/process.h"
#include "solving_strategies/builder_and_solvers/residualbased_block_builder_and_solver.h"
#include "solving_strategies/strategies/residualbased_newton_raphson_strategy.h"
#include "solving_strategies/strategies/solving_strategy.h"
#include "utilities/color_utilities.h"
#include "utilities/variable_utils.h"

// Application includes
#include "custom_elements/evm_k_epsilon/evm_epsilon_element.h"
#include "custom_elements/evm_k_epsilon/evm_k_element.h"
#include "custom_elements/evm_k_epsilon/evm_k_epsilon_utilities.h"
#include "custom_processes/turbulence_eddy_viscosity_model_process.h"
#include "custom_strategies/evm_k_epsilon/residual_based_bossak_turbulent_energy_dissipation_scheme.h"
#include "custom_strategies/evm_k_epsilon/residual_based_bossak_turbulent_kinetic_energy_scheme.h"
#include "custom_strategies/general_convergence_criteria.h"
#include "custom_utilities/rans_calculation_utilities.h"
#include "rans_constitutive_laws_application_variables.h"

namespace Kratos
{
///@name Kratos Classes
///@{

template <unsigned int TDim, class TSparseSpace, class TDenseSpace, class TLinearSolver>
class TurbulenceEvmKEpsilonProcess
    : public TurbulenceEddyViscosityModelProcess<TDim, TSparseSpace, TDenseSpace, TLinearSolver>
{
public:
    ///@name Type Definitions
    ///@{

    /// Pointer definition of TurbulenceEvmKEpsilonProcess
    KRATOS_CLASS_POINTER_DEFINITION(TurbulenceEvmKEpsilonProcess);

    typedef TurbulenceEddyViscosityModelProcess<TDim, TSparseSpace, TDenseSpace, TLinearSolver> BaseType;

    typedef Node<3> NodeType;

    typedef Geometry<NodeType> GeometryType;

    typedef SolvingStrategy<TSparseSpace, TDenseSpace, TLinearSolver> SolvingStrategyType;

    typedef SolvingStrategy<TSparseSpace, TDenseSpace, TLinearSolver> StrategyType;

    typedef Scheme<TSparseSpace, TDenseSpace> SchemeType;

    typedef typename SchemeType::Pointer SchemePointerType;

    typedef typename SchemeType::DofsArrayType DofsArrayType;

    typedef typename SchemeType::TSystemMatrixType SystemMatrixType;

    typedef typename SchemeType::TSystemVectorType SystemVectorType;

    typedef BuilderAndSolver<TSparseSpace, TDenseSpace, TLinearSolver> BuilderAndSolverType;

    typedef typename BuilderAndSolverType::Pointer BuilderAndSolverPointerType;

    typedef ConvergenceCriteria<TSparseSpace, TDenseSpace> ConvergenceCriteriaType;

    typedef typename ConvergenceCriteriaType::Pointer ConvergenceCriteriaPointerType;

    ///@}
    ///@name Life Cycle
    ///@{

    /// Constructor.
    TurbulenceEvmKEpsilonProcess(ModelPart& rModelPart, Parameters& rParameters, Process& rRansYPlusProcess)
        : TurbulenceEddyViscosityModelProcess<TDim, TSparseSpace, TDenseSpace, TLinearSolver>(
              rModelPart, rRansYPlusProcess)
    {
        KRATOS_TRY

        KRATOS_INFO("TurbulenceModel")
            << "Initializing k-epsilon turbulence model" << std::endl;

        Parameters default_parameters = Parameters(R"(
        {
            "relative_tolerance": 1e-3,
            "absolute_tolerance": 1e-5,
            "max_iterations": 10,
            "echo_level": 2
        })");

        rParameters.ValidateAndAssignDefaults(default_parameters);

        this->mTurbulentViscosityRelativeTolerance =
            rParameters["relative_tolerance"].GetDouble();
        this->mTurbulentViscosityAbsoluteTolerance =
            rParameters["absolute_tolerance"].GetDouble();
        this->mMaximumCouplingIterations = rParameters["max_iterations"].GetInt();

        KRATOS_CATCH("");
    }

    /// Destructor.
    virtual ~TurbulenceEvmKEpsilonProcess()
    {
    }

    ///@}
    ///@name Operators
    ///@{

    ///@}
    ///@name Operations
    ///@{

    void AddStrategy(SolvingStrategyType* pStrategy)
    {
        mrSolvingStrategiesList.push_back(pStrategy);
    }

    virtual void Execute() override
    {
        const ProcessInfo& r_process_info = this->mrModelPart.GetProcessInfo();

        if (!r_process_info[IS_CO_SOLVING_PROCESS_ACTIVE])
            return;

        KRATOS_INFO_IF("TurbulenceModel", this->mEchoLevel > 0)
            << "Solving RANS equations...\n";
        this->SolveStep();
    }

    /// this function will be executed at every time step BEFORE performing the solve phase
    virtual void ExecuteFinalizeSolutionStep() override
    {
        KRATOS_TRY

        this->UpdateFluidViscosity();

        KRATOS_CATCH("");
    }

    ///@}
    ///@name Access
    ///@{

    ///@}
    ///@name Inquiry
    ///@{

    ///@}
    ///@name Input and output
    ///@{

    /// Turn back information as a string.
    virtual std::string Info() const override
    {
        return std::string("TurbulenceEvmKEpsilonProcess");
    }

    /// Print information about this object.
    virtual void PrintInfo(std::ostream& rOStream) const override
    {
        rOStream << this->Info();
    }

    /// Print object's data.
    virtual void PrintData(std::ostream& rOStream) const override
    {
    }

    ///@}
    ///@name Friends
    ///@{

    ///@}

protected:
    ///@name Protected Operations
    ///@{

    ///@}

private:
    ///@name Static Member Variables
    ///@{

    ///@}
    ///@name Member Variables
    ///@{

    int mMaximumCouplingIterations;

    int mEchoLevel;

    double mTurbulentViscosityRelativeTolerance;

    double mTurbulentViscosityAbsoluteTolerance;

    std::vector<SolvingStrategyType*> mrSolvingStrategiesList;

    ///@}
    ///@name Private Operators
    ///@{

    void SolveStep()
    {
        this->UpdateTurbulentViscosity();

        for (auto strategy : mrSolvingStrategiesList)
        {
            strategy->InitializeSolutionStep();
            strategy->Predict();
        }

        const int number_of_nodes = this->mrModelPart.NumberOfNodes();
        Vector old_turbulent_viscosity = ZeroVector(number_of_nodes);
        Vector new_turbulent_viscosity = ZeroVector(number_of_nodes);

        bool is_converged = false;
        int step = 1;

        DofsArrayType dummy_dofs;
        SystemMatrixType dummy_matrix;
        SystemVectorType dummy_vector;

        while (!is_converged && (step <= mMaximumCouplingIterations))
        {
#pragma omp parallel for
            for (int i = 0; i < number_of_nodes; ++i)
            {
                old_turbulent_viscosity[i] =
                    (this->mrModelPart.NodesBegin() + i)->FastGetSolutionStepValue(TURBULENT_VISCOSITY);
            }

            for (auto strategy : mrSolvingStrategiesList)
                strategy->SolveSolutionStep();

            this->UpdateTurbulentViscosity();

#pragma omp parallel for
            for (int i = 0; i < number_of_nodes; ++i)
            {
                new_turbulent_viscosity[i] =
                    (this->mrModelPart.NodesBegin() + i)->FastGetSolutionStepValue(TURBULENT_VISCOSITY);
            }

            double increase_norm(0.0), solution_norm(0.0);

#pragma omp parallel for reduction(+ : increase_norm, solution_norm)
            for (int i = 0; i < number_of_nodes; ++i)
            {
                increase_norm += (new_turbulent_viscosity[i] - old_turbulent_viscosity[i])*(new_turbulent_viscosity[i] - old_turbulent_viscosity[i]);
                solution_norm += new_turbulent_viscosity[i]*new_turbulent_viscosity[i];
                // increase_norm += (new_turbulent_viscosity[i] - old_turbulent_viscosity[i]);
                // solution_norm += new_turbulent_viscosity[i];
            }

            if (solution_norm == 0.0)
                solution_norm = 1.0;

            const double ratio = std::abs(increase_norm / solution_norm);
            increase_norm = std::sqrt(increase_norm) / number_of_nodes;

            if (this->mEchoLevel > 0)
                std::cout << "[" << step << "] CONVERGENCE CHECK: TURBULENT_VISCOSITY: ratio = "
                          << std::scientific << ratio << "; exp.ratio = " << std::scientific
                          << mTurbulentViscosityRelativeTolerance
                          << ": abs = " << std::scientific << increase_norm
                          << "; exp.abs = " << std::scientific
                          << mTurbulentViscosityAbsoluteTolerance << std::endl;

            is_converged = (increase_norm < mTurbulentViscosityAbsoluteTolerance) ||
                           (ratio < mTurbulentViscosityRelativeTolerance);

            if (this->mEchoLevel > 0 && is_converged)
                std::cout << "[" << step << "] "
                          << "CONVERGENCE CHECK: TURBULENT_VISCOSITY: "
                             "*** CONVERGENCE IS ACHIEVED ***\n";

            step++;
        }

        if (!is_converged)
        {
            std::cout
                << "|----------------------------------------------------|"
                << std::endl;
            std::cout << "|    " << BOLDFONT(FRED("ATTENTION: Max coupling iterations exceeded"))
                      << "     |" << std::endl;
            std::cout
                << "|----------------------------------------------------|"
                << std::endl;
        }

        for (auto strategy : mrSolvingStrategiesList)
            strategy->FinalizeSolutionStep();
    }

    double CalculateNodalTurbulentViscosity(const ModelPart::NodeIterator& iNode,
                                            const double C_mu,
                                            const unsigned int Step) const
    {
        const double tke = iNode->FastGetSolutionStepValue(TURBULENT_KINETIC_ENERGY, Step);
        const double epsilon =
            iNode->FastGetSolutionStepValue(TURBULENT_ENERGY_DISSIPATION_RATE, Step);
        const double y_plus = iNode->FastGetSolutionStepValue(RANS_Y_PLUS);
        const double f_mu = EvmKepsilonModelUtilities::CalculateFmu(y_plus);

        const double nu_t = EvmKepsilonModelUtilities::CalculateTurbulentViscosity(
            C_mu, tke, epsilon, f_mu);

        return nu_t;
    }

    void UpdateTurbulentViscosity()
    {
        DofsArrayType dummy_dofs;
        SystemMatrixType dummy_matrix;
        SystemVectorType dummy_vector;

        const int number_of_nodes = this->mrModelPart.NumberOfNodes();

        const ProcessInfo& r_current_process_info = this->mrModelPart.GetProcessInfo();

        const double C_mu = r_current_process_info[TURBULENCE_RANS_C_MU];
        const double nu_t_min = r_current_process_info[TURBULENT_VISCOSITY_MIN];
        const double nu_t_max = r_current_process_info[TURBULENT_VISCOSITY_MAX];

#pragma omp parallel for
        for (int i = 0; i < number_of_nodes; i++)
        {
            ModelPart::NodeIterator iNode = this->mrModelPart.NodesBegin() + i;
            const double nu_t = CalculateNodalTurbulentViscosity(iNode, C_mu, 0);
            iNode->FastGetSolutionStepValue(TURBULENT_VISCOSITY) = nu_t;
        }

        RansCalculationUtilities(this->mEchoLevel)
            .WarnIfNegative(this->mrModelPart, TURBULENT_VISCOSITY, "NuT");
        RansCalculationUtilities(this->mEchoLevel)
            .ClipVariable(this->mrModelPart, TURBULENT_VISCOSITY, nu_t_min, nu_t_max);
    }

    void CalculateTurbulentValues(double& TurbulentKineticEnergy,
                                  double& TurbulentEnergyDissipationRate,
                                  const NodeType& rNode,
                                  const ProcessInfo& rProcessInfo)
    {
        const double c_mu = rProcessInfo[TURBULENCE_RANS_C_MU];
        const double von_karman = rProcessInfo[WALL_VON_KARMAN];
        const double y_plus = rNode.FastGetSolutionStepValue(RANS_Y_PLUS, 0);
        const double nu = rNode.FastGetSolutionStepValue(KINEMATIC_VISCOSITY);
        const double wall_distance = rNode.FastGetSolutionStepValue(DISTANCE);

        EvmKepsilonModelUtilities::CalculateTurbulentValues(
            TurbulentKineticEnergy, TurbulentEnergyDissipationRate, y_plus, nu,
            wall_distance, c_mu, von_karman);
    }

    ///@}
    ///@name Un accessible methods
    ///@{

    /// Assignment operator.
    TurbulenceEvmKEpsilonProcess& operator=(TurbulenceEvmKEpsilonProcess const& rOther);

    /// Copy constructor.
    TurbulenceEvmKEpsilonProcess(TurbulenceEvmKEpsilonProcess const& rOther);

    ///@}

}; // Class TurbulenceEvmKEpsilonProcess

///@}

///@name Type Definitions
///@{

///@}
///@name Input and output
///@{

/// input stream function
template <unsigned int TDim, class TSparseSpace, class TDenseSpace, class TLinearSolver>
inline std::istream& operator>>(
    std::istream& rIStream,
    TurbulenceEvmKEpsilonProcess<TDim, TSparseSpace, TDenseSpace, TLinearSolver>& rThis);

/// output stream function
template <unsigned int TDim, class TSparseSpace, class TDenseSpace, class TLinearSolver>
inline std::ostream& operator<<(
    std::ostream& rOStream,
    const TurbulenceEvmKEpsilonProcess<TDim, TSparseSpace, TDenseSpace, TLinearSolver>& rThis)
{
    rThis.PrintInfo(rOStream);
    rOStream << std::endl;
    rThis.PrintData(rOStream);

    return rOStream;
}
///@}

} // namespace Kratos.

#endif // KRATOS_TURBULENCE_EVM_K_EPSILON_PROCESS_H_INCLUDED  defined
