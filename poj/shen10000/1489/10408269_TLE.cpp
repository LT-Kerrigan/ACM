#include<stdio.h>
#include<string.h>
char map[10]="|n98r";
char str1[100],str2[100],tmp[100];
char ban0[20][50];
int ban1[20];
int a,b;
int tonumber(char *s){
	int num=0;
	for(int i=0;s[i];i++){
		switch(s[i]){
			case '|':num+=1;break;
			case 'n':num+=10;break;
			case '9':num+=100;break;
			case '8':num+=1000;break;
			case 'r':num+=10000;break;

		}
	}
	return num;
}

int tochar(int num,char *q){

	int i=0;
	int lev=-1;
	int mod;
	while(1){
		mod=num%10;
		num/=10;
		lev++;
		if(mod){
			while(mod--)q[i++]=map[lev];
			
			if(num){q[i++]=' ';}
			else {
				q[i]='\0';
				break;
			}
			
		}
	}
	
	return i;
} 

int main()
{

	int ans,mod,now,len;
	now=1;
	int i=1;
	while(now<99999){
		ban1[i]=tochar(now,ban0[i]);
		i++;
		now<<=1;
	}
	while(gets(str1)){
		while(str1[0]=='\n')gets(str1);
		gets(str2);
		while(str1[0]=='\n')gets(str2);
		a=tonumber(str1);
		b=tonumber(str2);
		ans=a*b;
		now=1;
		//printf("%d %d %d \n",a,b,ans);
		while(b){
			mod=b&1;
			b>>=1;
			len=ban1[now];
			strcpy(tmp,ban0[now]);
			
			tmp[len++]=' ';
			if(mod){
				tmp[len++]='*';
			}
			while(len<34)tmp[len++]=' ';
			tmp[len]='\0';
			printf("%s",tmp);
			len=tochar(a,tmp);
			printf("%s \n",tmp);
			now++;
			a<<=1;
		}
		tochar(ans,tmp);
		printf("The solution is: %s\n",tmp);
	}
return 0;
}
