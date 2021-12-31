#include "rc.h"
#include "exec.h"
#include "io.h"
#include "fns.h"

void psubst(io*, uchar*);
void pstrs(io*, word*);

char*
readhere(tree *tag, io *in)
{
	io *out;
	char c, *m;

	if(tag->type!=WORD){
		yyerror("Bad here tag");
		return 0;
	}
	pprompt();
	out = openiostr();
	m = tag->str;
	while((c = rchr(in)) != EOF){
		if(c=='\0'){
			yyerror("NUL bytes in here doc");
			closeio(out);
			return 0;
		}
		if(c=='\n'){
			lex->line++;
			if(m && *m=='\0'){
				out->bufp -= m - tag->str;
				*out->bufp='\0';
				break;
			}
			pprompt();
			m = tag->str;
		} else if(m){
			if(*m == c){
				m++;
			} else {
				m = 0;
			}
		}
		pchr(out, c);
	}
	doprompt = 1;
	return closeiostr(out);
}

void
psubst(io *f, uchar *s)
{
	int savec, n;
	uchar *t, *u;
	word *star;
	while(*s){
		if(*s!='$'){
			if(0xa0 <= *s && *s <= 0xf5){
				pchr(f, *s++);
				if(*s=='\0')
					break;
			}
			else if(0xf6 <= *s && *s <= 0xf7){
				pchr(f, *s++);
				if(*s=='\0')
					break;
				pchr(f, *s++);
				if(*s=='\0')
					break;
			}
			pchr(f, *s++);
		}
		else{
			t=++s;
			if(*t=='$')
				pchr(f, *t++);
			else{
				while(*t && idchr(*t)) t++;
				savec=*t;
				*t='\0';
				n = 0;
				for(u = s;*u && '0'<=*u && *u<='9';u++) n = n*10+*u-'0';
				if(n && *u=='\0'){
					star = vlook("*")->val;
					if(star && 1<=n && n<=count(star)){
						while(--n) star = star->next;
						pstr(f, star->word);
					}
				}
				else
					pstrs(f, vlook((char *)s)->val);
				*t = savec;
				if(savec=='^')
					t++;
			}
			s = t;
		}
	}
}

void
pstrs(io *f, word *a)
{
	if(a){
		while(a->next && a->next->word){
			pstr(f, a->word);
			pchr(f, ' ');
			a = a->next;
		}
		pstr(f, a->word);
	}
}
