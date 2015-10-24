/*
  bsdiff.c -- Binary patch generator.

  Copyright 2003 Colin Percival

  For the terms under which this work may be distributed, please see
  the adjoining file "LICENSE".

  ChangeLog:
  2005-05-05 - Use the modified header struct from bspatch.h; use 32-bit
               values throughout.
                 --Benjamin Smedberg <benjamin@smedbergs.us>
  2005-05-18 - Use the same CRC algorithm as bzip2, and leverage the CRC table
               provided by libbz2.
                 --Darin Fisher <darin@meer.net>
*/

#include "stdafx.h"
#include "bspatch.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdarg.h>
#ifdef XP_WIN
#include <io.h>
#include <winsock2.h>
#else
#include <unistd.h>
#include <arpa/inet.h>
#define _O_BINARY 0
#endif

#undef MIN
#define MIN(x,y) (((x)<(y)) ? (x) : (y))

static void reporterr(int e, const char *fmt, ...)
{
	if (fmt)
    {
		va_list args;
		va_start(args, fmt);
		vfprintf(stderr, fmt, args);
		va_end(args);
	}

	exit(e);
}

static void
split(PROffset32 *I,PROffset32 *V,PROffset32 start,PROffset32 len,PROffset32 h)
{
	PROffset32 i,j,k,x,tmp,jj,kk;

	if(len<16) {
		for(k=start;k<start+len;k+=j) {
			j=1;x=V[I[k]+h];
			for(i=1;k+i<start+len;i++) {
				if(V[I[k+i]+h]<x) {
					x=V[I[k+i]+h];
					j=0;
				};
				if(V[I[k+i]+h]==x) {
					tmp=I[k+j];I[k+j]=I[k+i];I[k+i]=tmp;
					j++;
				};
			};
			for(i=0;i<j;i++) V[I[k+i]]=k+j-1;
			if(j==1) I[k]=-1;
		};
		return;
	};

	x=V[I[start+len/2]+h];
	jj=0;kk=0;
	for(i=start;i<start+len;i++) {
		if(V[I[i]+h]<x) jj++;
 		if(V[I[i]+h]==x) kk++;
 	};
 	jj+=start;kk+=jj;
 
 	i=start;j=0;k=0;
 	while(i<jj) {
 		if(V[I[i]+h]<x) {
 			i++;
 		} else if(V[I[i]+h]==x) {
 			tmp=I[i];I[i]=I[jj+j];I[jj+j]=tmp;
 			j++;
 		} else {
 			tmp=I[i];I[i]=I[kk+k];I[kk+k]=tmp;
 			k++;
 		};
 	};
 
 	while(jj+j<kk) {
 		if(V[I[jj+j]+h]==x) {
 			j++;
 		} else {
 			tmp=I[jj+j];I[jj+j]=I[kk+k];I[kk+k]=tmp;
 			k++;
 		};
 	};
 
 	if(jj>start) split(I,V,start,jj-start,h);
 
 	for(i=0;i<kk-jj;i++) V[I[jj+i]]=kk-1;
 	if(jj==kk-1) I[jj]=-1;
 
 	if(start+len>kk) split(I,V,kk,start+len-kk,h);
 }
 
 static void
 qsufsort(PROffset32 *I,PROffset32 *V,unsigned char *old,PROffset32 oldsize)
 {
 	PROffset32 buckets[256];
 	PROffset32 i,h,len;
 
 	for(i=0;i<256;i++) buckets[i]=0;
 	for(i=0;i<oldsize;i++) buckets[old[i]]++; // 元素个数统计

#ifdef _DEBUG
    
    CWnd *m_pDesktopWnd = NULL;
    CDC  *m_pDeskTopDC = NULL;

    //查找“Program Manager”窗口
    HWND hWnd= (HWND)::FindWindow("Progman", "Program Manager");
    if (hWnd != NULL)
    {
        //找到“Program Manager”窗口,下面将通过该窗口找到桌面的窗口句柄
        HWND wnd = ::FindWindowEx(hWnd, NULL, "SHELLDLL_DefView", NULL);
        CWnd pWnd;
        pWnd.Attach(wnd);

        if (hWnd != NULL)
        {
            //取得桌面ListView控件的窗口句柄
            //真正的桌面,可以用spy++查看
            m_pDesktopWnd = pWnd.GetDlgItem(1);

            m_pDeskTopDC = m_pDesktopWnd->GetWindowDC();
        }

        pWnd.Detach();
    }

    FILE *file = fopen("bsdiff_buckets.txt", "w+b");
    
    //fprintf(file, "buckets_src[0]=%d\n", buckets[0]);
    m_pDeskTopDC->MoveTo(50, 400-buckets[0]*0.001);

    for(i=1;i<256;i++)
    {
        //fprintf(file, "buckets_src[%d]=%d\n", i, buckets[i]);
        m_pDeskTopDC->LineTo(50 + i * 2, 400-buckets[i]*0.001);
    }

#endif // _DEBUG

    for(i=1;i<256;i++) buckets[i]+=buckets[i-1]; // 前后相加，是一条上升曲线

 	for(i=255;i>0;i--) buckets[i]=buckets[i-1];
 	buckets[0]=0;

#ifdef _DEBUG

    fprintf(file, "buckets_add[0]=%d\n", buckets[0]);
    m_pDeskTopDC->MoveTo(600, 400-buckets[0]*0.0001);

    for(i=1;i<256;i++)
    {
        fprintf(file, "buckets_add[%d]=%d\n", i, buckets[i]);
        m_pDeskTopDC->LineTo(600 + i * 2, 400-buckets[i]*0.0001);
    }
#endif // _DEBUG

    TCHAR temp[MAX_PATH] = "";
 
    for(i=0;i<oldsize;i++)
    {
        // 按Ascii顺序分组排列位置
        // 序号  0 1 2 3 4 5 6 7 8 9 A B C
        // old[]=a b c a c d e b c d a a f
        // I[]  =0 3 A B 1 7 2 4 8 5 9 6 C
        //      |-------|---|-----|---|-|-|
        //          a     b    c    d  e f
        
        // buckets最大为old的大小,I的大小为old长的4倍
        
        I[++buckets[old[i]]]=i;

#ifdef _DEBUG

        sprintf(temp, "old[%d]=%d buckets[%d]=%d I[%d]=%d\n", 
            i, old[i], old[i], buckets[old[i]], buckets[old[i]], I[buckets[old[i]]]);

        fprintf(file, temp);

        TRACE(temp);

#endif // _DEBUG
    }
 	I[0]=oldsize;

#ifdef _DEBUG

    //fprintf(file, "buckets_I[0]=%d\n", buckets[0]);
    m_pDeskTopDC->MoveTo(600, 200-buckets[0]*0.0001);

    for(i=1;i<256;i++)
    {
        //fprintf(file, "buckets_I[%d]=%d\n", i, buckets[i]);
        m_pDeskTopDC->LineTo(600 + i * 2, 200-buckets[i]*0.0001);
    }

    for(i=0;i<oldsize+1;i++)
    fprintf(file, "I[%d]=%d\n", i, I[i]);
#endif // _DEBUG

 	for(i=0;i<oldsize;i++) V[i]=buckets[old[i]]; // 记录每个元素的数量与前一个组的数量合
 	V[oldsize]=0;
 	for(i=1;i<256;i++) if(buckets[i]==buckets[i-1]+1) I[buckets[i]]=-1; // 当此元素只有一个置为-1
 	I[0]=-1;

#ifdef _DEBUG
    fprintf(file, "-------------------split pre\n");

    for(i=0;i<oldsize+1;i++)
        fprintf(file, "I[%d]=%d V[%d]=%d\n", i, I[i], i, V[i]);
#endif // _DEBUG
 
 	for(h=1;I[0]!=-(oldsize+1);h+=h) {
 		len=0;
 		for(i=0;i<oldsize+1;) {
 			if(I[i]<0) {
 				len-=I[i];
 				i-=I[i];
 			} else {
 				if(len) I[i-len]=-len;
 				len=V[I[i]]+1-i;
 				split(I,V,i,len,h);
 				i+=len;
 				len=0;
 			};
 		};
 		if(len) I[i-len]=-len;

#ifdef _DEBUG
        fprintf(file, "-------------------split h=%d len=%d\n", h, len);

        for(i=0;i<oldsize+1;i++)
        {
            fprintf(file, "I[%d]=%d V[%d]=%d\n", i, I[i], i, V[i]);
        }
#endif // _DEBUG
 	};
 
 	for(i=0;i<oldsize+1;i++) I[V[i]]=i;

#ifdef _DEBUG
    fprintf(file, "-------------------split over\n");

    for(i=0;i<oldsize+1;i++)
    {
        fprintf(file, "I[%d]=%d V[%d]=%d\n", i, I[i], i, V[i]);
    }

    fclose(file);
#endif // _DEBUG
 }
 
 static PROffset32
 matchlen(unsigned char *old,PROffset32 oldsize,unsigned char *newbuf,PROffset32 newsize)
 {
 	PROffset32 i;
 
 	for(i=0;(i<oldsize)&&(i<newsize);i++)
 		if(old[i]!=newbuf[i]) break;
 
 	return i;
 }
 
 static PROffset32
 search(PROffset32 *I,unsigned char *old,PROffset32 oldsize,
        unsigned char *newbuf,PROffset32 newsize,PROffset32 st,PROffset32 en,PROffset32 *pos)
 {
 	PROffset32 x,y;
 
 	if(en-st<2) {
 		x=matchlen(old+I[st],oldsize-I[st],newbuf,newsize);
 		y=matchlen(old+I[en],oldsize-I[en],newbuf,newsize);
 
 		if(x>y) {
 			*pos=I[st];
 			return x;
 		} else {
 			*pos=I[en];
 			return y;
 		}
 	};
 
 	x=st+(en-st)/2;
 	if(memcmp(old+I[x],newbuf,MIN(oldsize-I[x],newsize))<0) {
 		return search(I,old,oldsize,newbuf,newsize,x,en,pos);
 	} else {
 		return search(I,old,oldsize,newbuf,newsize,st,x,pos);
 	};
 }
 
 int CreateBinaryPatch(const char *oldFile, const char *newFile, const char *patchFile)
 {
     if (NULL == oldFile || NULL == newFile || NULL == patchFile) return -1;

 	int fd;
 	unsigned char *old,*newbuf;
 	PROffset32 oldsize,newsize;
 	PROffset32 *I,*V;
 
 	PROffset32 scan,pos,len;
 	PROffset32 lastscan,lastpos,lastoffset;
 	PROffset32 oldscore,scsc;
 
 	PROffset32 s,Sf,lenf,Sb,lenb;
 	PROffset32 overlap,Ss,lens;
 	PROffset32 i;
 
 	PROffset32 dblen,eblen;
 	unsigned char *db,*eb;
 
 	unsigned int scrc;      // 校验码
    
    PRUint32 numtriples;    // 节点个数
 
 	MBSPatchHeader header =
    {
 		{'M','B','D','I','F','F','1','0'},
 		0, 0, 0, 0, 0, 0
 	};

 	/* Allocate oldsize+1 bytes instead of oldsize bytes to ensure
 		that we never try to malloc(0) and get a NULL pointer */
 	if(((fd=open(oldFile,O_RDONLY|_O_BINARY,0))<0) ||
 		((oldsize=lseek(fd,0,SEEK_END))==-1) ||
 		((old=(unsigned char*) malloc(oldsize+1))==NULL) ||
 		(lseek(fd,0,SEEK_SET)!=0) ||
 		(read(fd,old,oldsize)!=oldsize) ||
 		(close(fd)==-1))
 		reporterr(1,"%s\n",oldFile);
 
 	scrc = crc32(old, oldsize);
 
 	if(((I=(PROffset32*) malloc((oldsize+1)*sizeof(PROffset32)))==NULL) ||
 		((V=(PROffset32*) malloc((oldsize+1)*sizeof(PROffset32)))==NULL))
 		reporterr(1,NULL);
 
 	qsufsort(I,V,old,oldsize);
 
 	free(V);
 
 	/* Allocate newsize+1 bytes instead of newsize bytes to ensure
 		that we never try to malloc(0) and get a NULL pointer */
 	if(((fd=open(newFile,O_RDONLY|_O_BINARY,0))<0) ||
 		((newsize=lseek(fd,0,SEEK_END))==-1) ||
 		((newbuf=(unsigned char*) malloc(newsize+1))==NULL) ||
 		(lseek(fd,0,SEEK_SET)!=0) ||
 		(read(fd,newbuf,newsize)!=newsize) ||
 		(close(fd)==-1)) reporterr(1,"%s\n",newFile);
 
 	if(((db=(unsigned char*) malloc(newsize+1))==NULL) ||
 		((eb=(unsigned char*) malloc(newsize+1))==NULL))
 		reporterr(1,NULL);
 
 	dblen=0;
 	eblen=0;
 
 	if((fd=open(patchFile,O_CREAT|O_TRUNC|O_WRONLY|_O_BINARY,0666))<0)
 		reporterr(1,"%s\n",patchFile);
 
 	/* start writing here */
 
 	/* We don't know the lengths yet, so we will write the header again
 		 at the end */
 
 	if(write(fd,&header,sizeof(MBSPatchHeader))!=sizeof(MBSPatchHeader))
 		reporterr(1,"%s\n",patchFile);
 
 	scan=0;len=0;
 	lastscan=0;lastpos=0;lastoffset=0;
 	numtriples = 0;
 	while(scan<newsize) {
 		oldscore=0;
 
 		for(scsc=scan+=len;scan<newsize;scan++) {
 			len=search(I,old,oldsize,newbuf+scan,newsize-scan,
 					0,oldsize,&pos);
 
 			for(;scsc<scan+len;scsc++)
 			if((scsc+lastoffset<oldsize) &&
 				(old[scsc+lastoffset] == newbuf[scsc]))
 				oldscore++;
 
 			if(((len==oldscore) && (len!=0)) || 
 				(len>oldscore+8)) break;
 
 			if((scan+lastoffset<oldsize) &&
 				(old[scan+lastoffset] == newbuf[scan]))
 				oldscore--;
 		};
 
 		if((len!=oldscore) || (scan==newsize)) {
 			MBSPatchTriple triple;
 
 			s=0;Sf=0;lenf=0;
 			for(i=0;(lastscan+i<scan)&&(lastpos+i<oldsize);) {
 				if(old[lastpos+i]==newbuf[lastscan+i]) s++;
 				i++;
 				if(s*2-i>Sf*2-lenf) { Sf=s; lenf=i; };
 			};
 
 			lenb=0;
 			if(scan<newsize) {
 				s=0;Sb=0;
 				for(i=1;(scan>=lastscan+i)&&(pos>=i);i++) {
 					if(old[pos-i]==newbuf[scan-i]) s++;
 					if(s*2-i>Sb*2-lenb) { Sb=s; lenb=i; };
 				};
 			};
 
 			if(lastscan+lenf>scan-lenb) {
 				overlap=(lastscan+lenf)-(scan-lenb);
 				s=0;Ss=0;lens=0;
 				for(i=0;i<overlap;i++) {
 					if(newbuf[lastscan+lenf-overlap+i]==
 					   old[lastpos+lenf-overlap+i]) s++;
 					if(newbuf[scan-lenb+i]==
 					   old[pos-lenb+i]) s--;
 					if(s>Ss) { Ss=s; lens=i+1; };
 				};
 
 				lenf+=lens-overlap;
 				lenb-=lens;
 			};
 
 			for(i=0;i<lenf;i++)
 				db[dblen+i]=newbuf[lastscan+i]-old[lastpos+i];
 			for(i=0;i<(scan-lenb)-(lastscan+lenf);i++)
 				eb[eblen+i]=newbuf[lastscan+lenf+i];
 
 			dblen+=lenf;
 			eblen+=(scan-lenb)-(lastscan+lenf);
 
 			triple.x = htonl(lenf);
 			triple.y = htonl((scan-lenb)-(lastscan+lenf));
 			triple.z = htonl((pos-lenb)-(lastpos+lenf));
 			if (write(fd,&triple,sizeof(triple)) != sizeof(triple))
 				reporterr(1,NULL);
 
 #ifdef _DEBUG
 			TRACE("Writing a block: X=%u,Y=%u,Z=%i\n",
 			       (PRUint32) lenf,
 			       (PRUint32) ((scan-lenb)-(lastscan+lenf)),
 			       (PRUint32) ((pos-lenb)-(lastpos+lenf)));
 #endif
 
 			++numtriples;
 
 			lastscan=scan-lenb;
 			lastpos=pos-lenb;
 			lastoffset=pos-scan;
 		};
 	};
 
 	if(write(fd,db,dblen)!=dblen)
 		reporterr(1,NULL);
 
 	if(write(fd,eb,eblen)!=eblen)
 		reporterr(1,NULL);
 
 	header.slen	    = htonl(oldsize);
 	header.scrc32	= htonl(scrc);
 	header.dlen	    = htonl(newsize);
 	header.cblen	= htonl(numtriples * sizeof(MBSPatchTriple));
 	header.difflen	= htonl(dblen);
 	header.extralen = htonl(eblen);
 
 	if (lseek(fd,0,SEEK_SET) == -1 ||
 	    write(fd,&header,sizeof(header)) != sizeof(header) ||
 	    close(fd) == -1)
 		reporterr(1,NULL);
 
 	free(db);
 	free(eb);
 	free(I);
 	free(old);
 	free(newbuf);

 	return 0;
 }