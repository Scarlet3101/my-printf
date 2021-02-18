#include<stdio.h> 
#include<stdarg.h>						
#include<unistd.h>
#include<stdlib.h>	


//my oun strlen
int my_strlen(char* param_1)
{
    int count = 0;
    for(int i=0; param_1[i] != '\0'; i++)
    {
        count++;
    }
   return count; 
}


//my oun putchar

int my_putchar(char c) {
    write(1, &c, 1);
    return 1;
}
// my own puts
int my_puts( char *str_a)
{
  int i =0;
    for(i = 0; i < my_strlen(str_a);i++){
      my_putchar(str_a[i]);
    }
    return i;
}

//itoa implementation
char* itoaa(unsigned long num,int base,char mass[]){  
    int i = 48;
    int remainder;
    mass[i+1] = '\0';  
    if(num == 0){
        mass[i--]= '0';
    } else{
        do{
            remainder = num%base;   
            num/=base;
            if (remainder>9){
                mass[i] = 'a'+ remainder - 10; 
            }else{
                mass[i]=  remainder + '0'; 
            }
            i--;
        }while(num!=0);
    }
    return &mass[i+1];        
}

int my_printf(char*restrict format,...) 
{ 
  // my_printf arguments
  void* kakoito;
  char mas[50];
	char *elements; 
  char *str_a; 
	int num;
  int count = 0;
	va_list arg; 
	va_start(arg, format);
	// ///////////////////////

	for(elements = format; *elements != '\0'; elements++)
	{
		if( *elements != '%' ) 
		{ 
      count ++;
			my_putchar(*elements);
			//elements++; 
		}
		//elements++; 
    else{
    elements++; 
		// %c %d %o %s %x %u
		switch(*elements) 
		{
		    case 'c' : num = va_arg(arg,int);	//char
				count += my_putchar(num);
				break; 
						
				
			case 'o': num = va_arg(arg,unsigned int);//Octal 
					count += my_puts(itoaa(num,8,mas));
					break; 

      case 'x': num = va_arg(arg,unsigned int);//Hexadecimal 
					count += my_puts(itoaa(num,16,mas));
					break;

      case 'p': num = va_arg(arg,unsigned int);//P 
          kakoito = va_arg(arg, void*);
          count += my_puts("0x");
					count += my_puts(itoaa((unsigned long)kakoito,16,mas));
					break;
						
			case 's': str_a = va_arg(arg,char *);//string
          if(str_a == NULL){
           count +=  my_puts("(null)");
          }
          else{
            count += my_puts(str_a); 
          }
					break; 

      case 'd': num = va_arg(arg,int);
            if(num < 0){
              count += my_puts("-");
              num = -num;
            }
            count += my_puts(itoaa(num,10,mas));
              break;

        case 'u' : num = va_arg(arg,unsigned int);//              Decimal/Integer 
				  //   if(num <= 0)
					// {
					// 	num = -num;
					// } 
					count += my_puts(itoaa(num,10,mas));
					break; 
		}	
	} 
  }
	va_end(arg); 
  return count;
} 

int main() 
{ 
  my_printf("Hello\n");
  my_printf("%c%c%c%c%c!\n", 'H', 'e', 'l', 'l', 'o'); 
  my_printf("Hello %s!\n", "QWASAR.IO");
  my_printf("NULL STRING %s!\n", (char*)NULL);
  my_printf("%d - %d - %d!\n", 2048, 0, -1337);
  my_printf("%o!\n", 100);
  my_printf("%u!\n", 1337);
  my_printf("%x!\n", 17);
  my_printf("Hello world!\n");
  my_printf("%c!\n", 'H');  
	return 0;
}