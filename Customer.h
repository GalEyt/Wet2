#ifndef CUSTOMER
#define CUSTOMER

class Customer{
private:
    int m_id;
    int m_phone;
    bool m_member;
    double m_monthlyExpences;
public:
    Customer(int id, int phone) : m_id(id), m_phone(phone), m_member(false), m_monthlyExpences(0){}
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
    void newMonth(){
        m_monthlyExpences = 0;
    }
};

#endif // CUSTOMER