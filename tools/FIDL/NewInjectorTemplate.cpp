


 public:
  virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit,char *buf) { 
   //  Target= *buf
    void * Target= (void *)buf;  
   //write your code here
     buf= (char*) Target;
  }
};

