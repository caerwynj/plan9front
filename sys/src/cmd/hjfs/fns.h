void*	emalloc(int);
void*	erealloc(void*,int);
char*	estrdup(char*);
void	bufinit(int);
Buf*	getbuf(Dev *, uvlong, int, int);
void	putbuf(Buf *);
void	sync(int);
void	pack(Buf *, uchar *);
void	unpack(Buf *, uchar *);
Dev*	newdev(char *);
ThrData*	getthrdata(void);
Fs*	initfs(Dev *, int, int);
Dentry*	getdent(FLoc *, Buf *);
int	getfree(Fs *, uvlong *);
int	putfree(Fs *, uvlong);
Chan*	chanattach(Fs *, int);
Chan*	chanclone(Chan *);
int	chanwalk(Chan *, char *);
int	chancreat(Chan *, char *, int, int);
int	chanopen(Chan *, int mode);
int	chanwrite(Chan *, void *, ulong, uvlong);
int	chanread(Chan *, void *, ulong, uvlong);
int	chanstat(Chan *, Dir *);
int	chanwstat(Chan *, Dir *);
int	permcheck(Fs *, Dentry *, short, int);
char *	uid2name(Fs *, short, char *);
int	name2uid(Fs *, char *, short *);
void	start9p(char *, char **, int);
int	chanclunk(Chan *);
int	chanremove(Chan *);
int	getblk(Fs *, FLoc *, Buf *, uvlong, uvlong *, int);
void	initcons(char *);
void	shutdown(void);
int	fsdump(Fs *);
int	willmodify(Fs *, Loc *, int);
void	chbegin(Chan *);
void	chend(Chan *);
int	newqid(Fs *, uvlong *);
Loc *	getloc(Fs *, FLoc, Loc *);
int	haveloc(Fs *, uvlong, int, Loc *);
Loc *	cloneloc(Fs *, Loc *);
void	putloc(Fs *, Loc *, int);
int	findentry(Fs *, FLoc *, Buf *, char *, FLoc *, int);
void	modified(Loc *, Dentry *, short);
int	trunc(Fs *, FLoc *, Buf *, uvlong);
void	dprint(char *fmt, ...);
#pragma	varargck argpos dprint 1
int	delete(Fs *, FLoc *, Buf *);
int	chref(Fs *, uvlong, int);
int	newentry(Fs *, Loc *, Buf *, char *, FLoc *, int);
int	namevalid(char *);
int	usersload(Fs *, Chan *);
int	userssave(Fs *, Chan *);
int	ingroup(Fs *, short, short, int);
void	workerinit(void);
void	writeusers(Fs *);
void	readusers(Fs *);
