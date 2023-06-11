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
    if (c_id < 0 || phone < 0)
    {
        return StatusType::INVALID_INPUT;
    }
    try
    {
        m_customers.addElement(shared_ptr<Customer>(new Customer(c_id, phone)), c_id);
    }
    catch (std::bad_alloc const &)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    catch (Exist)
    {
        return StatusType::ALREADY_EXISTS;
    }
    return StatusType::SUCCESS;
}

Output_t<int> RecordsCompany::getPhone(int c_id)
{
    if (c_id < 0)
    {
        return StatusType::INVALID_INPUT;
    }
    int phone;
    try
    {
        phone = m_customers.getElement(c_id)->getPhone();
    }
    catch (NotFound)
    {
        return Output_t<int>(StatusType::DOESNT_EXISTS);
    }
    return Output_t<int>(phone);
}

StatusType RecordsCompany::makeMember(int c_id)
{
    if (c_id < 0)
    {
        return StatusType::INVALID_INPUT;
    }
    shared_ptr<Customer> ptr;
    try
    {
        ptr = m_customers.getElement(c_id);
        if (ptr->isMember())
        {
            return StatusType::ALREADY_EXISTS;
        }
        ptr->makeMember();
    }
    catch (NotFound)
    {
        return StatusType::DOESNT_EXISTS;
    }
	catch (std::bad_alloc const&)
	{
		return StatusType::ALLOCATION_ERROR;
	}
    return StatusType::SUCCESS;
}

Output_t<bool> RecordsCompany::isMember(int c_id)
{
    if (c_id < 0)
    {
        return Output_t<bool>(StatusType::INVALID_INPUT);
    }
    bool isMember;
    try
    {
        isMember = m_customers.getElement(c_id)->isMember();
    }
    catch (NotFound)
    {
        return Output_t<bool>(StatusType::DOESNT_EXISTS);
    }

    return Output_t<bool>(isMember);
}

StatusType RecordsCompany::buyRecord(int c_id, int r_id)
{
    if (c_id < 0 || r_id < 0)
    {
        return StatusType::INVALID_INPUT;
    }
    if(r_id >= m_numOfRecrods){
        return StatusType::DOESNT_EXISTS;
    }
    try
    {
        shared_ptr<Customer> customer = m_customers.getElement(c_id);
        shared_ptr<Record> record = m_records.getElement(r_id);
        customer->pay(100 + record->getSales());
        record->sold();
    }
    catch (NotFound)
    {
        return StatusType::DOESNT_EXISTS;
    }
    return StatusType::SUCCESS;
}

Output_t<double> RecordsCompany::getExpenses(int c_id)
{
    if (c_id < 0)
    {
        return StatusType::INVALID_INPUT;
    }
    double expences;
    try
    {
        expences = m_customers.getElement(c_id)->getExpences();
    }
    catch (NotFound)
    {
        return Output_t<double>(StatusType::DOESNT_EXISTS);
    }
    return Output_t<double>(expences);
}

StatusType RecordsCompany::putOnTop(int r_id1, int r_id2)
{
    return StatusType();
}

StatusType RecordsCompany::getPlace(int r_id, int *column, int *hight)
{
    return StatusType();
}
