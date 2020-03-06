//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:		 BSD License
//					 Kratos default license: kratos/license.txt
//
//  Main authors:    Anoop Kodakkal, Mate Pentek
//
//

// System includes

// External includes

// Project includes
#include "geometries/geometry.h"
#include "geometries/geometry_data.h"
#include "utilities/openmp_utils.h"
#include "utilities/variable_utils.h"

// Application includes
#include "drag_and_moment_utilities.h"
#include "fluid_dynamics_application_variables.h"

namespace Kratos
{
    /* Public functions *******************************************************/

    array_1d<double, 6> DragAndMomentUtilities::CalculateBodyFittedDragAndMoment(ModelPart& rModelPart, array_1d<double, 3> rReferencePoint) {

        array_1d<double, 6> drag_force_moment = ZeroVector(6);
        double dx = 0.0;
        double dy = 0.0;
        double dz = 0.0;
        double fx = 0.0;
        double fy = 0.0;
        double fz = 0.0;

        #pragma omp parallel for reduction(+:dx,dy,dz,fx,fy,fz)
        for(int i_node = 0; i_node < static_cast<int>(rModelPart.NumberOfNodes()); i_node++){
            auto it_node = rModelPart.NodesBegin() + i_node;
            auto drag = it_node->GetSolutionStepValue(REACTION,0);
            auto x = it_node->X() - rReferencePoint[0];
            auto y = it_node->Y() - rReferencePoint[1];
            auto z = it_node->Z() - rReferencePoint[2];
            dx += -1 * drag[0];
            dy += -1 * drag[1];
            dz += -1 * drag[2];
            fx +=  y * (-1) * drag[2] - z * (-1) * drag[1];
            fy +=  z * (-1) * drag[0] - x * (-1) * drag[2];
            fz +=  x * (-1) * drag[1] - y * (-1) * drag[0];
        }
        // three drag components
        drag_force_moment[0] = dx;
        drag_force_moment[1] = dy;
        drag_force_moment[2] = dz;
        // three base moment components
        drag_force_moment[3] = fx;
        drag_force_moment[4] = fy;
        drag_force_moment[5] = fz;

        // Perform MPI synchronization
        //drag_force_moment = rModelPart.GetCommunicator().GetDataCommunicator().SumAll(drag_force_moment);
        return drag_force_moment;
    }

    std::tuple<array_1d<double, 3>, array_1d<double, 3>> DragAndMomentUtilities::CalculateEmbeddedDragAndMoment(ModelPart& rModelPart, array_1d<double, 3> rReferencePoint) {
        // Initialize total drag force
        array_1d<double, 3> drag_moment = ZeroVector(3);
        array_1d<double, 3> drag_force = ZeroVector(3);
        double& drag_x = drag_force[0];
        double& drag_y = drag_force[1];
        double& drag_z = drag_force[2];
        double& moment_x = drag_moment[0];
        double& moment_y = drag_moment[1];
        double& moment_z = drag_moment[2];

        // Iterate the model part elements to compute the drag
        array_1d<double, 3> elem_drag;
        array_1d<double, 3> elem_drag_center;

        // Auxiliary var to make the reduction
        double drag_x_red = 0.0;
        double drag_y_red = 0.0;
        double drag_z_red = 0.0;
        double moment_x_red = 0.0;
        double moment_y_red = 0.0;
        double moment_z_red = 0.0;

        #pragma omp parallel for reduction(+:drag_x_red, drag_y_red, drag_z_red, moment_x_red, moment_y_red, moment_z_red) private(elem_drag) private(elem_drag_center) schedule(dynamic)
        for(int i = 0; i < static_cast<int>(rModelPart.Elements().size()); ++i){
            auto it_elem = rModelPart.ElementsBegin() + i;
            it_elem->Calculate(DRAG_FORCE_CENTER, elem_drag_center, rModelPart.GetProcessInfo());
            it_elem->Calculate(DRAG_FORCE, elem_drag, rModelPart.GetProcessInfo());
            drag_x_red += elem_drag[0];
            drag_y_red += elem_drag[1];
            drag_z_red += elem_drag[2];            
            auto x = elem_drag_center[0] - rReferencePoint[0];
            if (elem_drag[0] == 0.0) {
               x = 0;
            }
            auto y = elem_drag_center[1] - rReferencePoint[1];
            if (elem_drag[1] == 0.0) {
               y = 0;
            }
            auto z = elem_drag_center[2] - rReferencePoint[2];
            if (elem_drag[2] == 0.0) {
               z = 0;
            }
            moment_x_red += y * elem_drag[2] - z * elem_drag[1];
            moment_y_red += z * elem_drag[0] - x * elem_drag[2];
            moment_z_red += x * elem_drag[1] - y * elem_drag[0];
        }

        drag_x += drag_x_red;
        drag_y += drag_y_red;
        drag_z += drag_z_red;
        moment_x += moment_x_red;
        moment_y += moment_y_red;
        moment_z += moment_z_red;

        // Perform MPI synchronization
        noalias(drag_moment) = rModelPart.GetCommunicator().GetDataCommunicator().SumAll(drag_moment);
        noalias(drag_force) = rModelPart.GetCommunicator().GetDataCommunicator().SumAll(drag_force);
        

        return std::make_tuple<array_1d<double, 3>, array_1d<double,3>>(std::forward<array_1d<double,3>>(drag_force), std::forward<array_1d<double,3>>(drag_moment));
    }

    /* External functions *****************************************************/

    /// output stream function
    inline std::ostream& operator << (
        std::ostream& rOStream,
        const DragAndMomentUtilities& rThis) {

        rThis.PrintData(rOStream);
        return rOStream;
    }

}