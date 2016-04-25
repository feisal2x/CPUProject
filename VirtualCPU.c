/**
 *Created By:Feisal Salim &Wenzhong Zheng
 *Implementing the memory dump and the modify memory.
 */
//dfdf
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cpu.h"

int main(){
    char choice;
    char memory[BUFFER_SIZE];
    int offset; //for dump memory where to start
    int length; //number of bites to dump from the inital starting point the offset. 
    unsigned int  sizeofFile;
    int address; //starting address

while(1){
    printf("d       dump memory\n");
    printf("g       go - run the entire program\n");
    printf("l       load a file into memory\n");
    printf("m       memory modify\n");
    printf("q       quit\n");
    printf("r       display registry\n");
    printf("t       trace - execute one instruction\n");
    printf("w       write file\n");
    printf("z       reset all regesters to zero\n");
    printf("?,h     display list of commands\n");
    
    scanf("%s",&choice);

    printf("choice: %s\n",&choice);
    
    switch(choice){
            case 'd':
            case 'D':   
                        printf("Enter offset value\n");
                        scanf("%x", &offset);
                        printf("Enter length\n");//# of bytes to dump
                        scanf("%x", &length);

                        MemDump(memory,offset,length);
                        break;
            case 'q':
            case 'Q':
                    printf("Exiting Program\n");
                    return 1;
            case 'g':
            case 'G':
                    RunProgram(memory);
                    break;
            case 'm':
            case 'M':
                    printf("Enter starting address\n");
                    scanf("%x",&address);
                    MemModify(address,memory);
                    break;
            case 't':
            case 'T':
                    Trace(memory);
                    break;
            case 'r':
            case 'R': 
                    RegistryDisplay();
                    break;
            case 'z':
            case 'Z':
                    ZeroRegistry();
                    break;
            case 'l':
            case 'L':
                    LoadFile(memory,sizeof(memory));
                    break;
            case 'w':
            case 'W':
                    WriteFile(memory);
                    break;
            case 'h':
            case 'H':
                    printf("displaying commands:\n\n");
                    break;
    
    }
}


}

int LoadFile(void * memory, unsigned int max){
                                    
                    FILE *f;
                    char fileN[30];
                    int bytesRead=0;
                    printf("Enter name of file\n");
                    scanf("%s",fileN);
                   
                    printf("How much bytes do you want to read:\n");
                    scanf(" %d",&max);

                    //printf("memory : %s\n",&memory);
                   if((f= fopen(fileN,"r")) == NULL)
                    {
                       printf("Unable to open file!\n\n");
                       exit(1);
                    }else{
                        printf("Opened file successfully\n \n");
                        //char buffer[max];
                        //bzero(&memory,sizeof(&memory));
                        fread(memory,sizeof(char),max,f);
                        fclose(f);
                        bytesRead=max*sizeof(char);
                       // printf("memory address: %p\n",&memory);
                        printf("memory:\n%s",(char *)memory);
                        printf("\n__________________________\n");
                        printf("bytes read: %d decimal || %xH\n", bytesRead,bytesRead);
                    }
                   return max;
}

/**
*
*/
void WriteFile(void * memory){
                    char fileN[30];
                    FILE *f;
                    int bytes=0;
                    printf("Enter name of file\n ");
                    scanf("%s",fileN);

                    printf("how many bytes do you want to write\n");
                    scanf(" %d", &bytes);
                    f=fopen(fileN,"w+");
                    fwrite(memory,bytes,1,f);
                    
                    printf("write complete");
                    fclose(f);

}
void MemDump(void * memptr, unsigned offset,unsigned length){

    unsigned char *pc =(unsigned char*)memptr;
    //char buffer[16]="";
    int initalOffset=offset;
    int counter=offset;
    while(offset<(length+initalOffset)){
    fprintf(stdout,"%05x ",counter);
        for(int i=offset ;i<(offset+16);i++){
                    fprintf(stdout," %4x",pc[i]);
        }
        
                    printf("\n");
        
        fprintf(stdout,"     ");
        for(int i=offset ;i<(offset+16);i++){
            //char tmp=(unsigned char)pc[i];
            fprintf(stdout," %4c",isprint(pc[i]) ?pc[i]:'.');
        }
              fprintf(stdout,"\n\n");
         offset+=16;
         counter+=16;
    }
}
void MemModify(unsigned  memptr,void *memory){
unsigned char *p=(unsigned char *)memory;
while(1){
    unsigned int newVal=0;
    printf("Location: %x  Value:%c\n",memptr,p[memptr]);    
    printf("Enter new Value\n");
    scanf("%x",&newVal);
    getchar();
    fflush(stdin);
    if(newVal==0){
        break;
    }
    p[memptr]=newVal;
    memptr++;
    
}



}
/**
 *Displays the Registry
 *
 */
