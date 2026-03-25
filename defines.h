
#ifndef __DEFINES_H__
#define __DEFINES_H__
#define SSETBIT(WORD,BITPOS) (WORD=1<<BITPOS)  //Macro for setting a bit
#define SCLRBIT(WORD,BITPOS) (WORD=1<<BITPOS)	 //Macro for Clearing a bit
#define SETBIT(WORD,BITPOS) (WORD|=1<<BITPOS)	 //Macro for setting a bit without disturbing other bits
#define CLRBIT(WORD,BITPOS)	(WORD&=~(1<<BITPOS)) //Macro for clearing a bit without disturbing other bits
#define WBYTE(WORD,SBITPOS,BYTE) (WORD=(WORD&~(0xFF<<SBITPOS))|(BYTE<<SBITPOS)) //Macro for Writing a byte
#define WNIBBLE(WORD,SBITPOS,NIBBLE) (WORD=(WORD&~(0XF<<SBITPOS))|(NIBBLE<<SBITPOS)) //Macro for writing a nibble 
#define WBIT(WORD,BITPOS,BIT) (WORD=(WORD&~(1<<BITPOS))|(BIT<<BITPOS))	//Macro for writing a bit
#define RBIT(WORD,BITPOS) ((WORD>>BITPOS)&1)	 // Macro for reading a bit
#define RNIBBLE(WORD,SBITPOS) ((WORD>>SBITPOS)&15) // Macro for reading a nibble
#define RBYTE(WORD,SBITPOS) ((WORD>>SBITPOS)&255)	 // Macro for reading a byte
#define CPLBIT(WORD,BITPOS) (WORD^=1<<BITPOS)		// Macro for Complementing/toggling a bit
#define READWRITEBIT(DWORD,DBIT,SBIT)	(DWORD=(DWORD&~(1<<DBIT))|(((DWORD>>SBIT)&1)<<DBIT)) // Macro for Reading and writing a bit at a position of a word
#define READWRITEBIT2(DWORD,DBIT,SWORD,SBIT) (DWORD=(DWORD&~(1<<DBIT))|(((SWORD>>SBIT)&1)<<DBIT)) // Macro for Reading and writing a bit at starting of a word
#endif

