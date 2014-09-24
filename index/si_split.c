
/*
 * sophia database
 * sphia.org
 *
 * Copyright (c) Dmitry Simonenko
 * BSD License
*/

#include <libsr.h>
#include <libsv.h>
#include <libsd.h>
#include <libsi.h>

int si_splitfree(srbuf *result, sr *r)
{
	sriter i;
	sr_iterinit(&i, &sr_bufiterref, NULL);
	sr_iteropen(&i, result, sizeof(sinode*));
	for (; sr_iterhas(&i); sr_iternext(&i)) {
		sinode *p = sr_iterof(&i);
		si_nodefree(p, r);
	}
	return 0;
}

int si_split(sisplit *s, sr *r, sdc *c, srbuf *result)
{
	int count = 0;
	int rc;
	sdmerge merge;
	sd_mergeinit(&merge, r, s->i, &c->build,
	             s->size_key,
	             s->size_stream,
	             s->size_node,
	             s->conf->node_page_size, s->lsvn);
	while ((rc = sd_merge(&merge)) > 0)
	{
		sinode *n = si_nodenew(r);
		if (srunlikely(n == NULL))
			goto error;
		if (s->src_deriveid && count == 0)
			n->id = s->src->id;
		else
			n->id = sr_seq(r->seq, SR_NSNNEXT);
		rc = si_nodecreate(n, s->conf, s->root, &merge.index, &c->build);
		if (srunlikely(rc == -1))
			goto error;
		rc = sr_bufadd(result, r->a, &n, sizeof(sinode*));
		if (srunlikely(rc == -1)) {
			si_nodefree(n, r);
			goto error;
		}
		sd_buildreset(&c->build);
		count++;
	}
	if (srunlikely(rc == -1))
		goto error;

	return 0;
error:
	si_splitfree(result, r);
	sd_mergefree(&merge);
	return -1;
}
