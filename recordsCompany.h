#ifndef RECORDS_COMPANY_H
#define RECORDS_COMPANY_H

#include "utilesWet2.h"
#include "HashTable.h"
#include "unionFind.h"
#include "Customer.h"
#include "Record.h"
#include "PrizeTree.h"
#include <memory>


class RecordsCompany {
  private:
    int m_numOfCustomers;
    int m_numOfRecrods;
    HashTable<int, std::shared_ptr<Customer> > m_customers;
    HashTable<int, std::shared_ptr<Record> > m_records;
    UnionFind<int> recordStacks;
    PrizeTree<std::shared_ptr<Customer>, int> *m_prizeTree;
    void updateCustomers(AVLTree<std::shared_ptr<Customer>, int>* root);
    void updateCustomers(PrizeTree<std::shared_ptr<Customer>, int>* root);

  public:
    RecordsCompany();
    ~RecordsCompany();
    StatusType newMonth(int *records_stocks, int number_of_records);
    StatusType addCostumer(int c_id, int phone);
    Output_t<int> getPhone(int c_id);
    StatusType makeMember(int c_id);
    Output_t<bool> isMember(int c_id);
    StatusType buyRecord(int c_id, int r_id);
    StatusType addPrize(int c_id1, int c_id2, double  amount);
    Output_t<double> getExpenses(int c_id);
    StatusType putOnTop(int r_id1, int r_id2);
    StatusType getPlace(int r_id, int *column, int *hight);
};

#endif