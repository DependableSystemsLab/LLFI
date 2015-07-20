


 public:
  virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit,char *buf) { 
   //  Target= *buf
    int * Target= (int *)buf;  
   //write your code here
     buf= (char*) Target;
  }
};

