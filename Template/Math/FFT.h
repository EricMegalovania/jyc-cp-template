using LD=double;
using CP=complex<LD>;
const LD pi=3.1415926535897932384626;

vector<int>rev{0};
void FFT(vector<CP>& a,const int& on=1){
	const int n=a.size();
//	assert(on==1 || on==-1);
//	assert((1<<__lg(n))==n);
	for(int i=0;i<n;i++) if(i<rev[i]){
		swap(a[i],a[rev[i]]);
	}
	for(int h=2;h<=n;h<<=1){
		CP wn(cos(pi*2/h),sin(pi*2/h));
		for(int j=0;j<n;j+=h){
			CP w(1,0);
			for(int k=j;k<j+h/2;k++){
				CP u=a[k];
				CP t=w*a[k+h/2];
				a[k]=u+t;
				a[k+h/2]=u-t;
				w*=wn;
			}
		}
	}
	if(on==-1){
		reverse(a.begin()+1,a.end());
		for(auto& x:a) x/=n;
	}
}
void mul(vector<CP>& a,vector<CP>& b){ //a=a*b, b is changed
	int n=a.size()+b.size()-1;
	int len=1<<__lg(n);
	if(len<n) len<<=1;
	//init rev
	rev.resize(len,0);
	for(int i=1;i<len;i++){
		rev[i]=rev[i>>1]>>1;
		if(i&1){
			rev[i]|=len>>1;
		}
	}
	//resize a, b
	a.resize(len,CP());
	b.resize(len,CP());
	FFT(a),FFT(b);
	for(int i=0;i<len;i++){
		a[i]*=b[i];
	}
	FFT(a,-1);
}
