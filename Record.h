#ifndef RECORD
#define RECORD

class Record{
private:
    int m_id;
    int m_copies = 0;
    int m_sales = 0;
public:
    Record(int id) : m_id(id){}
    int getID() const{
        return m_id;
    }

    int getCopies() const{
        return m_copies;
    }

    int getSales() const{
        return m_sales;
    }

    void sold(){
        m_copies--;
        m_sales++;
    }
};

#endif // RECORD