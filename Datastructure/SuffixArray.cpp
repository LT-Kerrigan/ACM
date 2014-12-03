//rank��0��ʼ
//sa��1��ʼ,��Ϊ���һ���ַ�(��С��)���ڵ�0λ
//high��2��ʼ,��Ϊ��ʾ����sa[i-1]��sa[i]
#define M 220000
int rank[M],sa[M],X[M],Y[M],high[M],init[M];
int buc[M];
void calhigh(int n) {
	int i , j , k = 0;
	for(i = 1 ; i <= n ; i++) rank[sa[i]] = i;
	for(i = 0 ; i < n ; high[rank[i++]] = k)
		for(k?k--:0 , j = sa[rank[i]-1] ; init[i+k] == init[j+k] ; k++);
}
bool cmp(int *r,int a,int b,int l) {
	return (r[a] == r[b] && r[a+l] == r[b+l]);
}
void suffix(int n,int m = 128) {
	int i , l , p , *x = X , *y = Y;
	for(i = 0 ; i < m ; i ++) buc[i] = 0;
	for(i = 0 ; i < n ; i ++) buc[ x[i] = init[i]  ] ++;
	for(i = 1 ; i < m ; i ++) buc[i] += buc[i-1];
	for(i = n - 1; i >= 0 ; i --) sa[ --buc[ x[i] ]] = i;
	for(l = 1,p = 1 ; p < n ; m = p , l *= 2) {
		p = 0;
		for(i = n-l ; i < n ; i ++) y[p++] = i;
		for(i = 0 ; i < n ; i ++) if(sa[i] >= l) y[p++] = sa[i] - l;
		for(i = 0 ; i < m ; i ++) buc[i] = 0;
		for(i = 0 ; i < n ; i ++) buc[ x[y[i]] ] ++;
		for(i = 1 ; i < m ; i ++) buc[i] += buc[i-1];
		for(i = n - 1; i >= 0 ; i --) sa[ --buc[ x[y[i]] ] ] = y[i];
		for(swap(x,y) , x[sa[0]] = 0 , i = 1 , p = 1 ; i < n ; i ++)
			x[ sa[i] ] = cmp(y,sa[i-1],sa[i],l) ? p-1 : p++;
	}
	calhigh(n-1);//��׺����ؼ������high,������sa��ʱ��˳���rank��high�����
}
 
 
//����Ҫ����ѯ��������׺�������ǰ׺ʱ�õ�RMQ
int Log[M];
int best[20][M];
void initRMQ(int n) {//��ʼ��RMQ
	for(int i = 1; i <= n ; i ++) best[0][i] = high[i];
	for(int i = 1; i <= Log[n] ; i ++) {
		int limit = n - (1<<i) + 1;
		for(int j = 1; j <= limit ; j ++) {
			best[i][j] = min(best[i-1][j] , best[i-1][j+(1<<i>>1)]); 
		}
	}
}
int lcp(int a,int b) {//ѯ��a,b��׺�������ǰ׺
	a = rank[a];    b = rank[b];
	if(a > b) swap(a,b);
	a ++;
	int t = Log[b - a + 1];
	return min(best[t][a] , best[t][b - (1<<t) + 1]);
}
 
 
int main() {
	//Ԥ����ÿ�����ֵ�Logֵ,�����Ż�,����RMQ
	Log[0] = -1;
	for(int i = 1; i <= M ; i ++) {
		Log[i] = (i&(i-1)) ? Log[i-1] : Log[i-1] + 1 ;
	}
	//*******************************************
	//	nΪ���鳤��,�±�0��ʼ
	//	����ʼ����,������init��,���ұ�֤ÿ�����ֶ���0��
	//	m = max{ init[i] } + 1
	//	һ������´�����ַ�����,����128�㹻��
	//*******************************************
	init[n] = 0;
	suffix(n+1,m);
 
	initRMQ(n);
}