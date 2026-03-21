#include <iostream>
#include <vector>

// The purpoes of this file is to learn about variadic templates and the limits of what C++ will compile.
// This is being used in the process of allowing multiple keys for nested loop joins.

struct DataSegment
{
public:
    std::string dataType;
    void *toDataArray;
    int elementCount;
};

template <typename... Types>
void setupCalculation(const std::vector<DataSegment> &data, int columnIndex, int *elementCounts, int alreadyProcessedColumns, long &totalSum, Types *...args)
{

    if (sizeof...(args) == 3)
    {
        performCalculation(std::get<0>(std::forward<Types...>(args...)), std::get<1>(std::forward<Types...>(args...)), std::get<2>(std::forward<Types...>(args...)), elementCounts);
    }

    elementCounts[columnIndex] = data[columnIndex].elementCount;

    if (data[columnIndex].dataType == "short")
    {
        setupCalculation<Types..., short>(data, columnIndex + 1, alreadyProcessedColumns, totalSum, data[columnIndex].toDataArray, args...);
    }

    if (data[columnIndex].dataType == "long")
    {
        setupCalculation<Types..., long>(data, columnIndex + 1, elementCounts, alreadyProcessedColumns, totalSum, data[columnIndex].toDataArray, args...);
    }
}

template <typename T1, typename T2, typename T3>
long performCalculation(T1 *item1, T2 *item2, T3 *item3, int *numbersOfElements)
{
    long total = 0;
    for (int i = 0; i < numbersOfElements[0]; i++)
    {
        total += item1[i];
    }

    for (int i = 0; i < numbersOfElements[1]; i++)
    {
        total += item2[i];
    }

    for (int i = 0; i < numbersOfElements[2]; i++)
    {
        total += item3[i];
    }

    return total;
}

void setupCalculation(const std::vector<DataSegment> &data, int columnIndex, int *elementCounts, int alreadyProcessedColumns, long &totalSum)
{
    elementCounts[columnIndex] = data[columnIndex].elementCount;

    if (data[columnIndex].dataType == "short")
    {
        setupCalculation<short>(data, columnIndex + 1,  alreadyProcessedColumns, totalSum, data[columnIndex].toDataArray);
    }

    if (data[columnIndex].dataType == "long")
    {
        setupCalculation<long>(data, columnIndex + 1, elementCounts, alreadyProcessedColumns, totalSum, data[columnIndex].toDataArray);
    }
}
