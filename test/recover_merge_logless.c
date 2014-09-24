
/*
 * sophia database
 * sphia.org
 *
 * Copyright (c) Dmitry Simonenko
 * BSD License
*/

#include <libsr.h>
#include <sophia.h>
#include "suite.h"

static void
test_recover_merge_logless_replace_get0(void)
{
	rmrf("./test");
	rmrf("./log");

	void *env = sp_env();
	t( env != NULL );
	void *db = sp_storage(env);
	t( db != NULL );
	void *c = sp_ctl(db, "conf");
	t( c != NULL );
	t( sp_set(c, "storage.dir", "test") == 0 );
	t( sp_set(c, "storage.node_branch_wm", 0) == 0 );
	t( sp_set(c, "storage.node_merge_wm", 1) == 0 );
	t( sp_set(c, "storage.threads", 0) == 0 );
	t( sp_open(env) == 0 );

	int i = 0;
	while ( i < 949 ) {
		void *o = sp_object(db);
		t( o != NULL );
		t( sp_set(o, "key", &i, sizeof(i)) == 0 );
		t( sp_set(o, "value", &i, sizeof(i)) == 0 );
		t( sp_set(db, o) == 0 );
		i++;
	}
	t( sp_set(sp_ctl(db, "ctl"), "branch") == 0 );
	t( sp_set(sp_ctl(db, "ctl"), "merge") == 0 );
	i = 0;
	while ( i < 949 ) {
		int value = i + 1;
		void *o = sp_object(db);
		t( o != NULL );
		t( sp_set(o, "key", &i, sizeof(i)) == 0 );
		t( sp_set(o, "value", &value, sizeof(value)) == 0 );
		t( sp_set(db, o) == 0 );
		i++;
	}
	/* log rotation */
	t( sp_destroy(env) == 0 );

	env = sp_env();
	t( env != NULL );
	db = sp_storage(env);
	t( db != NULL );
	c = sp_ctl(db, "conf");
	t( c != NULL );
	t( sp_set(c, "storage.dir", "test") == 0 );
	t( sp_set(c, "storage.node_branch_wm", 0) == 0 );
	t( sp_set(c, "storage.node_merge_wm", 1) == 0 );
	t( sp_set(c, "storage.threads", 0) == 0 );
	t( sp_open(env) == 0 );

	/* reply log */
	i = 0;
	while ( i < 949 ) {
		int value = i + 1;
		void *o = sp_object(db);
		t( o != NULL );
		t( sp_set(o, "key", &i, sizeof(i)) == 0 );
		t( sp_set(o, "value", &value, sizeof(value)) == 0 );
		t( sp_set(db, o) == 0 );
		i++;
	}

	i = 0;
	while (i < 949) {
		void *o = sp_object(db);
		t( sp_set(o, "key", &i, sizeof(i)) == 0 );
		o = sp_get(db, o);
		t( o != NULL );
		t( *(int*)sp_get(o, "value", NULL) == i + 1 );
		sp_destroy(o);
		i++;
	}
	t( sp_destroy(env) == 0 );
}

