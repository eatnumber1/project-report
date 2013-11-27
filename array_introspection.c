char a[sizeof((*((int (*)[4]) NULL))[0])];
__typeof__(&a) ap = &a;
(int (*)[4]) ap
