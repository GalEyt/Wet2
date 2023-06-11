#ifndef CUSTOMER
#define CUSTOMER

class Customer{
private:
    int m_id;
    int m_phone;
    bool m_member = false;
    double m_monthlyExpences = 0;
public:
    Customer(int id, int phone) : m_id(id), m_phone(phone){}
    int getID() const {return m_id;};
    int getPhone() const {return m_phone;};
    double getExpences() const {return m_monthlyExpences;}
    bool isMember() const {return m_member;}
    void makeMember(){m_member = true;}
    void pay(int amount){
        if(m_member){
            m_monthlyExpences+= amount;
        }
    }
    void rewarded(int prize){
        pay(-1 * prize);
    }
};

#endif // CUSTOMER