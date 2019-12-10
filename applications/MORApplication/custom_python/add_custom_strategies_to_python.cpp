//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:		 BSD License
//					 Kratos default license: kratos/license.txt
//
//  Main authors:    Author1 Fullname
//                   Author2 Fullname
//


// System includes
// #include <complex>

// External includes
#include <pybind11/pybind11.h>
#include "boost/numeric/ublas/vector.hpp"


// Project includes
#include "includes/define_python.h"
#include "custom_python/add_custom_strategies_to_python.h"

#include "spaces/ublas_space.h"

// Strategies
#include "solving_strategies/strategies/solving_strategy.h"
#include "custom_strategies/custom_strategies/linear_mor_matrix_output_strategy.hpp"
#include "custom_strategies/custom_strategies/mor_offline_second_order_strategy.hpp"
#include "custom_strategies/custom_strategies/mor_online_strategy.hpp"
#include "custom_strategies/custom_strategies/mor_online_second_order_strategy.hpp"
#include "custom_strategies/custom_strategies/frequency_response_analysis_strategy.hpp"
#include "custom_strategies/custom_strategies/mor_second_order_krylov_strategy.hpp"

// Builders and solvers
#include "custom_strategies/custom_builder_and_solvers/system_matrix_builder_and_solver.hpp"

// Linear solvers
#include "linear_solvers/linear_solver.h"

namespace Kratos {
namespace Python {

void  AddCustomStrategiesToPython(pybind11::module& m)
{
    namespace py = pybind11;

    using complex = std::complex<double>;

    typedef UblasSpace<double, CompressedMatrix, Vector> SparseSpaceType;
    typedef UblasSpace<double, Matrix, Vector> LocalSpaceType;
    typedef TUblasSparseSpace<complex> ComplexSpaceType;
    typedef TUblasDenseSpace<complex> ComplexLocalSpaceType;

    // Base types
    typedef LinearSolver<SparseSpaceType, LocalSpaceType > LinearSolverType;
    typedef LinearSolverType::Pointer LinearSolverPointer;
    typedef LinearSolver<ComplexSpaceType, ComplexLocalSpaceType> ComplexLinearSolverType;
    typedef ComplexLinearSolverType::Pointer ComplexLinearSolverPointer;
    typedef SolvingStrategy< SparseSpaceType, LocalSpaceType, LinearSolverType > BaseSolvingStrategyType;
    typedef Scheme< SparseSpaceType, LocalSpaceType > BaseSchemeType;
    typedef BuilderAndSolver< SparseSpaceType, LocalSpaceType, LinearSolverType > BuilderAndSolverType;

    // Custom strategy types
    typedef LinearMorMatrixOutputStrategy< SparseSpaceType, LocalSpaceType, LinearSolverType > LinearMorMatrixOutputStrategyType;
    typedef FrequencyResponseAnalysisStrategy < SparseSpaceType, LocalSpaceType, LinearSolverType > FrequencyResponseAnalysisStrategyType;
    typedef MorOnlineStrategy< SparseSpaceType, LocalSpaceType, LinearSolverType > MorOnlineStrategyType;
    typedef MorOfflineSecondOrderStrategy< SparseSpaceType, LocalSpaceType, LinearSolverType > MorOfflineSecondOrderStrategyType;
    // typedef MorOnlineSecondOrderStrategy< SparseSpaceType, LocalSpaceType, LinearSolverType, ComplexSpaceType, ComplexLocalSpaceType, ComplexLinearSolverType > MorOnlineSecondOrderStrategyType;

    typedef MorSecondOrderKrylovStrategy< SparseSpaceType, LocalSpaceType, LinearSolverType > MorSecondOrderKrylovStrategyType;

    // Custom builder and solver types
    typedef SystemMatrixBuilderAndSolver< SparseSpaceType, LocalSpaceType, LinearSolverType > SystemMatrixBuilderAndSolverType;


    //********************************************************************
    //*************************STRATEGY CLASSES***************************
    //********************************************************************

    py::class_< LinearMorMatrixOutputStrategyType, typename LinearMorMatrixOutputStrategyType::Pointer, BaseSolvingStrategyType >(m,"LinearMorMatrixOutputStrategy")
        .def(py::init < ModelPart&, BaseSchemeType::Pointer, LinearSolverPointer, bool >())
        ;

    py::class_< MorOnlineStrategyType, typename MorOnlineStrategyType::Pointer, BaseSolvingStrategyType >(m,"MorOnlineStrategy")
        .def(py::init < ModelPart&, LinearSolverPointer, MorOfflineSecondOrderStrategyType::Pointer >())
        ;

    py::class_< MorOfflineSecondOrderStrategyType, typename MorOfflineSecondOrderStrategyType::Pointer, BaseSolvingStrategyType >(m,"MorOfflineSecondOrderStrategy")
        .def(py::init < ModelPart&, BaseSchemeType::Pointer, LinearSolverPointer, bool >())
        .def("SetBuilderAndSolver", &MorOfflineSecondOrderStrategyType::SetBuilderAndSolver)
        ;
        
    py::class_< MorSecondOrderKrylovStrategyType, typename MorSecondOrderKrylovStrategyType::Pointer, MorOfflineSecondOrderStrategyType >(m,"MorSecondOrderKrylovStrategy")
        .def(py::init < ModelPart&, BaseSchemeType::Pointer, LinearSolverPointer, vector<double>, bool >())
        ;
    
    py::class_< FrequencyResponseAnalysisStrategyType, typename FrequencyResponseAnalysisStrategyType::Pointer, BaseSolvingStrategyType >(m,"FrequencyResponseAnalysisStrategy")
        .def(py::init < ModelPart&, BaseSchemeType::Pointer, ComplexLinearSolverPointer, bool, bool >())
        .def("GetBuilderAndSolver", &FrequencyResponseAnalysisStrategyType::GetBuilderAndSolver)
        ;

    //********************************************************************
    //*************************BUILDER AND SOLVER*************************
    //********************************************************************

    py::class_< SystemMatrixBuilderAndSolverType, typename SystemMatrixBuilderAndSolverType::Pointer, BuilderAndSolverType >(m, "SystemMatrixBuilderAndSolver")
        .def(py::init < LinearSolverPointer >())
        .def(py::init < LinearSolverPointer, Parameters >())
        .def("BuildEquationIdVector", &SystemMatrixBuilderAndSolverType::BuildEquationIdVector)
        .def("BuildOutputStructure", &SystemMatrixBuilderAndSolverType::BuildOutputStructure)
        ;

}

} // namespace Python.
} // Namespace Kratos