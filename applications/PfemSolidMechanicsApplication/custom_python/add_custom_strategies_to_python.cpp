//
//   Project Name:        KratosPfemSolidMechanicsApplication $
//   Created by:          $Author:                JMCarbonell $
//   Last modified by:    $Co-Author:                         $
//   Date:                $Date:                    July 2013 $
//   Revision:            $Revision:                      0.0 $
//
//

// System includes 

// External includes 
#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/timer.hpp> 


// Project includes
#include "includes/define.h"
#include "custom_python/add_custom_strategies_to_python.h"

#include "spaces/ublas_space.h"

//strategies
#include "solving_strategies/strategies/solving_strategy.h"

//convergence criterias
#include "solving_strategies/convergencecriterias/convergence_criteria.h"


//linear solvers
#include "linear_solvers/linear_solver.h"

//schemes
#include "custom_strategies/schemes/residual_based_bossak_scheme.hpp"
#include "custom_strategies/schemes/residual_based_U_W_bossak_scheme.hpp"
#include "custom_strategies/schemes/residual_based_contact_bossak_scheme.hpp"


#include "custom_strategies/schemes/new_residual_based_U_W_bossak_scheme.hpp"

namespace Kratos
{

  namespace Python
  {		
    using namespace boost::python;

    void  AddCustomStrategiesToPython()
    {
      typedef UblasSpace<double, CompressedMatrix, Vector> SparseSpaceType;
      typedef UblasSpace<double, Matrix, Vector> LocalSpaceType;

      //base types
      //typedef LinearSolver<SparseSpaceType, LocalSpaceType > LinearSolverType;
      //typedef SolvingStrategy< SparseSpaceType, LocalSpaceType, LinearSolverType > BaseSolvingStrategyType;
      //typedef BuilderAndSolver< SparseSpaceType, LocalSpaceType, LinearSolverType > BuilderAndSolverType;
      typedef Scheme< SparseSpaceType, LocalSpaceType > BaseSchemeType;
      //typedef ConvergenceCriteria< SparseSpaceType, LocalSpaceType > ConvergenceCriteriaBaseType;

      //custom scheme types
      typedef ResidualBasedBossakScheme< SparseSpaceType, LocalSpaceType >    ResidualBasedBossakSchemeType;
      typedef ResidualBasedUWBossakScheme< SparseSpaceType, LocalSpaceType >  ResidualBasedUWBossakSchemeType;
      typedef ResidualBasedContactBossakScheme< SparseSpaceType, LocalSpaceType >  ResidualBasedContactBossakSchemeType;    

      typedef NewResidualBasedUWBossakScheme< SparseSpaceType, LocalSpaceType >  NewResidualBasedUWBossakSchemeType;
    

      //********************************************************************
      //*************************BUILDER AND SOLVER*************************
      //********************************************************************
      


      //********************************************************************
      //*************************SHCHEME CLASSES****************************
      //********************************************************************
     
      // Residual Based Bossak Scheme Type
      class_< ResidualBasedBossakSchemeType,
	      bases< BaseSchemeType >,  boost::noncopyable >
	(
	 "ResidualBasedBossakScheme", init< double , double >() )
	
	.def("Initialize", &ResidualBasedBossakScheme<SparseSpaceType, LocalSpaceType>::Initialize)
	;
      

      // Residual Based Bossak Scheme Type
      class_< ResidualBasedUWBossakSchemeType,
	      bases< BaseSchemeType >,  boost::noncopyable >
	(
	 "ResidualBasedUWBossakScheme", init< double , double >() )
   .def(init<>())
   .def(init<double,double>())
   .def(init<double,double,double>())
   .def(init<double,double,double,double,double>())
	.def("Initialize", &ResidualBasedUWBossakScheme<SparseSpaceType, LocalSpaceType>::Initialize)
	;
      
      // Residual Based Bossak Scheme Type
      class_< ResidualBasedContactBossakSchemeType,
	      bases< BaseSchemeType >,  boost::noncopyable >
	(
	 "ResidualBasedContactBossakScheme", init< double , double >() )
	
	.def("Initialize", &ResidualBasedContactBossakScheme<SparseSpaceType, LocalSpaceType>::Initialize)
	;
      
      // Residual Based Displacement Bossak Scheme Type
      class_< NewResidualBasedUWBossakSchemeType,
      	      bases< BaseSchemeType >,  boost::noncopyable >
      	(
      	 "NewResidualBasedUWBossakScheme", init<>() )
      	.def("Initialize", &NewResidualBasedUWBossakScheme<SparseSpaceType, LocalSpaceType>::Initialize)
      	;
      
      //********************************************************************
      //*******************CONVERGENCE CRITERIA CLASSES*********************
      //********************************************************************
      
      
      //********************************************************************
      //*************************STRATEGY CLASSES***************************
      //********************************************************************
      
                             
    }

  }  // namespace Python.

} // Namespace Kratos

