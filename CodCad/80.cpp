#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for (int i=0;i<n;i++)
#define mp(x,y) make_pair(x,y)
#define pb(x) push_back(x)
#define F first
#define S second

int v[11][53], baralho[300], mao[11];
int p,m,n, descarte, jogador, topo, direcao;
char c;

int Carta()
{
	int numero;
    scanf(" %d %c ", &numero, &c);

    if (c == 'D')   numero +=13;
    if (c == 'H')   numero +=26;
    if (c == 'S')   numero +=39;

    return numero;
}

bool mesmoNaipe(int i, int j)
{
	return (i-1)/13 == (j-1)/13;
}

bool mesmoNumero(int i, int j)
{
	return i%13 == j%13;
}

void puxar(int atual)
{
    if (topo < n)
    {
		//printf("%d puxou %d-%d\n", atual, (baralho[topo]-1)%13 + 1, (baralho[topo]-1)/13 +1);
        v[atual][baralho[topo]]++;
        topo++;
        mao[atual]++;
    }
}

int proxJogador(int atual)
{
    if (atual+direcao == p+1) return 1;
    if (atual+direcao == 0) return p;
    return atual+direcao;
}

void efeitosEspeciais()
{
    if (descarte%13 == 1)
    {
		puxar(proxJogador(jogador));
        jogador = proxJogador(jogador);
    }
    else if (descarte%13 == 7)
    {
		puxar(proxJogador(jogador));
		puxar(proxJogador(jogador));
        jogador = proxJogador(jogador);
    }
    else if (descarte%13 == 11) jogador = proxJogador(jogador);
    else if (descarte%13 == 12) direcao *= -1;
}

bool fazerJogada()
{
    bool conseguiu = false;
	
	for (int k=13; k>=1 && !conseguiu; k--){
		for(int i=39 + k; i>=1 && !conseguiu; i -= 13){
			if (v[jogador][i]!=0 && (mesmoNaipe(i, descarte) || mesmoNumero(i, descarte))){
				v[jogador][i]--;
				mao[jogador]--;
				descarte = i;
				conseguiu = true;
				//printf("%d descartou %d-%d\n", jogador, (i-1)%13 + 1, (i-1)/13 + 1);
			}
		}
	}
	
	if (conseguiu) efeitosEspeciais();
	
	return conseguiu;
}

int main()
{
    while(scanf("%d %d %d", &p,&m,&n) && p!=0)
    {

        rep(j,53) rep(i,11) v[i][j] = 0;
        rep(i,300) baralho[i]=0;

        topo = 0;
        rep(i,n) baralho[i]=Carta();
        rep(i,p) mao[i+1] = 0;
        rep(i,p) rep(j,m) puxar(i+1);

        jogador = 1;
        direcao = 1;
        descarte = baralho[topo];
		topo++;
		//printf("inicio: %d-%d\n", (descarte-1)%13 + 1, (descarte-1)/13 + 1);
		efeitosEspeciais();

		bool acabou = false;
		int vencedor;
		
        while(!acabou)
        {
			//printf("topo = %d\n", topo);
            if (!fazerJogada())
            {
                puxar(jogador);
				fazerJogada();
            }
			
			for(int i=1; i<=p; i++){
				//printf("mao[%d] = %d\n", i, mao[i]);
				if (mao[i] == 0)
				{
					acabou = true;
					vencedor = i;
				}
			}

            jogador = proxJogador(jogador);
        }
        //printf ("vencedor : %d\n\n", vencedor);
        printf ("%d ", vencedor);
    }
	printf("\n");
    return 0;
}