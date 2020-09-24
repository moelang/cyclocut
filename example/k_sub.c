#include "cdds/cdds_builtin.h"
#include "dds/dds.h"

int main(int argc, char *argv[]) {

    dds_entity_t p;
    dds_entity_t t;
    dds_entity_t r;
    KeyValue *sample[1] = {0};
    dds_sample_info_t si;

    p = dds_create_participant (DDS_DOMAIN_DEFAULT, NULL, NULL);
    t = dds_create_topic (p, &KeyValue_desc, "KeyValue", NULL, NULL);
    r = dds_create_reader (p, t, NULL, NULL);

    printf ("=== [Reading] : \n");
    while (true) {
        int n = dds_take(r, (void**)sample, &si, 1, 1);
        if (n > 0 && si.valid_data) {
            printf ("(%s, %s)\n", sample[0]->key, sample[0]->value);
            fflush (stdout);
        }
        dds_sleepfor (DDS_MSECS (500));

    }
  return 0;
}