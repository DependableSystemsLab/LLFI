
    public:
    virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit, char *buf) {
        int *Target = (int *) buf;
        // Write your code here!
        
        // END
        buf = (char *) Target;
    }
};

