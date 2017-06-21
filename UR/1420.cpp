#include <cstdio>
#include <cstring>

int main()
{
	char str[50];
	int feira, dia, mes, ano, hora, min, seg, d, prev=1;
	int DIA, MES, ANO, HORA, MIN, SEG, FEIRA;
	int SDIA=24*60*60, DMES[12];
	DMES[0]=31;
	DMES[1]=28;
	DMES[2]=31;
	DMES[3]=30;
	DMES[4]=31;
	DMES[5]=30;
	DMES[6]=31;
	DMES[7]=31;
	DMES[8]=30;
	DMES[9]=31;
	DMES[10]=30;
	DMES[11]=31;
	while(true){
		scanf(" %s", str);
		if(!strcmp(str, "FIM")) break;
		printf("Previsao #%d\n", prev++);
		if(str[0]=='D' && str[1]=='O' && str[2]=='M') FEIRA = 0;
		if(str[0]=='S' && str[1]=='E' && str[2]=='G') FEIRA = 1;
		if(str[0]=='T' && str[1]=='E' && str[2]=='R') FEIRA = 2;
		if(str[0]=='Q' && str[1]=='U' && str[2]=='A') FEIRA = 3;
		if(str[0]=='Q' && str[1]=='U' && str[2]=='I') FEIRA = 4;
		if(str[0]=='S' && str[1]=='E' && str[2]=='X') FEIRA = 5;
		if(str[0]=='S' && str[1]=='A' && str[2]=='B') FEIRA = 6;
		DIA = (str[4] - '0')*10 + str[5]-'0';
		if(str[6]=='J' && str[7]=='A' && str[8]=='N') MES = 0;
		if(str[6]=='F' && str[7]=='E' && str[8]=='V') MES = 1;
		if(str[6]=='M' && str[7]=='A' && str[8]=='R') MES = 2;
		if(str[6]=='A' && str[7]=='B' && str[8]=='R') MES = 3;
		if(str[6]=='M' && str[7]=='A' && str[8]=='I') MES = 4;
		if(str[6]=='J' && str[7]=='U' && str[8]=='N') MES = 5;
		if(str[6]=='J' && str[7]=='U' && str[8]=='L') MES = 6;
		if(str[6]=='A' && str[7]=='G' && str[8]=='O') MES = 7;
		if(str[6]=='S' && str[7]=='E' && str[8]=='T') MES = 8;
		if(str[6]=='O' && str[7]=='U' && str[8]=='T') MES = 9;
		if(str[6]=='N' && str[7]=='O' && str[8]=='V') MES = 10;
		if(str[6]=='D' && str[7]=='E' && str[8]=='Z') MES = 11;
		ANO = (str[9]-'0')*1000 + (str[10]-'0')*100 + (str[11]-'0')*10 + str[12]-'0';
		HORA = (str[14]-'0')*10 + str[15]-'0';
		MIN = (str[17]-'0')*10 + str[18]-'0';
		SEG = (str[20]-'0')*10 + str[21]-'0';
		for(int i=0; i<5; i++){
			scanf("%d", &d);
			feira=FEIRA;
			dia=DIA;
			mes=MES;
			ano=ANO;
			hora=HORA;
			min=MIN;
			seg=SEG;
			while(d-SDIA>=0){
				feira = (feira+1)%7;
				d-=SDIA;
				dia++;
				if (mes==1){
					if ((ano%4==0 && dia>29) || (ano%4!=0 && dia>28)){
						dia=1;
						mes++;
					}
				}
				else if (dia>DMES[mes]){
					dia=1;
					mes++;
				}
				if(mes==12){
					mes=0;
					ano++;
				}
			}
			while(d>0){
				d--;
				seg++;
				if(seg==60){
					seg=0;
					min++;
				}
				if(min==60){
					min=0;
					hora++;
				}
				if(hora==24){
					dia++;
					feira = (feira+1)%7;
					hora=0;
				}
				if (mes==1){
					if ((ano%4==0 && dia>29) || (ano%4!=0 && dia>28)){
						dia=1;
						mes++;
					}
				}
				else if (dia>DMES[mes]){
					dia=1;
					mes++;
				}
				if(mes==12){
					mes=0;
					ano++;
				}
			}
			if(feira==0) {str[0]='D'; str[1]='O'; str[2]='M';}
			if(feira==1) {str[0]='S'; str[1]='E'; str[2]='G';}
			if(feira==2) {str[0]='T'; str[1]='E'; str[2]='R';}
			if(feira==3) {str[0]='Q'; str[1]='U'; str[2]='A';}
			if(feira==4) {str[0]='Q'; str[1]='U'; str[2]='I';}
			if(feira==5) {str[0]='S'; str[1]='E'; str[2]='X';}
			if(feira==6) {str[0]='S'; str[1]='A'; str[2]='B';}
			str[4] = dia/10 + '0';
			str[5] = dia%10 + '0';
			if (mes==0) {str[6]='J'; str[7]='A'; str[8]='N';}
			if (mes==1) {str[6]='F'; str[7]='E'; str[8]='V';}
			if (mes==2) {str[6]='M'; str[7]='A'; str[8]='R';}
			if (mes==3) {str[6]='A'; str[7]='B'; str[8]='R';}
			if (mes==4) {str[6]='M'; str[7]='A'; str[8]='I';}
			if (mes==5) {str[6]='J'; str[7]='U'; str[8]='N';}
			if (mes==6) {str[6]='J'; str[7]='U'; str[8]='L';}
			if (mes==7) {str[6]='A'; str[7]='G'; str[8]='O';}
			if (mes==8) {str[6]='S'; str[7]='E'; str[8]='T';}
			if (mes==9) {str[6]='O'; str[7]='U'; str[8]='T';}
			if (mes==10) {str[6]='N'; str[7]='O'; str[8]='V';}
			if (mes==11) {str[6]='D'; str[7]='E'; str[8]='Z';}
			str[9] = ano/1000 + '0';
			str[10] = (char)((ano/100)%10) + '0';
			str[11] = (char)((ano/10)%10) + '0';
			str[12] = (char)(ano%10) + '0';
			str[14] = (char)(hora/10) + '0';
			str[15] = (char)(hora%10) + '0';
			str[17] = (char)(min/10) + '0';
			str[18] = (char)(min%10) + '0';
			str[20] = (char)(seg/10) + '0';
			str[21] = (char)(seg%10) + '0';
			str[22] = '\n';
			str[23] = '\0';
			printf(str);
		}
	}
	return 0;
}