#include <lib.h>
#include <signal.h>
#include <env.h>


static void __attribute__((noreturn)) signal_handler_entry(struct Trapframe *tf,int signum) {
    sigset_t mask ;
    struct sigaction signal ;
    mask.sig[0] = syscall_get_mask(0,0);
    mask.sig[1] = syscall_get_mask(0,1);
    signal.sa_handler = syscall_get_sigaction(0,signum,0);
    signal.sa_mask.sig[0] = syscall_get_sigaction(0,signum,1);
    signal.sa_mask.sig[1] = syscall_get_sigaction(0,signum,2);
    if (signal.sa_handler == NULL){
        if ( signum==9 || signum==11 || signum==15){
            debugf("exit!!!!\n") ;
            exit() ;
        }else{
            user_panic("null sigaction\n");
        }
    }else{
        (*(signal.sa_handler))(signum);
        sigprocmask(SIG_SETMASK,&mask,NULL);
        //tf ->cp0_epc += 4;
        int r = syscall_set_trapframe(0, tf);
	    user_panic("syscall_set_trapframe returned %d", r);
    }
}


int isinvalid_signum(int signum){
    if (signum >= 1 && signum <=64){
        return 0;
    }else{
        return 1;
    }
}

void sigemptyset(sigset_t *set){
    set->sig[0] = 0;
    set->sig[1] = 0;
    syscall_set_signal_handler_entry(0,signal_handler_entry);
}


void sigfillset(sigset_t *set){
    set->sig[0] = -1;
    set->sig[1] = -1;
}


void sigaddset(sigset_t *set, int signum){
    if (isinvalid_signum(signum)){
        user_panic("invalid signum");
    }
    int index = SIGNALX(signum) / 32;
    int bitNum = SIGNALX(signum) % 32;
    set->sig[index] |= (1 << bitNum);
}


void sigdelset(sigset_t *set, int signum){
    if (isinvalid_signum(signum)){
       user_panic("invalid signum");
    }
    int index = SIGNALX(signum) / 32;
    int bitNum = SIGNALX(signum) % 32;
    set->sig[index] &= ~(1 << bitNum);
}


int sigismember(const sigset_t *set, int signum){
    if (isinvalid_signum(signum)){
        user_panic("invalid signum");
    }
    int index = SIGNALX(signum) / 32;
    int bitNum = SIGNALX(signum) % 32;
    if ((set->sig[index]) & (1 << bitNum)){
        return 1;
    }
    return 0;
}


int sigprocmask(int how, const sigset_t *set, sigset_t *oldset){
    return syscall_sigprocmask(how,set,oldset);
}

int kill(u_int envid, int sig){
    if (isinvalid_signum(sig)){
       return -1;
    }
    return syscall_signalkill(envid,sig);
}


int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact){
    if (isinvalid_signum(signum)){
        return -1;
    }
    //syscall_set_signal_handler_entry(0,signal_handler_entry);
    return syscall_sigaction(signum,act,oldact);
}



