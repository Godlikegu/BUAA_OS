#include <lib.h>
int global = 0;
void handler ( int num) {
    debugf ("Reach handler , now the signum is %d!\n" , num) ;
    global = 1;
}
struct sigset_t set2 ;
// 测 试 屏 蔽 信 号
int main ( int argc , char ** argv ) {
struct sigset_t set ;
struct sigaction sig ;
sigemptyset (&set ) ;
sigaddset (&set , 3 ) ;
sigaddset (&set , 2 ) ;
sig.sa_handler = handler ;
sig.sa_mask = set ;
panic_on ( sigaction (2 , &sig , NULL)) ;
int ret = fork () ,temp=0;
if ( ret != 0) {
for ( int i =0;i <10000000; i++) temp+=i ;
kill ( ret , 2 ) ;
for ( int i =0;i <10000; i++) temp+=i ;
debugf ( "Father : global %d.\n" , global ) ;
} else {
panic_on ( sigprocmask (SIG_BLOCK, &set , NULL) ) ;
    for ( int i =0;i <10000; i++) temp+=i ;
    debugf ( "Child : global %d.\n" , global) ;
}
return 0;
}


/*#include <lib.h>
int global = 0;
void handler ( int num) {
    debugf ( "Reach handler , now the signum is %d!\n" , num) ;
    global = 1;
}
int * t=NULL;
int main ( int argc , char ** argv ) {
    struct sigset_t set ;
    sigemptyset (&set) ;
    * t =10;
    int ans=0;
    for ( int i =0;i <100000000; i++) ans+=i ;
    debugf ( "error ! no exit \n" ) ;
    return 0;
}*/