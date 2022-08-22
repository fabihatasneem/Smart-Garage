class MyClass
{
    long startTime;
    String rfid;
    bool active;

    public:
    MyClass() {}
    
    MyClass(String rfid) 
    {
      this->rfid = rfid;
      this->startTime = 0;
      this->active = false;
    }

    void setActive(bool active) { this->active = active; }  
    bool isActive() { return active; }

    String getRfid() { return rfid; }
 
    void setStartTime(long startTime) { this->startTime = startTime; }
    long getStartTime() { return startTime; }
};