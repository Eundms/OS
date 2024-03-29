#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int is_pidndur_ok(int argc, char**argv, int*pid, int*dur){

	// pid값을 입력하지 않았을 때
	if(argc<2){printf("%s pid duration: duration default=10",*(argv)); return -1;}
	else if(argc!=2){*dur = atoi(*(argv+2));}

	*pid = atoi(*(argv+1));

	// 문자를 입력했을 때
	if(*pid<=0||*dur<=0)return -1;

	return 0;
}

int get_virtinfo(char *spid)
{ 
	char buffer[1024];
	char dest[30];
	sprintf(dest, "/proc/%s/statm", spid);
	int size, resident, shared ;
	FILE *fp=fopen(dest,"r");
	if(fp==NULL){return -1;}
	while(fgets(buffer,1024,fp)!=NULL){
		sscanf(buffer,"%d %d %d ",&size,&resident,&shared);//공백 기준으로 1번째 숫자이용.
		printf("%d\n",size);//가상메모리
		memset(buffer,0,sizeof(buffer));
	}
	fclose(fp);
return 0;
}
int main(int argc, char* argv[]){
	int pid = -1;
	int dur = 10; //default값
	int pidexist=-1;	
	if(is_pidndur_ok(argc, argv, &pid, &dur)==-1){return -1;}

	char spid[10];//stat, statm, status
	sprintf(spid, "%d", pid);
	
	for(int time=0; time<dur*2; time++){
		pidexist=get_virtinfo(spid);
		if(pidexist ==-1){printf("%s isn't exist.",spid);break;}
		usleep(500000);//usleep(1000000 ) 1초
	}
}