static void
test_recover_merge_logless_replace_get1(void)
{
	rmrf("./test");
	rmrf("./log");

	void *env = sp_env();
	t( env != NULL );
	void *db = sp_storage(env);
	t( db != NULL );
	void *c = sp_ctl(db, "conf");
	t( c != NULL );
	t( sp_set(c, "storage.dir", "test") == 0 );
	t( sp_set(c, "storage.node_branch_wm", 0) == 0 );
	t( sp_set(c, "storage.node_merge_wm", 1) == 0 );
	t( sp_set(c, "storage.threads", 0) == 0 );
	t( sp_open(env) == 0 );

	int i = 0;
	while ( i < 949 ) {
		void *o = sp_object(db);
		t( o != NULL );
		t( sp_set(o, "key", &i, sizeof(i)) == 0 );
		t( sp_set(o, "value", &i, sizeof(i)) == 0 );
		t( sp_set(db, o) == 0 );
		i++;
	}
	t( sp_set(sp_ctl(db, "ctl"), "branch") == 0 );
	t( sp_set(sp_ctl(db, "ctl"), "merge") == 0 );
	i = 0;
	while ( i < 949 ) {
		int value = i + 1;
		void *o = sp_object(db);
		t( o != NULL );
		t( sp_set(o, "key", &i, sizeof(i)) == 0 );
		t( sp_set(o, "value", &value, sizeof(value)) == 0 );
		t( sp_set(db, o) == 0 );
		i++;
	}
	/* log rotation */
	t( sp_destroy(env) == 0 );

	env = sp_env();
	t( env != NULL );
	db = sp_storage(env);
	t( db != NULL );
	c = sp_ctl(db, "conf");
	t( c != NULL );
	t( sp_set(c, "storage.dir", "test") == 0 );
	t( sp_set(c, "storage.node_branch_wm", 0) == 0 );
	t( sp_set(c, "storage.node_merge_wm", 1) == 0 );
	t( sp_set(c, "storage.threads", 0) == 0 );
	t( sp_open(env) == 0 );

	/* reply log */
	i = 0;
	while ( i < 949 ) {
		int value = i + 1;
		void *o = sp_object(db);
		t( o != NULL );
		t( sp_set(o, "key", &i, sizeof(i)) == 0 );
		t( sp_set(o, "value", &value, sizeof(value)) == 0 );
		t( sp_set(db, o) == 0 );
		i++;
	}

	i = 0;
	while (i < 949) {
		void *o = sp_object(db);
		t( sp_set(o, "key", &i, sizeof(i)) == 0 );
		o = sp_get(db, o);
		t( o != NULL );
		t( *(int*)sp_get(o, "value", NULL) == i + 1 );
		sp_destroy(o);
		i++;
	}
	t( sp_destroy(env) == 0 );
}

static void
test_recover_merge_logless_set_replace_get0(void)
{
	rmrf("./test");
	rmrf("./log");

	void *env = sp_env();
	t( env != NULL );
	void *db = sp_storage(env);
	t( db != NULL );
	void *c = sp_ctl(db, "conf");
	t( c != NULL );
	t( sp_set(c, "storage.dir", "test") == 0 );
	t( sp_set(c, "storage.node_branch_wm", 0) == 0 );
	t( sp_set(c, "storage.node_merge_wm", 1) == 0 );
	t( sp_set(c, "storage.threads", 0) == 0 );
	t( sp_open(env) == 0 );

	int key = 7;
	void *o = sp_object(db);
	t( o != NULL );
	t( sp_set(o, "key", &key, sizeof(key)) == 0 );
	t( sp_set(o, "value", &key, sizeof(key)) == 0 );
	t( sp_set(db, o) == 0 );
	t( sp_set(sp_ctl(db, "ctl"), "branch") == 0 );
	t( sp_set(sp_ctl(db, "ctl"), "merge") == 0 );
	t( sp_destroy(env) == 0 );

	env = sp_env();
	t( env != NULL );
	db = sp_storage(env);
	t( db != NULL );
	c = sp_ctl(db, "conf");
	t( c != NULL );
	t( sp_set(c, "storage.dir", "test") == 0 );
	t( sp_set(c, "storage.node_branch_wm", 0) == 0 );
	t( sp_set(c, "storage.node_merge_wm", 1) == 0 );
	t( sp_set(c, "storage.threads", 0) == 0 );
	t( sp_open(env) == 0 );
	key = 7;
	int value = 8;
	o = sp_object(db);
	t( o != NULL );
	t( sp_set(o, "key", &key, sizeof(key)) == 0 );
	t( sp_set(o, "value", &value, sizeof(value)) == 0 );
	t( sp_set(db, o) == 0 );
	/* log */
	t( sp_destroy(env) == 0 );

	env = sp_env();
	t( env != NULL );
	db = sp_storage(env);
	t( db != NULL );
	c = sp_ctl(db, "conf");
	t( c != NULL );
	t( sp_set(c, "storage.dir", "test") == 0 );
	t( sp_set(c, "storage.node_branch_wm", 0) == 0 );
	t( sp_set(c, "storage.node_merge_wm", 1) == 0 );
	t( sp_set(c, "storage.threads", 0) == 0 );
	t( sp_open(env) == 0 );

	/* reply log */
	key = 7;
	value = 8;
	o = sp_object(db);
	t( o != NULL );
	t( sp_set(o, "key", &key, sizeof(key)) == 0 );
	t( sp_set(o, "value", &value, sizeof(value)) == 0 );
	t( sp_set(db, o) == 0 );

	o = sp_object(db);
	t( sp_set(o, "key", &key, sizeof(key)) == 0 );
	o = sp_get(db, o);
	t( o != NULL );
	t( *(int*)sp_get(o, "value", NULL) == 8 );
	sp_destroy(o);

	t( sp_destroy(env) == 0 );
}

