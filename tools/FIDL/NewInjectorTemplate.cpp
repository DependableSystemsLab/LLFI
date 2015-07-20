    public:
    virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit, char *buf) {
        int *Target = (int *) buf;
        //write your code here
        buf = (char *) Target;
    }
};
