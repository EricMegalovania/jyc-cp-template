#ifndef __LOCAL_TEST
#define __LOCAL_TEST
#define s S.c_str()
char TEST_GEN[1000],TEST_ANS[1000],TEST_OUT[1000],TEST_FC[1000];
void TEST(string S,string sol="sol",string exe="exe"){
	assert(exe=="exe" || exe=="py");
	sprintf(TEST_GEN,"%s_gen.exe > %s_input.txt",s,s);
	sprintf(TEST_ANS,"%s_%s.exe < %s_input.txt > %s_ans.txt",s,sol.c_str(),s,s);
	if(exe=="exe") sprintf(TEST_OUT,"%s.exe < %s_input.txt > %s_out.txt",s,s,s);
	else sprintf(TEST_OUT,"python %s.py < %s_input.txt > %s_out.txt",s,s,s);
	sprintf(TEST_FC,"fc %s_ans.txt %s_out.txt /n",s,s);
	while(1){
		cerr<<"gen"<<endl; system(TEST_GEN);
		cerr<<"ans"<<endl; system(TEST_ANS);
		cerr<<"out"<<endl; system(TEST_OUT);
		if(system(TEST_FC)) break;
	}
}
#undef s
#endif
