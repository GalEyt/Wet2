#ifndef RECORD
#define RECORD

class Record{
private:
    int m_id;
    int m_copies;
    int m_sales;
public:
    Record(int id, int copies) : m_id(id), m_copies(copies), m_sales(0){}
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
        m_sales++;
    }
};

#endif // RECORD