static void
test_recover_merge_logless_set_replace_get1(void)
{
	rmrf("./test");
	rmrf("./log");

	void *env = sp_env();
	t( env != NULL );
	void *db = sp_storage(env);
	t( db != NULL );
	void *c = sp_ctl(db, "conf");
	t( c != NULL );
	t( sp_set(c, "storage.dir", "test") == 0 );
	t( sp_set(c, "storage.node_branch_wm", 0) == 0 );
	t( sp_set(c, "storage.node_merge_wm", 1) == 0 );
	t( sp_set(c, "storage.threads", 0) == 0 );
	t( sp_open(env) == 0 );
	t( sp_set(sp_ctl(db, "ctl"), "branch") == 0 );
	t( sp_set(sp_ctl(db, "ctl"), "merge") == 0 );
	t( sp_destroy(env) == 0 );

	env = sp_env();
	t( env != NULL );
	db = sp_storage(env);
	t( db != NULL );
	c = sp_ctl(db, "conf");
	t( c != NULL );
	t( sp_set(c, "storage.dir", "test") == 0 );
	t( sp_set(c, "storage.node_branch_wm", 0) == 0 );
	t( sp_set(c, "storage.node_merge_wm", 1) == 0 );
	t( sp_set(c, "storage.threads", 0) == 0 );
	t( sp_open(env) == 0 );

	int key = 7;
	void *o = sp_object(db);
	t( o != NULL );
	t( sp_set(o, "key", &key, sizeof(key)) == 0 );
	t( sp_set(o, "value", &key, sizeof(key)) == 0 );
	t( sp_set(db, o) == 0 );
	t( sp_set(sp_ctl(db, "ctl"), "branch") == 0 );
	t( sp_set(sp_ctl(db, "ctl"), "merge") == 0 );
	t( sp_destroy(env) == 0 );

	env = sp_env();
	t( env != NULL );
	db = sp_storage(env);
	t( db != NULL );
	c = sp_ctl(db, "conf");
	t( c != NULL );
	t( sp_set(c, "storage.dir", "test") == 0 );
	t( sp_set(c, "storage.node_branch_wm", 0) == 0 );
	t( sp_set(c, "storage.node_merge_wm", 1) == 0 );
	t( sp_set(c, "storage.threads", 0) == 0 );
	t( sp_open(env) == 0 );
	key = 7;
	int value = 8;
	o = sp_object(db);
	t( o != NULL );
	t( sp_set(o, "key", &key, sizeof(key)) == 0 );
	t( sp_set(o, "value", &value, sizeof(value)) == 0 );
	t( sp_set(db, o) == 0 );
	/* log */
	t( sp_destroy(env) == 0 );

	env = sp_env();
	t( env != NULL );
	db = sp_storage(env);
	t( db != NULL );
	c = sp_ctl(db, "conf");
	t( c != NULL );
	t( sp_set(c, "storage.dir", "test") == 0 );
	t( sp_set(c, "storage.node_branch_wm", 0) == 0 );
	t( sp_set(c, "storage.node_merge_wm", 1) == 0 );
	t( sp_set(c, "storage.threads", 0) == 0 );
	t( sp_open(env) == 0 );

	/* reply */
	key = 7;
	value = 8;
	o = sp_object(db);
	t( o != NULL );
	t( sp_set(o, "key", &key, sizeof(key)) == 0 );
	t( sp_set(o, "value", &value, sizeof(value)) == 0 );
	t( sp_set(db, o) == 0 );

	key = 7;
	o = sp_object(db);
	t( sp_set(o, "key", &key, sizeof(key)) == 0 );
	o = sp_get(db, o);
	t( o != NULL );
	t( *(int*)sp_get(o, "value", NULL) == 8 );
	sp_destroy(o);

	t( sp_destroy(env) == 0 );
}

