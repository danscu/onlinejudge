#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define N 100005
#define MOD 1000000007
#define LL long long
using namespace std;

#define CLR(x) memset(x, 0, sizeof x);
#define CLRN(x, n) memset(x, 0, (n)*sizeof x[0]);
#define CLRVN(x, v, n) memset(x, v, (n)*sizeof x[0]);
#define REP(v,n) for(int v=0;v<n;v++)
#define FOR(v,a,b) for(int v=a;v<=b;v++)
#define every(iter, iterable) \
    typeof((iterable).begin()) iter = (iterable).begin(); iter != (iterable).end(); iter++
typedef unsigned long long Num;
const int maxn = 150;
const int maxk = 20;
const int maxm = 100;

struct Trie{
    Trie *next[maxk];
    Trie *fail;
    int kind,isword;
};
Trie *que[N],s[N];
int idx;
int k;
int id(int x){
    return x;
}
Trie *NewTrie(){
    //静态Trie
    Trie *tmp=&s[idx];
    for(int i=0;i<k;i++) tmp->next[i]=NULL;
    tmp->isword=0;
    tmp->fail=NULL;
    tmp->kind=idx++;
    return tmp;
}
void Insert(Trie *root,int *s,int len){
    Trie *tmp=root;
    for(int i=0;i<len;i++){
        if(tmp->next[id(s[i])]==NULL) tmp->next[id(s[i])]=NewTrie();
        tmp=tmp->next[id(s[i])];
    }
    tmp->isword=1;
}
void Bulid_fail(Trie *root){
    int tail=0,head=0;
    que[tail++]=root;
    root->fail=NULL;
    while(head<tail){
        Trie *tmp=que[head++];
        for(int i=0;i<k;i++){
            if(tmp->next[i]==NULL){
                if(tmp==root) tmp->next[i]=root;
                else tmp->next[i]=tmp->fail->next[i];
            }
            else{
                if(tmp==root) tmp->next[i]->fail=root;
                else{
                    tmp->next[i]->fail=tmp->fail->next[i];
                    if(tmp->next[i]->fail->isword)
                        tmp->next[i]->isword=1;
                }
                que[tail++]=tmp->next[i];
            }
        }
    }
}
struct Matrix{
    LL m[maxn][maxn];
}Init;
Matrix mult(Matrix m1,Matrix m2){
    Matrix ans;
    memset(ans.m,0,sizeof(ans.m));
    for(int i=0;i<idx;i++){
        for(int k=0;k<idx;k++){
            if(m1.m[i][k]==0) continue;
            for(int j=0;j<idx;j++){
                ans.m[i][j]+=(LL)m1.m[i][k]*m2.m[k][j];
                if(ans.m[i][j]>=MOD) ans.m[i][j]%=MOD;
            }
        }
    }
    return ans;
}
Matrix PowMod(Matrix m1,int n){
    Matrix ans;
    for(int i=0;i<idx;i++) for(int j=0;j<idx;j++) ans.m[i][j]=i==j;
    while(n){
        if(n&1) ans=mult(ans,m1);
        m1=mult(m1,m1);
        n>>=1;
    }
    return ans;
}
int main(){
#if BENCH
    freopen("files/1_rand.txt","r",stdin);
#endif
    int m,n,T;
    int sym[maxk];
    scanf("%d", &T);
    for(int tc = 0; tc < T; tc++) {
        while(scanf("%d%d%d",&n,&k,&m)!=EOF){
            idx=0;
            Trie *root=NewTrie();
            REP(i,m) {
                int l;
                scanf("%d", &l);
                REP(j,l)
                scanf("%d", &sym[j]);
                Insert(root, sym, l);
            }

            Bulid_fail(root);
            memset(Init.m,0,sizeof(Init.m));
            for(int i=0;i<idx;i++){
                for(int j=0;j<k;j++){
                    Trie *son=s[i].next[j];
                    if(!son->isword&&!s[i].isword)
                        Init.m[i][son->kind]++;
                }
            }
#define DBG 1
#if DBG
        printf("----mat----\n");
        REP(i,idx) {
            REP(j,idx)
                printf("%lld ", Init.m[i][j]);
            printf("\n");
        }
#endif            
            
            Init=PowMod(Init,n);
            
#if DBG
        printf("----pow----\n");
        REP(i,idx) {
            REP(j,idx)
                printf("%lld ", Init.m[i][j]);
            printf("\n");
        }
#endif                 
            
            LL ans=0;
            for(int i=0;i<idx;i++){
                ans+=Init.m[0][i];
                if(ans>=MOD) ans-=MOD;
            }
            printf("Case #%d\n", tc+1);
            printf("%lld\n",ans);
        }
    }
    return 0;
}
