#include "recordsCompany.h"

void RecordsCompany::updateCustomers(AVLTree<std::shared_ptr<Customer>, int> * root)
{
        if(root->getHeight() == -1)
        {
            return;
        }
    	if (root->getLeft())
		{
			updateCustomers(root->getLeft());
        }
        root->getData()->newMonth();
        if(root->getRight())
        {
            updateCustomers(root->getRight());
        }
}

void RecordsCompany::updateCustomers(PrizeTree<std::shared_ptr<Customer>, int> * root)
{
        if(root->getHeight() == -1)
        {
            return;
        }
    	if (root->getLeft())
		{
			updateCustomers(root->getLeft());
        }
        root->setExtra(0);
        if(root->getRight())
        {
            updateCustomers(root->getRight());
        }
}

RecordsCompany::RecordsCompany() : m_numOfCustomers(0), m_numOfRecrods(0), m_customers(HashTable<int, std::shared_ptr<Customer> >()), m_records(HashTable<int, std::shared_ptr<Record> >()), recordStacks(UnionFind<int>()), m_prizeTree(new PrizeTree<std::shared_ptr<Customer>, int>())
{
}

RecordsCompany::~RecordsCompany()
{
    delete m_prizeTree;
}

StatusType RecordsCompany::newMonth(int *records_stocks, int number_of_records)
{
    if (records_stocks == nullptr || number_of_records <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    try
    {
        m_numOfRecrods = number_of_records;
        m_records.reset();
        for (int i = 0; i < number_of_records; i++)
        {
            m_records.addElement(shared_ptr<Record>(new Record(i, records_stocks[i])), i);
        }
        recordStacks = UnionFind<int>(records_stocks, records_stocks, number_of_records);
        AVLTree<std::shared_ptr<Customer>, int>** cust_table = m_customers.getTable();

        for (int i = 0; i < m_customers.getSize(); i++)
        {
            updateCustomers(cust_table[i]);
        }
        updateCustomers(m_prizeTree);

        
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
        m_prizeTree->insert(ptr, ptr->getID());
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

StatusType RecordsCompany::addPrize(int c_id1, int c_id2, double amount)
{
    if (c_id1 < 0 || c_id2 < 0 || amount <= 0 || c_id1 >= c_id2)
    {
        return StatusType::INVALID_INPUT;
    }
    try
    {
        m_prizeTree->addPrize(amount, c_id2);
        m_prizeTree->addPrize(-1 * amount, c_id1);
    }
    catch (std::bad_alloc const &)
    {
        return StatusType::ALLOCATION_ERROR;
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
        if(!m_customers.getElement(c_id)->isMember()){
            return Output_t<double>(0);
        }
        expences = m_customers.getElement(c_id)->getExpences() - m_prizeTree->getSum(m_prizeTree->find(c_id));
    }
    catch (NotFound)
    {
        return Output_t<double>(StatusType::DOESNT_EXISTS);
    }
    return Output_t<double>(expences);
}

StatusType RecordsCompany::putOnTop(int r_id1, int r_id2)
{
    if (r_id1 < 0 || r_id2 < 0 || r_id1 >= m_numOfRecrods || r_id2 >= m_numOfRecrods)
    {
        return StatusType::INVALID_INPUT;
    }
    try
    {
        recordStacks.unionGroups(r_id1, r_id2);
    }
    catch (std::bad_alloc const &)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    catch (NotFound)
    {
        return StatusType::DOESNT_EXISTS;
    }
    return StatusType::SUCCESS;
}

StatusType RecordsCompany::getPlace(int r_id, int *column, int *hight)
{
    if (r_id < 0 || r_id >= m_numOfRecrods)
    {
        return StatusType::INVALID_INPUT;
    }
    try
    {
        *column = recordStacks.find(r_id);
        *hight = recordStacks.getHeight(r_id);
    }
    catch (NotFound)
    {
        return StatusType::DOESNT_EXISTS;
    }
    return StatusType::SUCCESS;
}
