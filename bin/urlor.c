#include <lcthw/tstree.h>
#include <lcthw/bstrlib.h>

TSTree *add_route_data(TSTree * routes, bstring line)
{
    struct bstrList *data = bsplit(line, ' ');
    check(data != NULL, "Bad data from bsplit.");
    check(data->qty == 2, "Line '%s' does not have two columns",
            bdata(line));

    routes = TSTree_insert(routes,
            bdata(data->entry[0]),
            blength(data->entry[0]),
            bstrcpy(data->entry[1]));

    bstrListDestroy(data);

    return routes;

error:
    if (data) bstrListDestroy(data);
    return NULL;
}

TSTree *load_routes(const char *file)
{
    TSTree *routes = NULL;
    bstring line = NULL;
    FILE *routes_map = NULL;

    routes_map = fopen(file, "r");
    check(routes_map != NULL, "Failed to open routes: %s", file);

    while((line = bgets((bNgetc) fgetc, routes_map, '\n')) != NULL) {
        check(btrimws(line) == BSTR_OK, "Failed to trim line.");
        routes = add_route_data(routes, line);
        check(routes != NULL, "Failed to add to route.");
        bdestroy(line); line = NULL; // For error cleanup
    }

    fclose(routes_map);
    return routes;

error:
    if (routes_map) fclose(routes_map);
    if (line) bdestroy(line);

    return NULL;
}

bstring match_url(TSTree * routes, bstring url, int *out_prefix)
{
    bstring route = TSTree_search(routes, bdata(url), blength(url));

    if (route == NULL) {
        *out_prefix = 1;
        printf("No exact match found, trying prefix.\n");
        route = TSTree_search_prefix(routes, bdata(url), blength(url));
    } else {
        *out_prefix = 0;
    }

    return route;
}

bstring read_line(const char *prompt)
{
    printf("%s", prompt);

    bstring result = bgets((bNgetc) fgetc, stdin, '\n');
    check_debug(result != NULL, "stdin closed");

    check(btrimws(result) == BSTR_OK, "Failed to trim.");

    return result;

error:
    if (result) bdestroy(result);
    return NULL;
}

void bdestroy_cb(void *value, void *ignored)
{
    (void)ignored;
    bdestroy((bstring) value);
}

void destroy_routes(TSTree * routes)
{
    TSTree_traverse(routes, bdestroy_cb, NULL);
    TSTree_destroy(routes);
}

int main(int argc, char *argv[])
{
    bstring url = NULL;
    bstring route = NULL;
    TSTree *routes = NULL;
    int prefix = 0;

    check(argc == 2, "USAGE: urlor <urlfile>");

    routes = load_routes(argv[1]);
    check(routes != NULL, "Your route file has an error.");

    // BUG: Only CTRL-C can make you exit this?
    while (1) {
        url = read_line("URL> ");
        check_debug(url != NULL, "Goodbye");

        route = match_url(routes, url, &prefix);

        if (route) {
            if (prefix) {
                printf("PREFIX MATCH: %s == %s\n", bdata(url), bdata(route));
            } else {
                printf("EXACT MATCH: %s == %s\n", bdata(url), bdata(route));
            }
        } else {
            printf("FAIL: %s\n", bdata(url));
        }

        bdestroy(url);
    }

    destroy_routes(routes);
    return 0;

error:
    if (routes) destroy_routes(routes);
    return 1;
}
