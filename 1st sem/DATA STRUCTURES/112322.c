#include <stdio.h>
#include <string.h>

char text[1000];

int main(){
    FILE *fp;

    if(fp = fopen("MP5.txt", "r") == 0){
        fp = fopen("MachineProb.txt", "w");
        printf("Input a text: ");
        fgets(text, 1000, stdin);
        fprintf(fp, "%s", text);
    }
    else{
        fp = fopen("MP5.txt", "r");
        fgets(text, 1000, fp);
    }
    print();
}

void print(){
    int  i,j,k,count=0,n;

    for(j=0;text[j];j++);
	 n=j;

	printf(" frequency count character in string:\n");

    for(i=0;i<n;i++)
    {
     	count=1;
    	if(text[i])
    	{

 		  for(j=i+1;j<n;j++)
	      {

	        if(text[i]==text[j])
    	    {
                 count++;
                 text[j]='\0';
	     	}
	      }
	      printf(" '%c' = %d \n",text[i],count);



       }


 	}
}
