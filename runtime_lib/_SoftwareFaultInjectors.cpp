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

static RegisterFaultInjector AA("NoOpen(API)", BitCorruptionInjector::getBitCorruptionInjector());
static RegisterFaultInjector AB("WrongMode(API)", BitCorruptionInjector::getBitCorruptionInjector());
static RegisterFaultInjector AC("WrongPointer(Data)", BitCorruptionInjector::getBitCorruptionInjector());
static RegisterFaultInjector AD("WrongSource(Data)", BitCorruptionInjector::getBitCorruptionInjector());
static RegisterFaultInjector AE("WrongDestination(Data)", BitCorruptionInjector::getBitCorruptionInjector());
static RegisterFaultInjector AF("InvalidPointer(Res)", BitCorruptionInjector::getBitCorruptionInjector());
static RegisterFaultInjector AG("WrongAPI(API)", BitCorruptionInjector::getBitCorruptionInjector());
static RegisterFaultInjector AH("IncorrectOutput(API)", BitCorruptionInjector::getBitCorruptionInjector());
static RegisterFaultInjector AI("IncorrectOutput(Data)", BitCorruptionInjector::getBitCorruptionInjector());
static RegisterFaultInjector AJ("WrongRetrievedAddress(I/O)", BitCorruptionInjector::getBitCorruptionInjector());
static RegisterFaultInjector AK("InvalidSender(MPI)", BitCorruptionInjector::getBitCorruptionInjector());
static RegisterFaultInjector AL("DeadLock(MPI)", BitCorruptionInjector::getBitCorruptionInjector());
static RegisterFaultInjector AM("WrongSavedAddress(I/O)", BitCorruptionInjector::getBitCorruptionInjector());
static RegisterFaultInjector AN("DataCorruption(Data)", BitCorruptionInjector::getBitCorruptionInjector());

class MemoryLeakInjector: public SoftwareFaultInjector {
	public:
	virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit,char *buf){
		void* fake_p = malloc(1024 * sizeof(char));
		void** newbuf = (void**) buf;
		*newbuf = fake_p;
		return;
	}
};

static RegisterFaultInjector BA("MemoryLeak(Res)", new MemoryLeakInjector());

class HangInjector: public SoftwareFaultInjector {
	public:
	virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit,char *buf){
		while(1);
		return;
	}
};

static RegisterFaultInjector CA("NoOutput(API)", new HangInjector());
static RegisterFaultInjector CB("NoOutput(Data)", new HangInjector());
static RegisterFaultInjector CC("NoMessage(MPI)", new HangInjector());
static RegisterFaultInjector CD("NoAck(MPI)", new HangInjector());

class SleepInjector: public SoftwareFaultInjector {
	public:
	virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit,char *buf){
		sleep(3);
		return;
	}
};

static RegisterFaultInjector DA("HighFrequentEvent(Timing)", new SleepInjector());
static RegisterFaultInjector DB("CPUHog(Res)", new SleepInjector());

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

static RegisterFaultInjector EA("InvalidMessage(MPI)", new ChangeValueInjector(+1024, false));
static RegisterFaultInjector EB("NoDrain(MPI)", new ChangeValueInjector(+5000, true));
static RegisterFaultInjector EC("BufferOverflow(API)", new ChangeValueInjector(+45, false));
static RegisterFaultInjector ED("BufferUnderflow(API)", new ChangeValueInjector(-40, false));
static RegisterFaultInjector EE("BufferOverflowMemmove(Data)", new ChangeValueInjector(+45, false));
static RegisterFaultInjector EF("BufferOverflowMalloc(Data)", new ChangeValueInjector(-40, false));
static RegisterFaultInjector EG("UnderAccumulator(Res)", new ChangeValueInjector(+45, false));
static RegisterFaultInjector EH("PacketStorm(MPI)", new ChangeValueInjector(-40, false));

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

static RegisterFaultInjector FA("InappropriateClose(API)", new InappropriateCloseInjector(true));
static RegisterFaultInjector FB("NoClose(API)", new InappropriateCloseInjector(false));

class StalePointerInjector: public SoftwareFaultInjector {
	public:
	virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit,char *buf){
		void** newbuf = (void**) buf;
		free(*newbuf);
	}
};

static RegisterFaultInjector GA("StalePointer(Res)", new StalePointerInjector());

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

static RegisterFaultInjector HA("MemoryExhaustion(Res)", new MemoryExhaustionInjector(true));
static RegisterFaultInjector HB("LowMemory(Res)", new MemoryExhaustionInjector(false));

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

static RegisterFaultInjector IA("WrongRetrievedFormat(I/O)", new WrongFormatInjector());
static RegisterFaultInjector IB("WrongSavedFormat(I/O)", new WrongFormatInjector());

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

static RegisterFaultInjector JA("DeadLock(Res)", new PthreadDeadLockInjector());

class PthreadThreadKillerInjector: public SoftwareFaultInjector {
	public:
	virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit,char *buf){
		pthread_t t = pthread_t(*buf);
		sleep(0.02);
		pthread_cancel(t);
		return;
	}
};

static RegisterFaultInjector KA("ThreadKiller(Res)", new PthreadThreadKillerInjector());

class PthreadRaceConditionInjector: public SoftwareFaultInjector {
	public:
	virtual void injectFault(long llfi_index, unsigned size, unsigned fi_bit,char *buf){
		pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
		pthread_mutex_unlock(&mutex);
		return;
	}
};

static RegisterFaultInjector LA("RaceCondition(Timing)", new PthreadRaceConditionInjector());