static void
test_recover_merge_logless_fetch_gte(void)
{
	rmrf("./test");
	rmrf("./log");

	void *env = sp_env();
	t( env != NULL );
	void *db = sp_storage(env);
	t( db != NULL );
	void *c = sp_ctl(db, "conf");
	t( c != NULL );
	t( sp_set(c, "storage.dir", "test") == 0 );
	t( sp_set(c, "storage.node_branch_wm", 0) == 0 );
	t( sp_set(c, "storage.node_merge_wm", 1) == 0 );
	t( sp_set(c, "storage.cmp", sr_cmpu32) == 0 );
	t( sp_set(c, "storage.threads", 0) == 0 );
	t( sp_open(env) == 0 );

	int i = 0;
	while ( i < 949 ) {
		void *o = sp_object(db);
		t( o != NULL );
		t( sp_set(o, "key", &i, sizeof(i)) == 0 );
		t( sp_set(o, "value", &i, sizeof(i)) == 0 );
		t( sp_set(db, o) == 0 );
		i++;
	}
	t( sp_set(sp_ctl(db, "ctl"), "branch") == 0 );
	t( sp_set(sp_ctl(db, "ctl"), "merge") == 0 );
	i = 0;
	while ( i < 949 ) {
		int value = i + 1;
		void *o = sp_object(db);
		t( o != NULL );
		t( sp_set(o, "key", &i, sizeof(i)) == 0 );
		t( sp_set(o, "value", &value, sizeof(value)) == 0 );
		t( sp_set(db, o) == 0 );
		i++;
	}
	/* log */
	t( sp_destroy(env) == 0 );

	env = sp_env();
	t( env != NULL );
	db = sp_storage(env);
	t( db != NULL );
	c = sp_ctl(db, "conf");
	t( c != NULL );
	t( sp_set(c, "storage.dir", "test") == 0 );
	t( sp_set(c, "storage.node_branch_wm", 0) == 0 );
	t( sp_set(c, "storage.node_merge_wm", 1) == 0 );
	t( sp_set(c, "storage.cmp", sr_cmpu32) == 0 );
	t( sp_set(c, "storage.threads", 0) == 0 );
	t( sp_open(env) == 0 );

	/* reply */
	i = 0;
	while ( i < 949 ) {
		int value = i + 1;
		void *o = sp_object(db);
		t( o != NULL );
		t( sp_set(o, "key", &i, sizeof(i)) == 0 );
		t( sp_set(o, "value", &value, sizeof(value)) == 0 );
		t( sp_set(db, o) == 0 );
		i++;
	}

	void *cur = sp_cursor(db, ">=", NULL);
	t( cur != NULL );
	i = 0;
	while (sp_get(cur)) {
		void *o = sp_object(cur);
		t( *(int*)sp_get(o, "value", NULL) == i + 1 );
		i++;
	}
	t( i == 949 );
	sp_destroy(cur);
	t( sp_destroy(env) == 0 );
}

