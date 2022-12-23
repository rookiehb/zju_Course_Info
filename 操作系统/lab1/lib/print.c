#include "print.h"
#include "sbi.h"

void putc(char c){
	sbi_putchar(c);
}

void puts(char *s) {
    // unimplemented
	while (*s!='\0'){
		//sbi_ecall(0x1, 0x0, *s, 0,0,0,0,0);
		sbi_putchar(*s);
		s++;
	}
	//sbi_ecall(0x1, 0x0, 0x30, 0,0,0,0,0);

}

void puti(int x) {
    // unimplemented
	int digit=1;
	int tmp=x;
	while (tmp>=10){
		digit *= 10;
		tmp /= 10;
	}

	while (digit>=1){
		sbi_putchar('0'+x/digit);
		x %= digit;
		digit /= 10;
	}
	
	//sbi_ecall(0x1, 0x0, x+48, 0,0,0,0,0);


}
