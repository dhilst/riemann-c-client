#include <riemann/_config.h>
#include <riemann/attribute.h>

void riemann_attribute_init(riemann_attribute_t *attrp)
{
        attribute__init((Attribute *) attrp);
}

riemann_attribute_t *riemann_attribute_alloc(void)
{
        return (malloc(sizeof (riemann_attribute_t)));
}

void riemann_attribute_free(riemann_attribute_t *attrp)
{
        assert(attrp);

        if (attrp->key)
                free(attrp->key);

        if (attrp->value)
                free(attrp->value);

        free(attrp);
        attrp = NULL;
}

void riemann_attribute_set_key(riemann_attribute_t *attrp, char *key)
{
        attrp->key = strdup(key);
        assert(attrp->key);
}

void riemann_attribute_set_value(riemann_attribute_t *attrp, char *value)
{
        attrp->value = strdup(value);
        assert(attrp->value);
}

