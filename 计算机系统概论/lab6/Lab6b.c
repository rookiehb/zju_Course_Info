#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

short int Condition_Code=2;
short int unsigned Res[8];
char PC[52763][17];

int main()
{   
    short int unsigned i;
    for (i=0;i<8;i++)
        Res[i]=0x7777;

    short int unsigned n;
    gets(PC[0]);
    for (n=1; PC[n-1][0] != '\000'; n++)    
            gets(PC[n]);
    n -= 1;//全部的语句数量

    short int unsigned Start_Address;//开始的位置
    for (int j=0;j<=15;j++)
        Start_Address = 2*Start_Address + PC[0][j]-'0';

    for ( i=1 ; 1 ; )
    {  
        if ( PC[i][0]=='0' && PC[i][1]=='0' && PC[i][2]=='0' && PC[i][3]=='1' ) //ADD 注意这边需要改CC
        {
            if (PC[i][10]=='0')
            {
                int DR,SR1,SR2;
                DR = (PC[i][4]-'0')*4 + (PC[i][5]-'0')*2 + (PC[i][6]-'0');
                SR1 = (PC[i][7]-'0')*4 + (PC[i][8]-'0')*2 + (PC[i][9]-'0');
                SR2 =  (PC[i][13]-'0')*4 + (PC[i][14]-'0')*2 + (PC[i][15]-'0');
                
                if ( Res[SR1]>0x7fff && SR1!=6 && SR1!=5)
                {
                    Res[SR1] = ~Res[SR1];
                    Res[SR1] += 1;
                    Res[SR1] = -Res[SR1];
                }
                
                if ( Res[SR2]>0x7fff && SR2!=6 && SR2!=5)
                {
                    Res[SR2] = ~Res[SR2];
                    Res[SR2] += 1;
                    Res[SR2] = -Res[SR2];
                }
                
                Res[DR] = Res[SR1] + Res[SR2];
                
                if ( Res[DR]>0x7fff )
                    Condition_Code=-1;
                else if (Res[DR]==0x0000)
                    Condition_Code=0;
                else
                    Condition_Code=1;
                i += 1;
                continue;
            }
            else
            {
                int DR,SR1,IMM;
                DR = (PC[i][4]-'0')*4 + (PC[i][5]-'0')*2 + (PC[i][6]-'0'); 
                SR1 = (PC[i][7]-'0')*4 + (PC[i][8]-'0')*2 + (PC[i][9]-'0');
                
                if ( PC[i][11]=='0' )
                    IMM = (PC[i][12]-'0')*8 + (PC[i][13]-'0')*4 + (PC[i][14]-'0')*2 + (PC[i][15]-'0');
                else
                {
                    IMM = ('1'-PC[i][12])*8 + ('1'-PC[i][13])*4 + ('1'-PC[i][14])*2 + ('1'-PC[i][15]);
                    IMM += 1;
                    IMM = -IMM;
                }

                if ( Res[SR1]>0x7fff )
                {
                    Res[SR1] = ~Res[SR1];
                    Res[SR1] += 1;
                    Res[SR1] = -Res[SR1];
                }

                Res[DR] = Res[SR1] + IMM;
                if ( Res[DR]>0x7fff )//0x8000 = 1000 0000 0000 0000
                    Condition_Code=-1;
                else if ( Res[DR]==0x0000 )
                    Condition_Code=0;
                else
                    Condition_Code=1;
                i += 1;
                continue;
            }
        }
        else if ( PC[i][0]=='0' && PC[i][1]=='1' && PC[i][2]=='0' && PC[i][3]=='1' ) // AND
        {    
            if ( PC[i][10]=='0' )
            {
                int DR,SR1,SR2;
                DR = (PC[i][4]-'0')*4 + (PC[i][5]-'0')*2 + (PC[i][6]-'0'); 
                SR1 = (PC[i][7]-'0')*4 + (PC[i][8]-'0')*2 + (PC[i][9]-'0');
                SR2 =  (PC[i][13]-'0')*4 + (PC[i][14]-'0')*2 + (PC[i][15]-'0');
                
                Res[DR] = Res[SR1] & Res[SR2];
                
                if (Res[DR]>0x7fff)//0x8000 = 1000 0000 0000 0000
                    Condition_Code=-1;
                else if (Res[DR]==0x0000)
                    Condition_Code=0;
                else
                    Condition_Code=1;
                i += 1;
                continue;
            }
            else
            {
                int  DR,SR1,IMM;
                DR = (PC[i][4]-'0')*4 + (PC[i][5]-'0')*2 + (PC[i][6]-'0'); 
                SR1 = (PC[i][7]-'0')*4 + (PC[i][8]-'0')*2 + (PC[i][9]-'0');
                if (PC[i][11]-'0'==0)
                    IMM = (PC[i][12]-'0')*8 + (PC[i][13]-'0')*4 + (PC[i][14]-'0')*2 + (PC[i][15]-'0');
                else//要表示二进制的补码
                {
                    IMM = ('1'-PC[i][12])*8 + ('1'-PC[i][13])*4 + ('1'-PC[i][14])*2 + ('1'-PC[i][15]);
                    IMM += 1;
                    IMM = -IMM;
                }
                Res[DR] = Res[SR1] & IMM;
                if (Res[DR]>0x7fff)//0x8000 = 1000 0000 0000 0000
                    Condition_Code=-1;
                else if (Res[DR]==0x0000)
                    Condition_Code=0;
                else
                    Condition_Code=1;
                i += 1;
                continue;
            }
        }        
        else if ( PC[i][0]=='0' && PC[i][1]=='0' && PC[i][2]=='0' && PC[i][3]=='0' ) // BR
        {
            int OFFSET=0,j;
            
            if (PC[i][7]=='0')
                for (j=8;j<=15;j++)
                    OFFSET = OFFSET*2 + PC[i][j]-'0';
            else
            {
                for (j=8;j<=15;j++)
                    OFFSET = OFFSET*2 + '1' - PC[i][j];
                OFFSET += 1;
                OFFSET = -OFFSET;
            }
            if ( (Condition_Code==-1 && PC[i][4]=='1') || (Condition_Code==0 && PC[i][5]=='1') || (Condition_Code==1 && PC[i][6]=='1') ) 
                i += OFFSET;
            i += 1;
            continue;
        }    
        else if ( PC[i][0]=='1' && PC[i][1]=='1' && PC[i][2]=='0' && PC[i][3]=='0' ) //JMP
        {
            int BaseR;
            BaseR = (PC[i][7]-'0')*4 + (PC[i][8]-'0')*2 + (PC[i][9]-'0');
            i = Res[BaseR] - Start_Address;
            i += 1 ;
            continue
        }
        else if ( PC[i][0]=='0' && PC[i][1]=='1' && PC[i][2]=='0' && PC[i][3]=='0' ) //JSR
        {    
            if (PC[i][4]=='1')
            {
                int j,OFFSET=0;
                Res[7] = i + Start_Address;//之后RET直接赋值就行了
                if (PC[i][5]=='0')
                    for (j=6;j<=15;j++)
                        OFFSET = OFFSET*2 + PC[i][j]-'0';
                else
                {
                    for (j=6;j<=15;j++)
                        OFFSET = OFFSET*2 + '1' - PC[i][j];
                    OFFSET += 1;
                    OFFSET = -OFFSET;
                }
                i += OFFSET + 1;
                continue;
            }
            else //JSRR
            {
                int BaseR;
                Res[7] = i + Start_Address;
                BaseR = (PC[i][7]-'0')*4 + (PC[i][8]-'0')*2 + (PC[i][9]-'0');
                i = Res[BaseR] - Start_Address;
                i += 1 ;
                continue;
            }
        }
        else if ( PC[i][0]=='0' && PC[i][1]=='0' && PC[i][2]=='1' && PC[i][3]=='0' )//LD 
        {
            int DR,OFFSET=0,j,temp_PC=0;
            DR = (PC[i][4]-'0')*4 + (PC[i][5]-'0')*2 + (PC[i][6]-'0');
            
            if (PC[i][7]=='0')
                for (j=8;j<=15;j++)
                    OFFSET = OFFSET*2 + PC[i][j]-'0';
            else
            {
                for (j=8;j<=15;j++)
                    OFFSET = OFFSET*2 + '1' - PC[i][j];
                OFFSET += 1;
                OFFSET = -OFFSET;
            }

            for (j=0;j<=15;j++)
                temp_PC = 2*temp_PC + PC[i+OFFSET+1][j]-'0';

            Res[DR] = temp_PC;
            if ( Res[DR]>0x7fff )//0x8000 = 1000 0000 0000 0000
                Condition_Code=-1;
            else if (Res[DR]==0x0000)
                Condition_Code=0;
            else
                Condition_Code=1;
            i += 1;
            continue;
        }
        else  if ( PC[i][0]=='1' && PC[i][1]=='0' && PC[i][2]=='1' && PC[i][3]=='0' ) //LDI
        {
            int DR,OFFSET=0,temp_PC1=0,temp_PC2=0,j;
            DR = (PC[i][4]-'0')*4 + (PC[i][5]-'0')*2 + (PC[i][6]-'0');
            if ( PC[i][7]=='0' )
                for (j=8;j<=15;j++)
                    OFFSET = OFFSET*2 + PC[i][j]-'0';
            else 
            {
                for (j=8;j<=15;j++)
                    OFFSET = OFFSET*2 + '1' - PC[i][j];
                OFFSET += 1;
                OFFSET = -OFFSET;
            }
            
            for (j=0;j<=15;j++)
                temp_PC1 = 2*temp_PC1 + PC[i+OFFSET+1][j]-'0';
            

            for (j=0;j<=15;j++)
                temp_PC2 = 2*temp_PC2 + PC[temp_PC1-Start_Address+1][j] - '0';
            
            Res[DR] = temp_PC2;
            if (Res[DR] >0x7fff)//0x8000 = 1000 0000 0000 0000
                Condition_Code=-1;
            else if (Res[DR]==0x0000)
                Condition_Code=0;
            else
                Condition_Code=1;
            i += 1;
            continue;
        }
        else if ( PC[i][0]=='0' && PC[i][1]=='1' && PC[i][2]=='1' && PC[i][3]=='0' )//LDR //录入的是 address+offset的值
        {
            int DR,BaseR,OFFSET=0,j,num=0;
            DR = (PC[i][4]-'0')*4 + (PC[i][5]-'0')*2 + (PC[i][6]-'0');
            BaseR = (PC[i][7]-'0')*4 + (PC[i][8]-'0')*2 + (PC[i][9]-'0');
            if ( PC[i][10]=='0' )
                for (j=11;j<=15;j++)
                    OFFSET = 2*OFFSET + PC[i][j] - '0';
            else
            {
                for (j=11;j<=15;j++)
                    OFFSET = 2*OFFSET - PC[i][j] + '1';  
                OFFSET += 1;
                OFFSET = -OFFSET;
            }
            

            for (j=0;j<=15;j++)
                num = 2*num + PC[Res[BaseR]+OFFSET-Start_Address+1][j] - '0';

            Res[DR] = num;
            if (Res[DR]>0x7fff) //0x8000 = 1000 0000 0000 0000
                Condition_Code=-1;
            else if (Res[DR]==0x0000)
                Condition_Code=0;
            else
                Condition_Code=1;
            i += 1;
            continue;
        }
        else if ( PC[i][0]=='1' && PC[i][1]=='1' && PC[i][2]=='1' && PC[i][3]=='0' ) //LEA  似乎没问题
        {
            int DR,OFFSET=0,j;
            DR = (PC[i][4]-'0')*4 + (PC[i][5]-'0')*2 + (PC[i][6]-'0');
            if (PC[i][7]=='0')
                for (j=8;j<=15;j++)
                    OFFSET = 2*OFFSET + PC[i][j]-'0';
            else
            {
                for (j=8;j<=15;j++)
                    OFFSET = 2*OFFSET + '1' - PC[i][j];
                OFFSET += 1;
                OFFSET = -OFFSET;
            }
            Res[DR] = Start_Address + OFFSET + i;
            i += 1;
            continue;
        }
        else if ( PC[i][0]=='1' && PC[i][1]=='0' && PC[i][2]=='0' && PC[i][3]=='1' ) //NOT 
        {
            int DR,SR;
            DR = (PC[i][4]-'0')*4 + (PC[i][5]-'0')*2 + (PC[i][6]-'0'); 
            SR = (PC[i][7]-'0')*4 + (PC[i][8]-'0')*2 + (PC[i][9]-'0');

            Res[DR] = ~Res[SR];
            if (Res[DR]>0x7fff)
                Condition_Code=-1;
            else if (Res[DR]==0x0000)
                Condition_Code=0;
            else
                Condition_Code=1;
            i += 1;
            continue;
        }

        else if ( PC[i][0]=='0' && PC[i][1]=='0' && PC[i][2]=='1' && PC[i][3]=='1' )//ST
        {
            int SR,OFFSET=0,j,num;char temp[17];
            SR = (PC[i][4]-'0')*4 + (PC[i][5]-'0')*2 + (PC[i][6]-'0');
            if ( PC[i][7]=='0' )
                for (j=8;j<=15;j++)
                    OFFSET = OFFSET*2 + PC[i][j]-'0';
            else
            {
                for (j=8;j<=15;j++)
                    OFFSET = 2*OFFSET + '1' -PC[i][j];
                OFFSET += 1;
                OFFSET = -OFFSET;
            }
            num = Res[SR];
            for (j=15;j>=0;j--)
            {
                temp[j] = num%2 +'0';
                num /= 2;
            }
            temp[16]='\0';
            if ( Res[SR]>0x7fff ) //0x8000 = 1000 0000 0000 0000
                 Condition_Code=-1;
            else if (Res[SR]==0x0000)
                Condition_Code=0;
            else
                Condition_Code=1;
            strcpy(PC[i+OFFSET+1],temp);

            i += 1;
            continue;
        }
        else if ( PC[i][0]=='1' && PC[i][1]=='0' && PC[i][2]=='1' && PC[i][3]=='1' )//STI
        {
            int SR,OFFSET=0,j,num,Address=0;char temp[17];
            SR = (PC[i][4]-'0')*4 + (PC[i][5]-'0')*2 + (PC[i][6]-'0');
            
            if ( PC[i][7]=='0' )
                for (j=8;j<=15;j++)
                    OFFSET = OFFSET*2 + PC[i][j]- '0';
            else
            {
                for (j=8;j<=15;j++)
                    OFFSET = OFFSET*2 + '1' - PC[i][j];
                OFFSET += 1;
                OFFSET = -OFFSET;
            }

            num = Res[SR];
            for (j=15;j>=0;j--)
            {
                temp[j] = num % 2 + '0';
                num /= 2;
            }
            for (j=0;j<=15;j++)
                Address = Address*2 + PC[i+OFFSET+1][j]-'0';
            temp[16]='\0';
            strcpy(PC[Address-Start_Address+1],temp);
            if (Res[SR]>0x7fff) //0x8000 = 1000 0000 0000 0000
                Condition_Code=-1;
            else if (Res[SR]==0x0000)
                Condition_Code=0;
            else
                Condition_Code=1;
            i += 1;
            continue;
        }
        else if ( PC[i][0]=='0' && PC[i][1]=='1' && PC[i][2]=='1' && PC[i][3]=='1' )//STR
        {
            int SR,BaseR,OFFSET=0,j,num,Address;char temp[17];
            SR = (PC[i][4]-'0')*4 + (PC[i][5]-'0')*2 + (PC[i][6]-'0');
            BaseR = (PC[i][7]-'0')*4 + (PC[i][8]-'0')*2 + (PC[i][9]-'0');

            if ( PC[i][10]=='0' )
                for (j=11;j<=15;j++)
                    OFFSET = 2*OFFSET + PC[i][j] - '0';
            else
            {
                for (j=11;j<=15;j++)
                    OFFSET = 2*OFFSET - PC[i][j] + '1';
                OFFSET += 1;
                OFFSET = -OFFSET;
            }
            
            if (Res[SR]>0x7fff) //0x8000 = 1000 0000 0000 0000
                Condition_Code=-1;
            else if (Res[SR]==0)
                Condition_Code=0;
            else
                Condition_Code=1;

            num = Res[SR];
            for (j=15;j>=0;j--)
            {
                temp[j] = num % 2 + '0';
                num /= 2;
            }

            temp[16]='\0';
            Address = Res[BaseR] + OFFSET;
            strcpy(PC[Address-Start_Address+1],temp);

            i += 1;
            continue;
        }
        else if ( PC[i][0]=='1' && PC[i][1]=='1' && PC[i][2]=='1' && PC[i][3]=='1' )
        {
            break;
        }
    }

    for (i=0;i<8;i++)
        printf("R%d = x%04hX\n",i,Res[i]);

    system("pause");
    return 0;
}
