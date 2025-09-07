#define LS t[x].ch[0]
#define RS t[x].ch[1]
#define FA t[x].fa
struct Node {
	int val; int ch[2],d,fa;
	Node(){
		val=ch[0]=ch[1]=fa=0;
		d=-1;
	}
	Node(int v){
		val=v;
		ch[0]=ch[1]=d=fa=0;
	}
}t[N];
int& rs(int x){return t[x].ch[t[RS].d<t[LS].d];}
// 有了 pushup，直接 merge 左右儿子就实现了删除节点并保持左偏性质
int merge(int x, int y) {
	if(!x || !y) return x|y;
	if(t[x].val<t[y].val) swap(x,y); // 大根堆就换成 >
//	pushdown(x);
	int& rs_ref=rs(x);
	rs_ref=merge(rs_ref,y);
	t[rs_ref].fa=x;
	t[x].d=t[rs(x)].d+1;
	return x;
}
void pushup(int x){
	if(!x) return;
	if(t[x].d!=t[rs(x)].d+1){
		t[x].d=t[rs(x)].d+1;
		pushup(FA);
	}
}
void erase(int x){
//	pushdown(x);
	int y=merge(LS,RS);
	t[y].fa=FA;
	if(t[FA].ch[0]==x) t[FA].ch[0]=y;
	else if(t[FA].ch[1]==x) t[FA].ch[1]=y;
	pushup(t[y].fa);
}
#undef LS
#undef RS
#undef FA
