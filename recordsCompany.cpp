#include "recordsCompany.h"

RecordsCompany::RecordsCompany()
{
}

RecordsCompany::~RecordsCompany()
{
}

StatusType RecordsCompany::newMonth(int *records_stocks, int number_of_records)
{
    return StatusType();
}

StatusType RecordsCompany::addCostumer(int c_id, int phone)
{
    return StatusType();
}

Output_t<int> RecordsCompany::getPhone(int c_id)
{
    return Output_t<int>();
}

StatusType RecordsCompany::makeMember(int c_id)
{
    return StatusType();
}

Output_t<bool> RecordsCompany::isMember(int c_id)
{
    return Output_t<bool>();
}

StatusType RecordsCompany::buyRecord(int c_id, int r_id)
{
    return StatusType();
}

StatusType RecordsCompany::addPrize(int c_id1, int c_id2, double amount)
{
    return StatusType();
}

Output_t<double> RecordsCompany::getExpenses(int c_id)
{
    return Output_t<double>();
}

StatusType RecordsCompany::putOnTop(int r_id1, int r_id2)
{
    return StatusType();
}

StatusType RecordsCompany::getPlace(int r_id, int *column, int *hight)
{
    return StatusType();
}
