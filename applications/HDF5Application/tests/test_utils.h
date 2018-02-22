//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:		 BSD License
//					 Kratos default license: kratos/license.txt
//
//  Main authors:    Michael Andre, https://github.com/msandre
//

#if !defined(KRATOS_HDF5_TEST_UTILS_H_INCLUDED)
#define KRATOS_HDF5_TEST_UTILS_H_INCLUDED

// System includes
#include <string>

// External includes

// Project includes
#include "custom_io/hdf5_file.h"

namespace Kratos
{

class ModelPart;

namespace Testing
{

template<typename T>
HDF5::File::Vector<T> TestVector(std::size_t n=3)
{
    HDF5::File::Vector<T> vec(n);
    for (std::size_t i = 0; i < n; ++i)
        vec(i) = i;
    return vec;
}

template <>
HDF5::File::Vector<array_1d<double, 3>> TestVector(std::size_t n);

template<typename T>
HDF5::File::Matrix<T> TestMatrix(std::size_t m=3, std::size_t n=3)
{
    HDF5::File::Matrix<T> mat(m, n);
    for (std::size_t i = 0; i < m; ++i)
        for (std::size_t j = 0; j < n; ++j)
            mat(i, j) = i * n + j;
    return mat;
}

void CreateTestModelPart(ModelPart& rModelPart,
                         std::string const& rElementType = "Element2D3N",
                         std::string const& rConditionType = "Condition2D3N");

void CompareElements(HDF5::ElementsContainerType& rElements1, HDF5::ElementsContainerType& rElements2);

void CompareConditions(HDF5::ConditionsContainerType& rConditions1, HDF5::ConditionsContainerType& rConditions2);

void CompareModelParts(ModelPart& rModelPart1, ModelPart& rModelPart2);

HDF5::File::Pointer pGetFile();

} // namespace Testing
} // namespace Kratos.

#endif