static void
test_recover_merge_logless_fetch_gt(void)
{
	rmrf("./test");
	rmrf("./log");

	void *env = sp_env();
	t( env != NULL );
	void *db = sp_storage(env);
	t( db != NULL );
	void *c = sp_ctl(db, "conf");
	t( c != NULL );
	t( sp_set(c, "storage.dir", "test") == 0 );
	t( sp_set(c, "storage.node_branch_wm", 0) == 0 );
	t( sp_set(c, "storage.node_merge_wm", 1) == 0 );
	t( sp_set(c, "storage.cmp", sr_cmpu32) == 0 );
	t( sp_set(c, "storage.threads", 0) == 0 );
	t( sp_open(env) == 0 );

	int i = 0;
	while ( i < 949 ) {
		void *o = sp_object(db);
		t( o != NULL );
		t( sp_set(o, "key", &i, sizeof(i)) == 0 );
		t( sp_set(o, "value", &i, sizeof(i)) == 0 );
		t( sp_set(db, o) == 0 );
		i++;
	}
	t( sp_set(sp_ctl(db, "ctl"), "branch") == 0 );
	t( sp_set(sp_ctl(db, "ctl"), "merge") == 0 );
	i = 0;
	while ( i < 949 ) {
		int value = i + 1;
		void *o = sp_object(db);
		t( o != NULL );
		t( sp_set(o, "key", &i, sizeof(i)) == 0 );
		t( sp_set(o, "value", &value, sizeof(value)) == 0 );
		t( sp_set(db, o) == 0 );
		i++;
	}
	/* log */
	t( sp_destroy(env) == 0 );

	env = sp_env();
	t( env != NULL );
	db = sp_storage(env);
	t( db != NULL );
	c = sp_ctl(db, "conf");
	t( c != NULL );
	t( sp_set(c, "storage.dir", "test") == 0 );
	t( sp_set(c, "storage.node_branch_wm", 0) == 0 );
	t( sp_set(c, "storage.node_merge_wm", 1) == 0 );
	t( sp_set(c, "storage.cmp", sr_cmpu32) == 0 );
	t( sp_set(c, "storage.threads", 0) == 0 );
	t( sp_open(env) == 0 );

	/* reply */
	i = 0;
	while ( i < 949 ) {
		int value = i + 1;
		void *o = sp_object(db);
		t( o != NULL );
		t( sp_set(o, "key", &i, sizeof(i)) == 0 );
		t( sp_set(o, "value", &value, sizeof(value)) == 0 );
		t( sp_set(db, o) == 0 );
		i++;
	}

	i = 0;
	while (i < 949) {
		void *o = sp_object(db);
		t( o != NULL );
		t( sp_set(o, "key", &i, sizeof(i)) == 0 );
		void *cur = sp_cursor(db, ">", o);
		t( cur != NULL );
		o = sp_object(cur);
		if (i != 948) {
			t( o != NULL );
			t( *(int*)sp_get(o, "key", NULL) == i + 1 );
		} else {
			t( o == NULL );
		}
		sp_destroy(cur);
		i++;
	}
	t( sp_destroy(env) == 0 );
}

static void
test_recover_merge_logless_fetch_lte(void)
{
	rmrf("./test");
	rmrf("./log");

	void *env = sp_env();
	t( env != NULL );
	void *db = sp_storage(env);
	t( db != NULL );
	void *c = sp_ctl(db, "conf");
	t( c != NULL );
	t( sp_set(c, "storage.dir", "test") == 0 );
	t( sp_set(c, "storage.node_branch_wm", 0) == 0 );
	t( sp_set(c, "storage.node_merge_wm", 1) == 0 );
	t( sp_set(c, "storage.cmp", sr_cmpu32) == 0 );
	t( sp_set(c, "storage.threads", 0) == 0 );
	t( sp_open(env) == 0 );

	int i = 0;
	while ( i < 949 ) {
		void *o = sp_object(db);
		t( o != NULL );
		t( sp_set(o, "key", &i, sizeof(i)) == 0 );
		t( sp_set(o, "value", &i, sizeof(i)) == 0 );
		t( sp_set(db, o) == 0 );
		i++;
	}
	t( sp_set(sp_ctl(db, "ctl"), "branch") == 0 );
	t( sp_set(sp_ctl(db, "ctl"), "merge") == 0 );
	i = 0;
	while ( i < 949 ) {
		int value = i + 1;
		void *o = sp_object(db);
		t( o != NULL );
		t( sp_set(o, "key", &i, sizeof(i)) == 0 );
		t( sp_set(o, "value", &value, sizeof(value)) == 0 );
		t( sp_set(db, o) == 0 );
		i++;
	}
	/* log */
	t( sp_destroy(env) == 0 );

	env = sp_env();
	t( env != NULL );
	db = sp_storage(env);
	t( db != NULL );
	c = sp_ctl(db, "conf");
	t( c != NULL );
	t( sp_set(c, "storage.dir", "test") == 0 );
	t( sp_set(c, "storage.node_branch_wm", 0) == 0 );
	t( sp_set(c, "storage.node_merge_wm", 1) == 0 );
	t( sp_set(c, "storage.cmp", sr_cmpu32) == 0 );
	t( sp_set(c, "storage.threads", 0) == 0 );
	t( sp_open(env) == 0 );

	/* reply */
	i = 0;
	while ( i < 949 ) {
		int value = i + 1;
		void *o = sp_object(db);
		t( o != NULL );
		t( sp_set(o, "key", &i, sizeof(i)) == 0 );
		t( sp_set(o, "value", &value, sizeof(value)) == 0 );
		t( sp_set(db, o) == 0 );
		i++;
	}

	void *cur = sp_cursor(db, "<=", NULL);
	t( cur != NULL );
	i = 948;
	while (sp_get(cur)) {
		void *o = sp_object(cur);
		t( *(int*)sp_get(o, "key", NULL) == i );
		i--;
	}
	t( i == -1 );
	sp_destroy(cur);
	t( sp_destroy(env) == 0 );
}

