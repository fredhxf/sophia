#ifndef SO_OBJ_H_
#define SO_OBJ_H_

/*
 * sophia database
 * sehia.org
 *
 * Copyright (c) Dmitry Simonenko
 * BSD License
*/

typedef enum {
	SOUNDEF   = 0L,
	SOENV     = 0x06154834L,
	SOV       = 0x2FABCDE2L,
	SODB      = 0x34591111L,
	SODBCTL   = 0x55551921L,
	SODBCONF  = 0x6FFBBDDAL,
	SOTX      = 0x13491FABL,
	SOCURSOR  = 0x45ABCDFAL
} soobjid;

static inline soobjid
so_objof(void *ptr) {
	return *(soobjid*)ptr;
}

typedef struct soobjif soobjif;
typedef struct soobj soobj;

struct soobjif {
	void *(*ctl)(soobj*, va_list);
	void *(*storage)(soobj*, va_list);
	int   (*open)(soobj*, va_list);
	int   (*destroy)(soobj*);
	int   (*set)(soobj*, va_list);
	void *(*get)(soobj*, va_list);
	int   (*del)(soobj*, va_list);
	void *(*begin)(soobj*);
	int   (*commit)(soobj*, va_list);
	int   (*rollback)(soobj*);
	void *(*cursor)(soobj*, va_list);
	void *(*backup)(soobj*);
	void *(*object)(soobj*, va_list);
	void *(*type)(soobj*, va_list);
	void *(*copy)(soobj*, va_list);
};

struct soobj {
	soobjid  oid;
	srlist   olink;
	soobjif *oif;
};

static inline void
so_objinit(soobj *o, soobjid oid, soobjif *oif)
{
	o->oid = oid;
	o->oif = oif;
	sr_listinit(&o->olink);
}

#endif
