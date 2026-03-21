#include "recursiveCompile.hpp"

int main()
{

    std::vector<DataSegment> datas;
    DataSegment toAdd1;
    toAdd1.dataType = "short";
    toAdd1.elementCount = 3;
    short toAdd1Array[] = {1, 2, 3};
    toAdd1.toDataArray = toAdd1Array;
    datas.push_back(toAdd1);
    datas.push_back(toAdd1);
    datas.push_back(toAdd1);

    int elementCounts[] = {0, 0, 0};
    long totalSum;
    setupCalculation(datas, 0, elementCounts, 0, totalSum);
    std::cout<<totalSum;
}