static void
test_recover_merge_logless_fetch_lt(void)
{
	rmrf("./test");
	rmrf("./log");

	void *env = sp_env();
	t( env != NULL );
	void *db = sp_storage(env);
	t( db != NULL );
	void *c = sp_ctl(db, "conf");
	t( c != NULL );
	t( sp_set(c, "storage.dir", "test") == 0 );
	t( sp_set(c, "storage.node_branch_wm", 0) == 0 );
	t( sp_set(c, "storage.node_merge_wm", 1) == 0 );
	t( sp_set(c, "storage.cmp", sr_cmpu32) == 0 );
	t( sp_set(c, "storage.threads", 0) == 0 );
	t( sp_open(env) == 0 );

	int i = 0;
	while ( i < 949 ) {
		void *o = sp_object(db);
		t( o != NULL );
		t( sp_set(o, "key", &i, sizeof(i)) == 0 );
		t( sp_set(o, "value", &i, sizeof(i)) == 0 );
		t( sp_set(db, o) == 0 );
		i++;
	}
	t( sp_set(sp_ctl(db, "ctl"), "branch") == 0 );
	t( sp_set(sp_ctl(db, "ctl"), "merge") == 0 );
	i = 0;
	while ( i < 949 ) {
		int value = i + 1;
		void *o = sp_object(db);
		t( o != NULL );
		t( sp_set(o, "key", &i, sizeof(i)) == 0 );
		t( sp_set(o, "value", &value, sizeof(value)) == 0 );
		t( sp_set(db, o) == 0 );
		i++;
	}
	/* log */
	t( sp_destroy(env) == 0 );

	env = sp_env();
	t( env != NULL );
	db = sp_storage(env);
	t( db != NULL );
	c = sp_ctl(db, "conf");
	t( c != NULL );
	t( sp_set(c, "storage.dir", "test") == 0 );
	t( sp_set(c, "storage.node_branch_wm", 0) == 0 );
	t( sp_set(c, "storage.node_merge_wm", 1) == 0 );
	t( sp_set(c, "storage.cmp", sr_cmpu32) == 0 );
	t( sp_set(c, "storage.threads", 0) == 0 );
	t( sp_open(env) == 0 );

	/* reply */
	i = 0;
	while ( i < 949 ) {
		int value = i + 1;
		void *o = sp_object(db);
		t( o != NULL );
		t( sp_set(o, "key", &i, sizeof(i)) == 0 );
		t( sp_set(o, "value", &value, sizeof(value)) == 0 );
		t( sp_set(db, o) == 0 );
		i++;
	}

	i = 948;
	while (i >= 0) {
		void *o = sp_object(db);
		t( o != NULL );
		t( sp_set(o, "key", &i, sizeof(i)) == 0 );
		void *cur = sp_cursor(db, "<", o);
		t( cur != NULL );
		o = sp_object(cur);
		if (i != 0) {
			t( o != NULL );
			t( *(int*)sp_get(o, "key", NULL) == i - 1 );

		} else {
			t( o == NULL );
		}
		sp_destroy(cur);
		i--;
	}
	t( sp_destroy(env) == 0 );
}

int
main(int argc, char *argv[])
{
	test( test_recover_merge_logless_replace_get0 );
	test( test_recover_merge_logless_replace_get1 );
	test( test_recover_merge_logless_set_replace_get0 );
	test( test_recover_merge_logless_set_replace_get1 );
	test( test_recover_merge_logless_fetch_gte );
	test( test_recover_merge_logless_fetch_gt );
	test( test_recover_merge_logless_fetch_lte );
	test( test_recover_merge_logless_fetch_lt );
	return 0;
}
