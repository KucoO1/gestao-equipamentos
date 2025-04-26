#include<stdio.h>
#include<string.h> 

main () {
	
//int i, soma=0;
//char palavra [50], letra;
//printf ("digite  a frase:\n ");
//gets(palavra);
//fflush (stdin);
//puts(palavra);
//printf ("qual letra deseja procurar:\n");
//letra = getchar();
//for (i=0; palavra [i]!='\0'; i++ ) 
//	if(letra==palavra[i])
//	soma+=1;
//
//printf(" a letra %c aparece %d vezes", letra, soma);
//
//int a,b;
//float soma;
//do {
//scanf("%d%d", &a,&b);
//   soma= (float)a/b;
//printf("a div entre %d e %d e %f.2f \n", a,b, soma);	
//} while (b!=0);

//int vetor [4], aux=0;
//for(int i=0; i<4; i++) {
//		scanf ("%d", &vetor[i]);
//	}
//
//for(int i=0; i<4; i++) {
//	for (int j= i + 1; j<4; j++) {
//		if (vetor[j] <vetor[i]) {
//		aux = vetor[j];
//		vetor[j] = vetor[i]	;
//		vetor[i] = aux;
//		}
//	}
//}
//for(int i=0; i<4; i++)
//printf ("%d", vetor[i]);


//  int vetor[8], vetor1[5], k=0;
//for (int i=0; i<8; i++) {
//scanf("%d", &vetor[i]);	
// }
// for (int i=0; i<5; i++) {
// 		scanf("%d", &vetor1[i]);	
// }
// 
// for (int i=0, j=0; i<8, j<5; i++, j++) {
//          if (vetor[i]==vetor1[j])
//          printf ("%d  ", vetor[i]);
//	 }

// int pagamento;
// float etiqueta, pague=0.0; 
// printf (" digite o preço de etiqueta ");
// scanf("%f", &etiqueta);
//  printf(" digite a forma de pagamento: ");
//  scanf("%d", &pagamento);
//  switch (pagamento) {
//  	case 1: 
//  	pague = etiqueta - (etiqueta*0.1);
//  	break;
//  		case 2: 
//  	pague = etiqueta - (etiqueta*0.15);
//  	break;
//  		case 3: 
//  	pague = etiqueta - (etiqueta*0.1);
//  	break;
//  		case 4: 
//  	pague = etiqueta + (etiqueta*0.1);
//  	break;
//  	
//  	default :
//  		printf ("valor invalido");
//  	
//  }
//   printf (" Deves pagar %f  ", pague);
//}
//int ano, ano1=2014;
//float salario=1000.0, aumento=0.15;
//printf (" Digite o ano atual\n  ");
//scanf ("%d", &ano); 
//ano-=ano1;
//for(int i=0; i<ano; i++) {
//salario= salario + (salario*aumento);
//aumento*=2;
//printf (" %d é %f\n", i+2014, salario);	
//}

//int n1, control; 
//printf (" digite o valor  ");
//scanf("%d", &n1);
//for (int i=1; i<n1+1; i++){
//	if (n1%i == 0) 
//	if (i*(i+1)*(i*2) == n1)
//printf (" e  primo");
//else 
//printf (" nao e primo");


//char c, vogal, consoante;
//int numero, simbolo;
//printf ("Digite a letra ")	;
//scanf("%c", &c);
//
// if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
//
//        if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' ||
//            c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
//            printf("Vogal\n");
//        } else {
//            printf("Consoante\n");
//        }
//    }
//    
//    else if (c >= '0' && c <= '9') {
//        printf("Numero\n");
//    }
//
//    else {
//        printf("Simbolo\n");
//    }
	
	int i,j,m,n, menor=0, linha=0;
	scanf ("%d%d", &i, &j);
	int vetor [i][j];
	while (i<20 && j<20) {
		for (m=0; m<i; m++) {
			for (n=0; n<j; n++) {
				scanf ("%d", &vetor[m][n]);
			}
		}
		menor = vetor [1][1];
		
		for (m=0; m<i; m++) {
			for (n=0; n<j; n++) {
			if (vetor [m][n] < menor) {
			menor = vetor[m][n];
			linha= m;	
			}
			
			}
		}
	 printf ("A linha do menor e  %d", linha);
	}

}





    
    	
    	
	