void RegistryDisplay(){

               fprintf(stdout,"\n\nRegistries\n");
               fprintf(stdout,"-----------------------------------\n");
               fprintf(stdout," R0:%08X   R1:%08X   R2:%04X   R3:%08X    R4:%08X    R5:%08x\n",  R0,  R1, R2, R3, R4, R5);
               fprintf(stdout," R6:%08X   R7:%08X   R8:%04X   R9:%08X   R10:%08X   R11:%08x\n",  R6,  R7, R8, R9, R10, R11);  
               fprintf(stdout,"R12:%08X\n",R12);
               fprintf(stdout," SP:%08X \n",SP);
               fprintf(stdout," LR:%08X \n",  LR);
               fprintf(stdout," PC:%08X \n",  PC);

               fprintf(stdout,"\n MAR:%08X   MBR:%08X   IR0:%04X   IR1:%04X   Stop:%0d   IR Flag:%01d\n",  MAR,  MBR, IR0, IR1, flag_STOP, flag_IR);                    
               fprintf(stdout,"\n flag_STOP:%01X   flag_ZERO:%01X   flag_CARRY:%01X   flag_SIGN:%01X\n\n\n", flag_STOP,flag_ZERO ,flag_CARRY, flag_SIGN);  

 }  
 /**
 *Reset's all the registries
 *
 */ 
 void ZeroRegistry(){
    R0=0;R1=0;R2=0;R4=0;R5=0;
    
    R6=0;R7=0;R8=0;R9=0;R10=0;

    R11=0;R12=0;
    SP=0;
    LR=0;
    PC=0;
    MAR=0;
    MBR=0;
    IR0=0;
    IR1=0;
    flag_STOP=0;
    flag_IR=0;


 }
  /**
   * calls the function fetch and displays the registries
   *
   */
 void Trace(void * memptr){
        Fetch(memptr);
      //  InstructionSet(memptr);
       
        RegistryDisplay();
 }
void Fetch(void * mem){
    unsigned char *p = (unsigned char *)mem;
    MBR=0;
    MAR=(int) &p[PC];
    IR1=0;
     
    for(int i=PC;i<PC+4;i++){
	if(i==PC && p[i]=='1'){
		MBR+=0x8;
		IR1+=8;
	}
	if(i==PC+1 && p[i]=='1'){
		MBR+=4;
		IR1+=4;
	}
	if(i==PC+2 && p[i]=='1'){
		MBR+=2;
		IR1+=2;
	}
	if(i==PC+3 && p[i]=='1'){
		MBR+=1;
		IR1+=1;
	}
    }
    IR0=IR1;
	printf("\nPC:%d",PC);
    //recognize instrucion types bit:8-11 
    //IR1:0 is data processing
	printf("\nIR1: %d",IR1);
    if(IR1==0){
	    int code=fourBits(p,PC+4);
	    printf("\ncode is : %d",code);
		int *Rd = regNum(fourBits(p,PC+12));
		int A=*Rd;
		printf("\nRd: %d",A);
		int *Rn = regNum(fourBits(p,PC+8));
		int B=*Rn;
		printf("\nRn: %d",B);

	    if(code==4){ //code 4 is ADD
		*Rd=A+B;		
	    }
	    if(code==2){ //code 2 is SUB
		*Rd=A-B;		
	    }
  	    int final=*Rd;
	    flag_CARRY=isCarry(final);
    }
   //IR1=2 is Load/Store
   if(IR1==2){
	printf("I'M doing loading");
	int code=fourBits(p,PC+4);	
	int *Rd= regNum(fourBits(p,PC+12));
	int A=*Rd;
	int B = fourBits(p,PC+8);
	*Rd=B;

   }
   if(IR1>=15){
	printf("\nStop instruction detected");
	return;	
   }
   //Unconditional Branch
   if(IR1==13 || IR1==12){
	if(IR1==12){//BRA
		int step = fourBits(p,PC+12);
		PC=(step-2)*17;//each ins. takes 16 bits and a new line char
		printf("\nGo back to instruction %d",step);
	}

   }

  
   PC+=17;
}
int isCarry(int x)
{
    return x>MAX?1:0;
}


int fourBits( char* p, int o)
{

	int a=0;
	for(int i=0;i<4;i++)
	{
	  if(i==0 && p[o]=='1')
		a+=8;	
	  if(i==1 && p[o+i]=='1')
		a+=4;
	  if(i==2 && p[o+i]=='1')
		a+=2;
	  if(i==3 && p[o+i]=='1')
		a+=1;
	}
	return a;


}

int* regNum(int a)
{
	if(a==0)return &R0;
	if(a==1)return &R1;
	if(a==2)return &R2;
	if(a==3)return &R3;
	if(a==4)return &R4;
	if(a==5)return &R5;
	if(a==6)return &R6;
	if(a==7)return &R7;
	if(a==8)return &R8;
	if(a==9)return &R9;
	if(a==10)return &R10;
	if(a==11)return &R11;
	if(a==12)return &R12;
}


void InstructionSet(void * mem){
    

    if(MBR ==0xA){
        //The 0xA hex is the load/store instruction
        printf("Storing value");

        Fetch(mem);
        R0+=MBR;
        
         
    }

    if(MBR == 0xF){
        //0xF is the Stop instruction
        printf("Stop instruction detected");
        flag_STOP=1;
    }
    if (MBR== 0x5){
        //0x8 hex is the ADC instruction

        Fetch(mem);
        R1=MBR;
        Fetch(mem);
        R2=MBR;
        R3=R1+R2;
        if(R1>MAX){
            flag_CARRY=1;

        }
        else
            flag_CARRY=0;

    }
    
 

}
void RunProgram(void *mem){
        while(flag_STOP!=1 || MBR==99){

            Trace(mem);
        }

    //testing run program function
}




