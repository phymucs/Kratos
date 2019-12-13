// KRATOS  / ___|___/ ___|(_)_ __ ___  _   _| | __ _| |_(_) ___  _ ___
//        | |   / _ \___ \| | '_ ` _ \| | | | |/ _` | __| |/ _ \| '_  |
//        | |__| (_) |__) | | | | | | | |_| | | (_| | |_| | (_) | | | |
//         \____\___/____/|_|_| |_| |_|\__,_|_|\__,_|\__|_|\___/|_| |_|
//
//  License:		 BSD License
//                   license: CoSimulationApplication/license.txt
//
//  Main authors:    Philipp Bucher
//

#ifndef KRATOS_CO_SIM_IO_IMPL_H_INCLUDED
#define KRATOS_CO_SIM_IO_IMPL_H_INCLUDED

/*
This file contains the implementation of the functions defined in "co_sim_io.h"
*/

// System includes
#include <string>
#include <memory>

// Project includes
#include "co_sim_connection.h"

namespace CoSimIO {

namespace Internals {
// TODO make sure this is unique even across compilation units (test somehow)
static std::unordered_map<std::string, std::unique_ptr<CoSimConnection>> s_co_sim_connections;

static bool HasIO(const std::string& rConnectionName)
{
    return s_co_sim_connections.find(rConnectionName) != s_co_sim_connections.end();
}

static CoSimConnection& GetConnection(const std::string& rConnectionName)
{
    KRATOS_CO_SIM_ERROR_IF_NOT(HasIO(rConnectionName)) << "Trying to use connection \"" << rConnectionName << "\" which does not exist!" << std::endl;
    return *s_co_sim_connections.at(rConnectionName);
}

} // namespace Internals

inline void Connect(const std::string& rConnectionName, CoSimIO::SettingsType Settings)
{
    using namespace Internals;
    KRATOS_CO_SIM_ERROR_IF(HasIO(rConnectionName)) << "A connection for \"" << rConnectionName << "\" already exists!" << std::endl;

    s_co_sim_connections[std::string(rConnectionName)] = std::unique_ptr<CoSimConnection>(new CoSimConnection(rConnectionName, Settings));
    GetConnection(rConnectionName).Connect();
}

inline void Connect(const std::string& rConnectionName, const std::string& rSettingsFileName)
{
    Connect(rConnectionName, Internals::ReadSettingsFile(rSettingsFileName)); // forward call to funciton above
}

inline void Disconnect(const std::string& rConnectionName)
{
    using namespace Internals;
    KRATOS_CO_SIM_ERROR_IF_NOT(HasIO(rConnectionName)) << "Trying to disconnect connection \"" << rConnectionName << "\" which does not exist!" << std::endl;

    GetConnection(rConnectionName).Disconnect();
    s_co_sim_connections.erase(std::string(rConnectionName));
}

// Version for C++, there this input is a std::vector, which we have to wrap before passing it on
template<>
inline void ImportData(
    const std::string& rConnectionName,
    const std::string& rIdentifier,
    std::vector<double>& rData)
{
    using namespace CoSimIO::Internals;
    std::unique_ptr<DataContainer<double>> p_container(new DataContainerStdVector<double>(rData));
    GetConnection(rConnectionName).ImportData(rIdentifier, *p_container);
}

// Version for C and fortran, there we already get a container
template<>
inline void ImportData(
    const std::string& rConnectionName,
    const std::string& rIdentifier,
    CoSimIO::Internals::DataContainer<double>& rData)
{
    Internals::GetConnection(rConnectionName).ImportData(rIdentifier, rData);
}

// Version for C++, there this input is a std::vector, which we have to wrap before passing it on
template<>
inline void ExportData(
    const std::string& rConnectionName,
    const std::string& rIdentifier,
    std::vector<double>& rData)
{
    using namespace CoSimIO::Internals;
    std::unique_ptr<DataContainer<double>> p_container(new DataContainerStdVector<double>(rData));
    GetConnection(rConnectionName).ExportData(rIdentifier, *p_container);
}

// Version for C and fortran, there we already get a container
template<>
inline void ExportData(
    const std::string& rConnectionName,
    const std::string& rIdentifier,
    CoSimIO::Internals::DataContainer<double>& rData)
{
    Internals::GetConnection(rConnectionName).ExportData(rIdentifier, rData);
}

template<>
inline void ImportMesh(
    const std::string& rConnectionName,
    const std::string& rIdentifier,
    std::vector<double>& rNodalCoordinates,
    std::vector<int>& rElementConnectivities,
    std::vector<int>& rElementTypes)
{
    using namespace CoSimIO::Internals;
    std::unique_ptr<DataContainer<double>> p_container_coords(new DataContainerStdVector<double>(rNodalCoordinates));
    std::unique_ptr<DataContainer<int>> p_container_conn(new DataContainerStdVector<int>(rElementConnectivities));
    std::unique_ptr<DataContainer<int>> p_container_types(new DataContainerStdVector<int>(rElementTypes));
    Internals::GetConnection(rConnectionName).ImportMesh(rIdentifier, *p_container_coords, *p_container_conn, *p_container_types);
}

template<>
inline void ImportMesh(
    const std::string& rConnectionName,
    const std::string& rIdentifier,
    CoSimIO::Internals::DataContainer<double>& rNodalCoordinates,
    CoSimIO::Internals::DataContainer<int>& rElementConnectivities,
    CoSimIO::Internals::DataContainer<int>& rElementTypes)
{
    Internals::GetConnection(rConnectionName).ImportMesh(rIdentifier, rNodalCoordinates, rElementConnectivities, rElementTypes);
}

template<>
inline void ExportMesh(
    const std::string& rConnectionName,
    const std::string& rIdentifier,
    std::vector<double>& rNodalCoordinates,
    std::vector<int>& rElementConnectivities,
    std::vector<int>& rElementTypes)
{
    using namespace CoSimIO::Internals;
    std::unique_ptr<DataContainer<double>> p_container_coords(new DataContainerStdVector<double>(rNodalCoordinates));
    std::unique_ptr<DataContainer<int>> p_container_conn(new DataContainerStdVector<int>(rElementConnectivities));
    std::unique_ptr<DataContainer<int>> p_container_types(new DataContainerStdVector<int>(rElementTypes));
    Internals::GetConnection(rConnectionName).ExportMesh(rIdentifier, *p_container_coords, *p_container_conn, *p_container_types);
}

template<>
inline void ExportMesh(
    const std::string& rConnectionName,
    const std::string& rIdentifier,
    CoSimIO::Internals::DataContainer<double>& rNodalCoordinates,
    CoSimIO::Internals::DataContainer<int>& rElementConnectivities,
    CoSimIO::Internals::DataContainer<int>& rElementTypes)
{
    Internals::GetConnection(rConnectionName).ExportMesh(rIdentifier, rNodalCoordinates, rElementConnectivities, rElementTypes);
}

inline void IsConverged(const std::string& rConnectionName, int& rConvergenceSignal)
{
    Internals::GetConnection(rConnectionName).IsConverged(rConvergenceSignal);
}

inline void SendControlSignal(
    const std::string& rConnectionName,
    const std::string& rIdentifier,
    const CoSimIO::ControlSignal Signal)
{
    Internals::GetConnection(rConnectionName).SendControlSignal(rIdentifier, Signal);
}

inline void Run(const std::string& rConnectionName)
{
    Internals::GetConnection(rConnectionName).Run();
}

template<typename TFunctionType>
inline void Register(
    const std::string& rConnectionName,
    const std::string& rFunctionName,
    TFunctionType rFunction)
{
    // TODO If I use structs (base-class etc, constructed right here) then I can save all of them in one map and do the corresponding actions with them, since I know thich interface-fct to call!
    // => this means that I have to specialize this fct, but the CoSimConnection class will be much cleaner
    // (maybe internally they could be registered as void* to void* but probably not (a good idea))
    Internals::GetConnection(rConnectionName).Register(rFunctionName, rFunction);
}

} // namespace CoSimIO

#endif // KRATOS_CO_SIM_IO_IMPL_H_INCLUDED