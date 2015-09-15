#include "FaultInjector.h"
#include "FaultInjectorManager.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

//2^20 == 32MB
#define MEM_EXHAUSTION_UNIT 33554432

class BitCorruptionInjector: public SoftwareFaultInjector {
	public:
	virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit,char *buf){
		unsigned int fi_bytepos = fi_bit/8;
		unsigned int fi_bitpos = fi_bit%8;
		buf[fi_bytepos] ^= 0x1 << fi_bitpos;
		return;
	}
	
	static BitCorruptionInjector* getBitCorruptionInjector(){
		static BitCorruptionInjector* injector_ptr = NULL;
		if(injector_ptr == NULL){
			injector_ptr = new BitCorruptionInjector();
			return injector_ptr;
		}else	return injector_ptr;
	}
};

class MemoryLeakInjector: public SoftwareFaultInjector {
	public:
	virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit,char *buf){
		void* fake_p = malloc(1024 * sizeof(char));
		void** newbuf = (void**) buf;
		*newbuf = fake_p;
		return;
	}
};

class HangInjector: public SoftwareFaultInjector {
	public:
	virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit,char *buf){
		while(1);
		return;
	}
};

class SleepInjector: public SoftwareFaultInjector {
	public:
	virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit,char *buf){
		sleep(3);
		return;
	}
};

static RegisterFaultInjector DA("HighFrequentEvent(Timing)", new SleepInjector());

class ChangeValueInjector: public SoftwareFaultInjector {
	public:
	virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit,char *buf){
		if(is_replace == false){
			int* newbuf = (int*) buf;
			*newbuf = *newbuf + add_val;
		}
		else{
			int* newbuf = (int*) buf;
			*newbuf = rep_val;
		}
		return;
	}
	
	ChangeValueInjector(int val, bool replace):add_val(val), rep_val(val), is_replace(replace){};
	
	private:
	int add_val;
	int rep_val;
	bool is_replace;
};

class InappropriateCloseInjector: public SoftwareFaultInjector {
	public:
	virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit,char *buf){
		if(add_close){
			FILE** newbuf = (FILE**) buf;
			fclose(*newbuf);
		}else{
			FILE* fp = fopen("fake_file.txt", "w");
			FILE** newbuf = (FILE**) buf;
			*newbuf = fp;
		}
		return;
	}
	InappropriateCloseInjector(bool addclose):add_close(addclose){};
	
	private:
	bool add_close;
};

class StalePointerInjector: public SoftwareFaultInjector {
	public:
	virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit,char *buf){
		void** newbuf = (void**) buf;
		free(*newbuf);
	}
};

class MemoryExhaustionInjector: public SoftwareFaultInjector {
	public:
	virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit,char *buf){
		void* p = NULL;
		void* left_space = NULL;
		do{
			p = malloc(MEM_EXHAUSTION_UNIT);
			if(p == NULL)	p = malloc(MEM_EXHAUSTION_UNIT>>4);
			if(p == NULL)	p = malloc(MEM_EXHAUSTION_UNIT>>8);
			if(p == NULL)	p = malloc(MEM_EXHAUSTION_UNIT>>12);
			if(p != NULL)	left_space = p;
		}while(p != NULL);
		if(non_left_space){
			void** newbuf = (void**) buf;
			*newbuf = p;
		}else{
			void** newbuf = (void**) buf;
			*newbuf = left_space;
		}
		return;
	}
	
	MemoryExhaustionInjector(bool nonleftspace):non_left_space(nonleftspace) {};
	private:
	bool non_left_space;
};

class WrongFormatInjector: public SoftwareFaultInjector {
	public:
	virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit,char *buf){
		switch(*buf){
			case 1:
				*buf = 2; break;
			case 2:
				*buf = 4; break;
			case 4:
				*buf = 8; break;
			case 8:
				*buf = 4; break;
			case 10:
				*buf = 4; break;
			default:
				break;
		}
		return;
	}
};

class PthreadDeadLockInjector: public SoftwareFaultInjector {
	public:
	virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit,char *buf){
		pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
		pthread_mutex_lock(&mutex1);
		pthread_t thread1 = pthread_t(*buf);
		pthread_join(thread1, NULL);
		pthread_mutex_lock(&mutex1);
		return;
	}
};

class PthreadThreadKillerInjector: public SoftwareFaultInjector {
	public:
	virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit,char *buf){
		pthread_t t = pthread_t(*buf);
		sleep(0.02);
		pthread_cancel(t);
		return;
	}
};

class PthreadRaceConditionInjector: public SoftwareFaultInjector {
	public:
	virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit,char *buf){
		pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
		pthread_mutex_unlock(&mutex);
		return;
	}
};

